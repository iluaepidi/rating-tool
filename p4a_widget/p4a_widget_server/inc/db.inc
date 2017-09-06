<?php

/**
 * Get User
 */
function p4a_widget_server_get_user($ref){
    $id = db_query("SELECT id FROM p4a_user WHERE ref = :ref", array(':ref' => $ref))->fetchField();
    return $id;
}

/**
 * Get User
 */
function p4a_widget_server_get_drupal_user($ref){
    $user = user_load($ref);
    return $user;
}

/**
 * Gets page
 */
function p4a_widget_server_get_page($ref){
    $id = db_query("SELECT id FROM p4a_page WHERE ref = :ref", array(':ref' => $ref))->fetchField();
    return $id;
}

/**
 * Gets app
 */
function p4a_widget_server_get_app($name){
    $id = db_query("SELECT id FROM p4a_app WHERE name = :name", array(':name' => $name))->fetchField();
    return $id;
}

/**
 * Insert app
 */
function p4a_widget_server_insert_app($name, $description = ''){
    $id = db_insert('p4a_app')->fields(array('name' => $name, 'description' => $description))->execute();
    return $id;
}

/**
 * Insert page
 */
function p4a_widget_server_insert_page($ref, $app){
    $id = db_insert('p4a_page')->fields(array('ref' => $ref, 'app' => $app))->execute();
    return $id;
}

/**
 * Insert user
 */
function p4a_widget_server_insert_user($ref){
    $id = db_insert('p4a_user')->fields(array('ref' => $ref, 'approved' => 0, 'rejected' => 0))->execute();
    return $id;
}

/**
 * Insert ranking
 */
function p4a_widget_server_insert_page_ranking($value, $page, $user){
    $id = db_insert('p4a_generalranking')->fields(array('value' => $value, 'page' => $page, 'user' => $user))->execute();
    return $id;
}

/**
 * Insert comment in page by user
 */
function p4a_widget_server_insert_comment($title, $comment, $page, $user, $status){
    $id = db_insert('p4a_comment')->fields(array(
        'title' => $title, 
        'comment' => $comment, 
        'page' => $page, 
        'user' => $user, 
        'date' => date('Y-m-d H:i:s', time()),
        'status' => $status /* MODERATION */
    ))->execute();
    return $id;
}

/**
 * Insert reply
 */
function p4a_widget_server_insert_reply($comment, $reply, $user){
    $id = db_insert('p4a_replycomment')->fields(array(
        'comment' => $comment,
        'reply' => $reply,
        'date' => date('Y-m-d H:i:s', time()),
        'user' => $user
    ))->execute();
    return $id;
}

/**
 * Insert like.
 */
function p4a_widget_server_insert_like($id_comment, $id_user){
    $id = db_insert('p4a_commentvaloration')->fields(array(
        'IdComment' => $id_comment,
        'IdUser' => $id_user
    ))->execute();
    return $id;
}

/**
 * Insert flag.
 */
function p4a_widget_server_insert_flag($id_comment, $id_user){
    $id = db_insert('p4a_commentflag')->fields(array(
        'IdComment' => $id_comment,
        'IdUser' => $id_user
    ))->execute();
    return $id;
}

/**
 * Reset flags.
 * Reset all flasg from comment
 */
function p4a_widget_server_reset_flags($id_comment){
	db_delete('p4a_commentflag')->condition('IdComment', $id_comment)->execute();
}

/**
 * Update ranking
 */
function p4a_widget_server_update_ranking($value, $page, $user){
    $update = db_update('p4a_generalranking')->fields(array('value' => $value))->condition('page', $page)->condition('user', $user)->execute();
    return $update;
}

/**
 * Update comment
 */
function p4a_widget_server_update_comment($title, $comment, $status, $page, $user){
    $update = db_update('p4a_comment')->fields(array('title' => $title, 'comment' => $comment, 'status' => $status))->condition('page', $page)->condition('user', $user)->execute();
    return $update;
}

/**
 * Update reply
 */
function p4a_widget_server_update_reply($id_reply, $reply){
    $update = db_update('p4a_replycomment')->fields(array('reply' => $reply,))->condition('id', $id_reply)->execute();
    return $update;
}

/**
 * Gets page ranking by user
 */
function p4a_widget_server_get_page_ranking_by_user($id_page, $id_user){
    $value = db_query("SELECT value FROM p4a_generalranking WHERE page = :id_page AND user = :id_user", array(':id_page' => $id_page, ':id_user' => $id_user))->fetchField();
    return $value;
}

/**
 * Gets media ranking from page
 */
