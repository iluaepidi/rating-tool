<?php

/**
 * Admin callback. Server.
 */
function p4a_widget_client_server_admin($form, &$form_state){
    $form['p4a_server'] = array(
        '#type' => 'textfield',
        '#title' => t('P4A server'),
		'#description' => t('Leave blank to use default server configuration (./widget/)'),
        '#required' => FALSE,
        '#default_value' => variable_get('p4a_server')
    );

    return system_settings_form($form);
}

/**
 * Admin callback. Comments on init.
 */
function p4a_widget_client_comments_on_init_admin($form, &$form_state){
    $form['p4a_comments_on_init'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of comments'),
        '#required' => TRUE,
        '#default_value' => variable_get('p4a_comments_on_init')
    );

    return system_settings_form($form);
}

/**
 * Admin callback. Comments on init. Validate
 */
function p4a_widget_client_comments_on_init_admin_validate($form, &$form_state){
    $value = $form_state['values']['p4a_comments_on_init'];
    if(!is_int($value) && $value < 1){
        form_set_error('p4a_comments_on_init', 'Enter a integer value greater than zero');
    }
}