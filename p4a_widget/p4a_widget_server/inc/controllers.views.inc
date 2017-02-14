<?php

/* Views actions */

/**
 * Delete comment
 */
function p4a_widget_server_views_delete_comment($form, &$form_state, $id_comment){
    $form = array();
    $form['id_comment'] = array(
        '#type' => 'value',
        '#value' => $id_comment,
    );

    return confirm_form(
        $form,
        t('Are you sure you want to delete this item?'),
        'widget/comments/moderation',
        t('This action cannot be undone.'),
        t('Delete'),
        t('Cancel')
    );

    return $form;
}

/**
 * Delete comment
 */
function p4a_widget_server_views_delete_comment_submit($form, &$form_state){
    p4a_widget_server_delete_ranking_and_comment_by_id($form_state['values']['id_comment']);
    $form_state['redirect'] = 'widget/comments/moderation';
}

/**
 * Approve comment
 */
function p4a_widget_server_views_approve_comment($form, &$form_state, $id_comment){
    $form = array();
    $form['id_comment'] = array(
        '#type' => 'value',
        '#value' => $id_comment,
    );

    return confirm_form(
        $form,
        t('Are you sure you want to approve this comment?'),
        'widget/comments/moderation',
        '',
        t('Approve'),
        t('Cancel')
    );

    return $form;
}

/**
 * Approve comment
 */
function p4a_widget_server_views_approve_comment_submit($form, &$form_state){
    p4a_widget_server_set_comment_status($form_state['values']['id_comment'], 2);
    $id_user = p4a_widget_server_get_user_by_comment($form_state['values']['id_comment']);
    p4a_widget_server_add_approved_comment($id_user);
    $form_state['redirect'] = 'widget/comments/moderation';
}

/**
 * Reject comment
 */
function p4a_widget_server_views_reject_comment($form, &$form_state, $id_comment){
    $form = array();
    $form['id_comment'] = array(
        '#type' => 'value',
        '#value' => $id_comment,
    );

    return confirm_form(
        $form,
        t('Are you sure you want to reject this comment?'),
        'widget/comments/moderation',
        '',
        t('Reject'),
        t('Cancel')
    );

    return $form;
}

/**
 * Reject comment
 */
function p4a_widget_server_views_reject_comment_submit($form, &$form_state){
    p4a_widget_server_set_comment_status($form_state['values']['id_comment'], 1);
    $id_user = p4a_widget_server_get_user_by_comment($form_state['values']['id_comment']);
    p4a_widget_server_add_rejected_comment($id_user);
    $form_state['redirect'] = 'widget/comments/moderation';
}

/**
 * Unapprove comment
 */
function p4a_widget_server_views_unapprove_comment($form, &$form_state, $id_comment){
    $form = array();
    $form['id_comment'] = array(
        '#type' => 'value',
        '#value' => $id_comment,
    );

    return confirm_form(
        $form,
        t('Are you sure you want to unapprove this comment?'),
        'widget/comments/moderation',
        '',
        t('Unapprove'),
        t('Cancel')
    );

    return $form;
}

/**
 * Unapprove comment
 */
function p4a_widget_server_views_unapprove_comment_submit($form, &$form_state){
    $status = p4a_widget_server_get_comment_status($form_state['values']['id_comment']);
    p4a_widget_server_set_comment_status($form_state['values']['id_comment'], 0);
    $id_user = p4a_widget_server_get_user_by_comment($form_state['values']['id_comment']);
    if($status == 1){
        p4a_widget_server_subtract_rejected_comment($id_user);
    }
    elseif($status == 2){
        p4a_widget_server_subtract_approved_comment($id_user);
    }
    $form_state['redirect'] = 'widget/comments/moderation';
}

/**
 * Reset comments
 * Delete all flags from comment
 */
function p4a_widget_server_views_delete_comment_flags($form, &$form_state, $id_comment){
    $form = array();
    $form['id_comment'] = array(
        '#type' => 'value',
        '#value' => $id_comment,
    );

    return confirm_form(
        $form,
        t('Are you sure you want to reset all flags from this comment?'),
        'widget/comments/moderation',
        t('This action cannot be undone.'),
        t('Delete'),
        t('Cancel')
    );

    return $form;
}

/**
 * Reset comments
 * Delete all flags from comment
 */
function p4a_widget_server_views_delete_comment_flags_submit($form, &$form_state){
    $id_comment = $form_state['values']['id_comment'];
    p4a_widget_server_reset_flags($id_comment);
    $form_state['redirect'] = 'widget/comments/moderation';
}