function p4a_widget_server_get_media_ranking($ref, $app){
    $avg = 0;
    $sql = "SELECT p.id, p.app, gr.value " .
        "FROM p4a_page p " .
            "INNER JOIN p4a_generalranking gr ON p.id = gr.page " .
            "INNER JOIN p4a_app a ON a.id = p.app " .
        "WHERE p.ref = :ref AND a.name = :app";
    $results = db_query($sql, array(':ref' => $ref, ':app' => $app));
    $count = 0;
    if($results->rowCount() > 0){
        foreach($results as $result){
            $count += (int)$result->value;
        }
        $avg = $count / $results->rowCount();
    }
    return $avg;
}

/**
 * Gets comments list from page
 */
function p4a_widget_server_get_comments($ref, $id_user){
	global $base_url, $base_path;
    $sql = "SELECT p.app, c.id, c.comment, c.title, c.date, gr.value, u.ref, " .
        "(SELECT COUNT(v.IdComment) FROM p4a_commentvaloration v WHERE v.IdComment = c.id) as valoration " .
        "FROM p4a_page p " .
            "INNER JOIN p4a_comment c ON p.id = c.page " .
            "LEFT OUTER JOIN p4a_generalranking gr ON p.id = gr.page AND c.user = gr.user " .
            "LEFT OUTER JOIN p4a_user u ON u.id = gr.user " .
        "WHERE p.ref = :ref " .
            "AND (c.status = 2 OR (c.status <> 1 AND c.user = :id_user)) "; /* MODERATION */
        $order = variable_get('p4a_order', 'valoration');
        if($order == 'valoration'){
            $sql .= "ORDER BY valoration DESC, c.date DESC";
        }
        elseif($order == 'date'){
            $sql .= "ORDER BY c.date DESC";
        }
    $results = db_query($sql, array(':ref' => $ref, ':id_user' => $id_user));
    $comments = array();
    foreach($results as $result){
        $user = p4a_widget_server_get_drupal_user($result->ref);
        $user_image = isset($user->picture->uri) ? file_create_url($user->picture->uri) : $base_url . '/' . drupal_get_path('module', 'p4a_widget_client') . '/img/user.png';
        $comment = array(
            'c' => $result->comment,
            'title' => $result->title,
            'date' => $result->date,
            'value' => $result->value,
            'user' => $result->ref,
            'id' => $result->id,
            'rate' => p4a_widget_server_get_comment_rating($result->id),
            'userComment' => p4a_widget_server_has_user_rate_comment($result->id, $id_user),
            'userFlag' => p4a_widget_server_has_user_flag_comment($result->id, $id_user),
            'replies' => p4a_widget_server_get_comment_replies($result->id),
            'userName' => $user->name,
            'userImage' => $user_image
        );
        $comments[] = $comment;
    }
    return $comments;
}

/**
 * Gets replies for given comment
 */
function p4a_widget_server_get_comment_replies($id_comment){
    $sql = "SELECT c.id, c.comment, c.reply, c.date, u.ref " .
        "FROM p4a_replycomment c " .
            "INNER JOIN p4a_user u ON u.id = c.user " .
        "WHERE c.comment = :id_comment";
    $results = db_query($sql, array(':id_comment' => $id_comment));
    $replies = array();
    foreach($results as $result){
        $reply = array(
            'id' => $result->id,
            'comment' => $result->comment,
            'reply' => $result->reply,
            'date' => $result->date,
            'user' => $result->ref
        );
        $replies[] = $reply;
    }
    return $replies;
}

/**
 * Gets rating for a comment
 */
function p4a_widget_server_get_comment_rating($id_comment){
    $rating = db_query("SELECT COUNT(IdComment) AS total FROM p4a_commentvaloration WHERE IdComment = :id_comment", array('id_comment' => $id_comment))->fetchField();
    return (int)$rating;
}

/**
 * Gets user's rating comment
 */
function p4a_widget_server_has_user_rate_comment($id_comment, $id_user){
    $result = db_query("SELECT IdUser FROM p4a_commentvaloration WHERE IdComment = :id_comment AND IdUser = :id_user", array(':id_comment' => $id_comment, ':id_user' => $id_user));
    if($result->rowCount() > 0){
        return TRUE;
    }
    return FALSE;
}

/**
 * Gets user's flag comment
 */
function p4a_widget_server_has_user_flag_comment($id_comment, $id_user){
    $result = db_query("SELECT IdUser FROM p4a_commentflag WHERE IdComment = :id_comment AND IdUser = :id_user", array(':id_comment' => $id_comment, ':id_user' => $id_user));
    if($result->rowCount() > 0){
        return TRUE;
    }
    return FALSE;
}

/**
 * Delete ranking and comment
 */
