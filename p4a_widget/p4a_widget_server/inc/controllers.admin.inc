<?php

/* Admin */

/**
 * Automoderation settings
 */
function p4a_widget_server_moderation_admin($form, &$form_state){
    $form['p4a_automoderation_flags'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of flags to unapprove comment'),
        '#required' => TRUE,
        '#default_value' => variable_get('p4a_automoderation_flags')
    );
    $form['p4a_automoderation_approved'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of approved comments for autoapprove comment'),
        '#required' => TRUE,
        '#default_value' => variable_get('p4a_automoderation_approved')
    );
    return system_settings_form($form);
}

/**
 * Order settings
 */
function p4a_widget_server_order_admin($form, &$form_state){
    $form['p4a_order'] = array(
        '#type' => 'select',
        '#title' => t('Order by'),
        '#options' => array(
            'valoration' => t('Likes'),
            'date' => t('Date')
        ),
        '#required' => TRUE,
        '#default_value' => variable_get('p4a_order')
    );
    return system_settings_form($form);
}