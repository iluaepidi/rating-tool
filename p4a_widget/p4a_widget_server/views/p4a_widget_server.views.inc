<?php

/**
 *  Implements hook_views_handlers.
 */
function p4a_widget_server_views_handlers() {
    return array(
        'info' => array(
            'path' => drupal_get_path('module', 'p4a_widget_server') . '/views',
        ),
        'handlers' => array(
            'p4a_widget_server_handler_field_datetime' => array(
                'parent' => 'views_handler_field',
            ),
            'p4a_widget_server_handler_field_actions' => array(
                'parent' => 'views_handler_field',
            ),
            'p4a_widget_server_handler_field_status' => array(
                'parent' => 'views_handler_field',
            ),
            'p4a_widget_server_handler_field_flagged' => array(
                'parent' => 'views_handler_field',
            ),
            'p4a_widget_server_handler_sort_datetime' => array(
                'parent' => 'views_handler_sort'
            ),
            'p4a_widget_server_handler_filter_status' => array(
                'parent' => 'views_handler_filter_in_operator'
            ),
            'p4a_widget_server_handler_filter_flagged' => array(
                'parent' => 'views_handler_filter_in_operator'
            )
        )
    );
}

/**
 * Implements hook_views_data().
 */
function p4a_widget_server_views_data(){
    $data = array(
        'p4a_comment' => array(
            'table' => array(
                'group' => t('P4A Reviews'),
                'base' => array(
                    'title' => t('P4A Comments'),
                    'help' => t('Comments table.')
                ),
                'join' => array(
                    'p4a_page' => array(
                        'left_field' => 'id',
                        'field' => 'page'
                    ),
                    'p4a_user' => array(
                        'left_field' => 'id',
                        'field' => 'user'
                    )
                )
            ),
            'id' => array(
                'title' => t('Comment ID'),
                'help' => t('Comment ID.'),
                'field' => array(
                    'handler' => 'views_handler_field_numeric'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_numeric'
                ),
                'argument' => array(
                    'handler' => 'views_handler_argument_numeric'
                )
             ),
            'title' => array(
                'title' => t('Title'),
                'help' => t('Comment title.'),
                'field' => array(
                    'handler' => 'views_handler_field'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                )
            ),
            'comment' => array(
                'title' => t('Comment'),
                'help' => t('Comment.'),
                'field' => array(
                    'handler' => 'views_handler_field'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                )
            ),
            'date' => array(
                'title' => t('Date'),
                'help' => t('Comment date.'),
                'field' => array(
                    'handler' => 'p4a_widget_server_handler_field_datetime'
                ),
                'sort' => array(
                    'handler' => 'p4a_widget_server_handler_sort_datetime'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_date'
                )
            ),
            'page' => array(
                'title' => t('Page ID'),
                'help' => t('ID Page comment belongs to.'),
                'field' => array(
                    'handler' => 'views_handler_field_numeric'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_numeric'
                ),
                'relationship' => array(
                    'base' => 'p4a_page',
                    'base field' => 'id',
                    'handler' => 'views_handler_relationship',
                    'label' => t('Page'),
                    'tile' => t('Page')
                )
            ),
            'user' => array(
                'title' => t('P4A User ID'),
                'help' => t('ID user comment belongs to.'),
                'field' => array(
                    'handler' => 'views_handler_field_numeric'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_numeric'
                ),
                
                'relationship' => array(
                    'base' => 'p4a_user',
                    'base field' => 'id',
                    'handler' => 'views_handler_relationship',
                    'label' => t('P4A User'),
                    'tile' => t('P4A User')
                )
                
            ),
            'status' => array(
                'title' => t('Status'),
                'help' => t('Comment status.'),
                'field' => array(
                    'handler' => 'p4a_widget_server_handler_field_status'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'p4a_widget_server_handler_filter_status'
                )
            ),
            'actions' => array(
                'title' => 'Actions',
                'help' => 'Adds action links for moderating and deleting comments',
                'real field' => 'id',
                'field' => array(
                    'handler' => 'p4a_widget_server_handler_field_actions'
                )
            ),
            'flagged' => array(
                'title' => 'Flagged',
                'help' => 'Shows if comment is flagged',
                'real field' => 'id',
                'field' => array(
                    'handler' => 'p4a_widget_server_handler_field_flagged'
                ),
                'filter' => array(
                    'handler' => 'p4a_widget_server_handler_filter_flagged'
                )
            )
        ),
        'p4a_page' => array(
            'table' => array(
                'group' => t('P4A Reviews')
            ),
            'ref' => array(
                'title' => t('Page'),
                'help' => t('Page ref.'),
                'field' => array(
                    'handler' => 'views_handler_field'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                )
            )
        ),
        'p4a_user' => array(
            'table' => array(
                'group' => t('P4A Reviews'),
                'join' => array(
                    'users' => array(
                        'left_field' => 'uid',
                        'field' => 'ref'
                    )
                )
                
            ),
            'ref' => array(
                'title' => t('User ID'),
                'help' => t('User ID.'),
                'field' => array(
                    'handler' => 'views_handler_field_numeric'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_numeric'
                ),
                'relationship' => array(
                    'base' => 'users',
                    'base field' => 'uid',
                    'handler' => 'views_handler_relationship',
                    'label' => t('Drupal User'),
                    'tile' => t('Drupal User')
                )
                
            )
        ),
    );
    return $data;
}