function p4a_widget_server_delete_ranking_and_comment($id_page, $id_user){
    db_delete('p4a_comment')->condition('page', $id_page)->condition('user', $id_user)->execute();
    db_delete('p4a_generalranking')->condition('page', $id_page)->condition('user', $id_user)->execute();
}

/**
 * Delete ranking and comment
 * By id comment
 */
function p4a_widget_server_delete_ranking_and_comment_by_id($id_comment){
    $result = db_query("SELECT user, page FROM p4a_comment WHERE id = :id_comment", array(':id_comment' => $id_comment))->fetchObject();
    db_delete('p4a_generalranking')->condition('page', $result->page)->condition('user', $result->user)->execute();
    db_delete('p4a_comment')->condition('id', $id_comment)->execute();
}

/**
 * Delete reply
 */

function p4a_widget_server_delete_reply_by_id($id_reply){
    db_delete('p4a_replycomment')->condition('id', $id_reply)->execute();
}

/**
 * Sets comment status
 * 0 -> Unmoderated
 * 1 -> Rejected
 * 2 -> Approved
 */
function p4a_widget_server_set_comment_status($id_comment, $status){
    $update = db_update('p4a_comment')->fields(array('status' => $status))->condition('id', $id_comment)->execute();
    return $update;
}

/**
 * Gets comment status
 */
function p4a_widget_server_get_comment_status($id_comment){
    $status = db_query("SELECT status FROM p4a_comment WHERE id = :id_comment", array(':id_comment' => $id_comment))->fetchField();
    return (int)$status;
}

/**
 * Gets id user from id comment
 */
function p4a_widget_server_get_user_by_comment($id_comment){
    $id_user = db_query("SELECT user FROM p4a_comment WHERE id = :id_comment", array(':id_comment' => $id_comment))->fetchField();
    return $id_user;
}

/**
 * Adds one to approved comments count
 */
function p4a_widget_server_add_approved_comment($id_user){
    $update = db_update('p4a_user')->expression('approved', 'approved + :one', array(':one' => 1))->condition('id', $id_user)->execute();
    return $update;
}
 
/**
 * Subtract from to approved comments count
 */
function p4a_widget_server_subtract_approved_comment($id_user){
    $update = db_update('p4a_user')->expression('approved', 'approved - :one', array(':one' => 1))->condition('id', $id_user)->execute();
    return $update;
}
 
/**
 * Adds one to rejected comments count
 */
function p4a_widget_server_add_rejected_comment($id_user){
    $update = db_update('p4a_user')->expression('rejected', 'rejected + :one', array(':one' => 1))->condition('id', $id_user)->execute();
    return $update;
}

/**
 * Subtract one from rejected comments count
 */
function p4a_widget_server_subtract_rejected_comment($id_user){
    $update = db_update('p4a_user')->expression('rejected', 'rejected - :one', array(':one' => 1))->condition('id', $id_user)->execute();
    return $update;
}

/**
 * Get comment flags
 */
function p4a_widget_server_get_comment_flags($id_comment){
    $rating = db_query("SELECT COUNT(IdComment) AS total FROM p4a_commentflag WHERE IdComment = :id_comment", array('id_comment' => $id_comment))->fetchField();
    return $rating;
}

/**
 * Get comment is flagged
 */
function p4a_widget_server_get_comment_is_flagged($id_comment){
    if(p4a_widget_server_get_comment_flags($id_comment) > 0){
        return TRUE;
    }
    return FALSE;
}

/**
 * Gets comments flagged
 */
function p4a_widget_server_get_comments_flagged(){
    $results = db_query("SELECT IdComment FROM p4a_commentflag");
    $comments = array();
    foreach($results as $result){
        $comments[] = $result->IdComment;
    }
    return $comments;
}

/**
 * Gets number of approved comments by user
 */
function p4a_widget_server_get_user_approved_comments($id_user){
    $n = db_query("SELECT approved FROM p4a_user WHERE id = :id_user", array('id_user' => $id_user))->fetchField();
    return (int)$n;
}

/**
 * Gets the user vendor is replying to
 */
function p4a_widget_server_gets_user_from_comment($id_comment){
    $user_ref = db_query("SELECT U.ref FROM p4a_user U INNER JOIN p4a_comment C on U.id = C.user WHERE C.id = :id_comment", array(':id_comment' => $id_comment))->fetchField();
    return $user_ref;
    
}

/**
 * Gets refs by app
 */
function p4a_widget_server_get_refs_by_app($app){
	$id_app = p4a_widget_server_get_app($app);
    $sql = "SELECT DISTINCT(p.ref) FROM p4a_page p WHERE p.app = :app";
    $results = db_query($sql, array(':app' => $id_app));
    $refs = array();
    foreach($results as $result){
        $refs[] = $result->ref;
    }
    return $refs;
}