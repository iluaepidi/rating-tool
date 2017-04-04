<?php

/**
 * ControllerGetStar
 */
function p4a_widget_server_get_star(){
    $params = drupal_get_query_parameters();
    $id_user = p4a_widget_server_get_user($params['user']);
    $avg = p4a_widget_server_get_media_ranking($params['id'], $params['app']);
    $comments = p4a_widget_server_get_comments($params['id'], $id_user);
    return array(
        'value' => $avg,
        'comments' => $comments
    );
}

/**
 * ControllerStar
 */
function p4a_widget_server_star(){
    global $user;
    $params = drupal_get_query_parameters();
    if($params['user'] != $user->uid){
        return array('done' => FALSE);
    }
    //app
    $id_app = p4a_widget_server_get_app($params['app']);
    if(!$id_app){
        $id_app = p4a_widget_server_insert_app($params['app']);
    }
    //page
    $id_page = p4a_widget_server_get_page($params['id']);
    if(!$id_page){
        $id_page = p4a_widget_server_insert_page($params['id'], $id_app);
    }
    //user
    $id_user = p4a_widget_server_get_user($params['user']);
    if(!$id_user){
        $id_user = p4a_widget_server_insert_user($params['user']);
    }
    //stars
    $stars = $params['star'];
    if($params['titlecomment'] != '' && $params['comment'] != ''){
        $ranking = p4a_widget_server_get_page_ranking_by_user($id_page, $id_user);
        if(!$ranking){
            //Insert
            //ranking
            $id_ranking = p4a_widget_server_insert_page_ranking($stars, $id_page, $id_user);
            //comentario
            //Automoderation
            //Configuration option
            $status = 0;
            if(p4a_widget_server_get_user_approved_comments($id_user) >= variable_get('p4a_automoderation_approved', 3)){
                $status = 2;
                p4a_widget_server_add_approved_comment($id_user);
            }
            $id_comment = p4a_widget_server_insert_comment($params['titlecomment'], $params['comment'], $id_page, $id_user, $status);
        }
        else{
            //Update
            $update_ranking = p4a_widget_server_update_ranking($stars, $id_page, $id_user);
            $status = 0;
            p4a_widget_server_subtract_approved_comment($id_user);
            if(p4a_widget_server_get_user_approved_comments($id_user) >= variable_get('p4a_automoderation_approved', 3)){
                $status = 2;
                p4a_widget_server_add_approved_comment($id_user);
            }
            $update_comment = p4a_widget_server_update_comment($params['titlecomment'], $params['comment'], $status, $id_page, $id_user);
        }
    }
    return array('done' => TRUE);
}

/**
 * ControllerDeleteStar
 */
function p4a_widget_server_delete_star(){
    global $user;
    $params = drupal_get_query_parameters();
    if($params['user'] != $user->uid){
        return array('done' => FALSE);
    }
    $id_page = p4a_widget_server_get_page($params['id']);
    $id_user = p4a_widget_server_get_user($params['user']);
    p4a_widget_server_delete_ranking_and_comment($id_page, $id_user);
    return array('done' => TRUE);
}

/**
 * ControllerReplyComment
 */
function p4a_widget_server_reply_comment(){
    if(!p4a_widget_user_is_vendor()){
        return array('done' => FALSE);
    }
    //global $user;
    $params = drupal_get_query_parameters();
    if($params['comment'] != ''){
        if(intval($params['IdReply']) == 0){
            $id_user = p4a_widget_server_get_user($params['user']);
            if(!$id_user){
                $id_user = p4a_widget_server_insert_user($params['user']);
            }
            $id_reply = p4a_widget_server_insert_reply($params['IdComment'], $params['comment'], $id_user);
            //Send email
            $user_ref = p4a_widget_server_gets_user_from_comment($params['IdComment']);
            $drupal_user = p4a_widget_server_get_drupal_user($user_ref);
            //$drupal_user->mail;
            drupal_mail('p4a_widget_server', 'reply', $drupal_user->mail, 'en');
        }
        else{
            $update_reply = p4a_widget_server_update_reply($params['IdReply'], $params['comment']);
        }
    }
    return array('done' => TRUE);
}

/**
 * ControllerDeleteReply
 */
function p4a_widget_server_delete_reply(){
    if(!p4a_widget_user_is_vendor()){
        return array('done' => FALSE);
    }
    $params = drupal_get_query_parameters();
    p4a_widget_server_delete_reply_by_id($params['IdReply']);
    return array('done' => TRUE);
}

/**
 * ControllerRateComment
 */
function p4a_widget_server_rate_comment(){
    global $user;
    $params = drupal_get_query_parameters();
    if($params['user'] != $user->uid){
        return array('done' => FALSE);
    }
    $id_user = p4a_widget_server_get_user($params['user']);
    $id = p4a_widget_server_insert_like($params['IdComment'], $id_user);
    return array('done' => TRUE);
}

/**
 * ControllerFlagComment
 */
function p4a_widget_server_flag_comment(){
    global $user;
    $params = drupal_get_query_parameters();
    if($params['user'] != $user->uid){
        return array('done' => FALSE);
    }
    $id_user = p4a_widget_server_get_user($params['user']);
    $id = p4a_widget_server_insert_flag($params['IdComment'], $id_user);
    // If flagged more than X times unapprove comment
    // Configuration option
    if(p4a_widget_server_get_comment_flags($params['IdComment']) >= variable_get('p4a_automoderation_flag', 3)){
        p4a_widget_server_set_comment_status($params['IdComment'], 0);
    }
    return array('done' => TRUE);
}

/**
 * Assign rate to nodes
 */
function p4a_widget_server_assign_rate_to_nodes($form, &$form_state){
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Assign rate to nodes')
    );
	return $form;
}

/**
 * Assign rate to nodes
 * Submit
 */
function p4a_widget_server_assign_rate_to_nodes_submit($form, &$form_state){
	global $base_url;
	$total = 0;
	//drupal_set_message('<pre>' . print_r(p4a_widget_server_get_refs_by_app($base_url), TRUE) . '</pre>');
	foreach(p4a_widget_server_get_refs_by_app($base_url) as $ref){
		if(preg_match('/node\/([0-9]+)/', $ref, $matches)){
			//drupal_set_message('<pre>' . print_r($matches, TRUE) . '</pre>');
			$node = node_load($matches[1]);
			if(isset($node->field_p4a_rating)){
				//drupal_set_message('<pre>' . print_r($node, TRUE) . '</pre>');
				$rating = p4a_widget_server_get_media_ranking($ref, $base_url);
				//drupal_set_message('<pre>' . print_r($rating, TRUE) . '</pre>');
				$node->field_p4a_rating[LANGUAGE_NONE][]['value'] = $rating;
				node_save($node);
				$total++;
			}
		}
	}
	drupal_set_message('Done. ' . $total . ' ratings assigned');
}