<?php
/**
 * Implements hook_views_default_views()
 * Install comments moderation view
 */
function p4a_widget_server_views_default_views(){
    $view = new view();
    $view->name = 'p4a_comments_moderation';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'p4a_comment';
    $view->human_name = 'P4A, Comments moderation';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'P4A, Comments moderation';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'role';
    $admin = user_role_load_by_name('administrator');
    $moderator = user_role_load_by_name('Comment moderator');
    $handler->display->display_options['access']['role'] = array(
      $admin->rid => $admin->rid,
      $moderator->rid => $moderator->rid,
    );
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'table';
    $handler->display->display_options['style_options']['columns'] = array(
      'id' => 'id',
      'title' => 'title',
      'status' => 'status',
      'flagged' => 'flagged',
      'name' => 'name',
      'ref' => 'ref',
      'actions' => 'actions',
    );
    $handler->display->display_options['style_options']['default'] = '-1';
    $handler->display->display_options['style_options']['info'] = array(
      'id' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'title' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'status' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'flagged' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'name' => array(
        'sortable' => 0,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'ref' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'actions' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['area']['id'] = 'area';
    $handler->display->display_options['empty']['area']['table'] = 'views';
    $handler->display->display_options['empty']['area']['field'] = 'area';
    $handler->display->display_options['empty']['area']['label'] = 'No results';
    $handler->display->display_options['empty']['area']['empty'] = TRUE;
    $handler->display->display_options['empty']['area']['content'] = 'There are no comments to moderate';
    $handler->display->display_options['empty']['area']['format'] = 'plain_text';
    /* Relationship: P4A Reviews: Page ID */
    $handler->display->display_options['relationships']['page']['id'] = 'page';
    $handler->display->display_options['relationships']['page']['table'] = 'p4a_comment';
    $handler->display->display_options['relationships']['page']['field'] = 'page';
    /* Relationship: P4A Reviews: P4A User ID */
    $handler->display->display_options['relationships']['user']['id'] = 'user';
    $handler->display->display_options['relationships']['user']['table'] = 'p4a_comment';
    $handler->display->display_options['relationships']['user']['field'] = 'user';
    /* Relationship: P4A Reviews: User ID */
    $handler->display->display_options['relationships']['ref']['id'] = 'ref';
    $handler->display->display_options['relationships']['ref']['table'] = 'p4a_user';
    $handler->display->display_options['relationships']['ref']['field'] = 'ref';
    $handler->display->display_options['relationships']['ref']['relationship'] = 'user';
    /* Field: P4A Reviews: Comment ID */
    $handler->display->display_options['fields']['id']['id'] = 'id';
    $handler->display->display_options['fields']['id']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['id']['field'] = 'id';
    $handler->display->display_options['fields']['id']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['id']['alter']['path'] = 'widget/comments/moderation/[id]';
    $handler->display->display_options['fields']['id']['separator'] = '';
    /* Field: P4A Reviews: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    /* Field: P4A Reviews: Status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    /* Field: P4A Reviews: Flagged */
    $handler->display->display_options['fields']['flagged']['id'] = 'flagged';
    $handler->display->display_options['fields']['flagged']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['flagged']['field'] = 'flagged';
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['relationship'] = 'ref';
    $handler->display->display_options['fields']['name']['label'] = 'User';
    /* Field: P4A Reviews: Page */
    $handler->display->display_options['fields']['ref']['id'] = 'ref';
    $handler->display->display_options['fields']['ref']['table'] = 'p4a_page';
    $handler->display->display_options['fields']['ref']['field'] = 'ref';
    $handler->display->display_options['fields']['ref']['relationship'] = 'page';
    $handler->display->display_options['fields']['ref']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['ref']['alter']['path'] = '[ref]';
    /* Field: P4A Reviews: Actions */
    $handler->display->display_options['fields']['actions']['id'] = 'actions';
    $handler->display->display_options['fields']['actions']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['actions']['field'] = 'actions';
    /* Sort criterion: P4A Reviews: Date */
    $handler->display->display_options['sorts']['date']['id'] = 'date';
    $handler->display->display_options['sorts']['date']['table'] = 'p4a_comment';
    $handler->display->display_options['sorts']['date']['field'] = 'date';
    $handler->display->display_options['sorts']['date']['order'] = 'DESC';
    $handler->display->display_options['sorts']['date']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['date']['expose']['label'] = 'Date';
    /* Sort criterion: P4A Reviews: Status */
    $handler->display->display_options['sorts']['status']['id'] = 'status';
    $handler->display->display_options['sorts']['status']['table'] = 'p4a_comment';
    $handler->display->display_options['sorts']['status']['field'] = 'status';
    $handler->display->display_options['sorts']['status']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['status']['expose']['label'] = 'Status';
    /* Sort criterion: P4A Reviews: Page */
    $handler->display->display_options['sorts']['ref']['id'] = 'ref';
    $handler->display->display_options['sorts']['ref']['table'] = 'p4a_page';
    $handler->display->display_options['sorts']['ref']['field'] = 'ref';
    $handler->display->display_options['sorts']['ref']['relationship'] = 'page';
    $handler->display->display_options['sorts']['ref']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['ref']['expose']['label'] = 'Page';
    /* Filter criterion: P4A Reviews: Status */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'p4a_comment';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['exposed'] = TRUE;
    $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
    $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
    $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
    $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
    $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array();
    /* Filter criterion: P4A Reviews: Flagged */
    $handler->display->display_options['filters']['flagged']['id'] = 'flagged';
    $handler->display->display_options['filters']['flagged']['table'] = 'p4a_comment';
    $handler->display->display_options['filters']['flagged']['field'] = 'flagged';
    $handler->display->display_options['filters']['flagged']['exposed'] = TRUE;
    $handler->display->display_options['filters']['flagged']['expose']['operator_id'] = 'flagged_op';
    $handler->display->display_options['filters']['flagged']['expose']['label'] = 'Flagged';
    $handler->display->display_options['filters']['flagged']['expose']['operator'] = 'flagged_op';
    $handler->display->display_options['filters']['flagged']['expose']['identifier'] = 'flagged';
    $handler->display->display_options['filters']['flagged']['expose']['remember_roles'] = array();

    /* Display: Comments moderation */
    $handler = $view->new_display('page', 'Comments moderation', 'page_1');
    $handler->display->display_options['path'] = 'widget/comments/moderation';
    $translatables['p4a_comments_moderation'] = array(
      t('Master'),
      t('P4A, Comments moderation'),
      t('more'),
      t('Apply'),
      t('Reset'),
      t('Sort by'),
      t('Asc'),
      t('Desc'),
      t('Page'),
      t('P4A User'),
      t('Drupal User'),
      t('Comment ID'),
      t('.'),
      t('Title'),
      t('Status'),
      t('Flagged'),
      t('User'),
      t('Actions'),
      t('Date'),
      t('Comments moderation'),
    );
    // Add view to list of views to provide.
    $views[$view->name] = $view;
    //----------------------------------------------------------------------------
    unset($view);
    //----------------------------------------------------------------------------
    $view = new view();
    $view->name = 'p4a_comment_detail';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'p4a_comment';
    $view->human_name = 'P4A, Comment detail';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'P4A, Comment detail';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'role';
    $admin = user_role_load_by_name('administrator');
    $moderator = user_role_load_by_name('Comment moderator');
    $handler->display->display_options['access']['role'] = array(
      $admin->rid => $admin->rid,
      $moderator->rid => $moderator->rid,
    );
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: P4A Reviews: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['element_type'] = 'h1';
    $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
    /* Field: P4A Reviews: Date */
    $handler->display->display_options['fields']['date']['id'] = 'date';
    $handler->display->display_options['fields']['date']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['date']['field'] = 'date';
    $handler->display->display_options['fields']['date']['element_type'] = 'span';
    $handler->display->display_options['fields']['date']['element_label_type'] = 'strong';
    $handler->display->display_options['fields']['date']['element_wrapper_type'] = 'p';
    $handler->display->display_options['fields']['date']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['date']['date_format'] = 'short';
    $handler->display->display_options['fields']['date']['second_date_format'] = 'long';
    /* Field: P4A Reviews: Comment */
    $handler->display->display_options['fields']['comment']['id'] = 'comment';
    $handler->display->display_options['fields']['comment']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['comment']['field'] = 'comment';
    $handler->display->display_options['fields']['comment']['element_type'] = 'div';
    $handler->display->display_options['fields']['comment']['element_label_type'] = 'p';
    $handler->display->display_options['fields']['comment']['element_wrapper_type'] = 'div';
    $handler->display->display_options['fields']['comment']['element_default_classes'] = FALSE;
    /* Field: P4A Reviews: Status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    $handler->display->display_options['fields']['status']['element_type'] = 'span';
    $handler->display->display_options['fields']['status']['element_label_type'] = 'strong';
    $handler->display->display_options['fields']['status']['element_wrapper_type'] = 'p';
    $handler->display->display_options['fields']['status']['element_default_classes'] = FALSE;
    /* Field: P4A Reviews: Flagged */
    $handler->display->display_options['fields']['flagged']['id'] = 'flagged';
    $handler->display->display_options['fields']['flagged']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['flagged']['field'] = 'flagged';
    $handler->display->display_options['fields']['flagged']['element_type'] = 'span';
    $handler->display->display_options['fields']['flagged']['element_label_type'] = 'strong';
    $handler->display->display_options['fields']['flagged']['element_wrapper_type'] = 'p';
    $handler->display->display_options['fields']['flagged']['element_default_classes'] = FALSE;
    /* Field: P4A Reviews: Comment ID */
    $handler->display->display_options['fields']['id']['id'] = 'id';
    $handler->display->display_options['fields']['id']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['id']['field'] = 'id';
    /* Field: P4A Reviews: Actions */
    $handler->display->display_options['fields']['actions']['id'] = 'actions';
    $handler->display->display_options['fields']['actions']['table'] = 'p4a_comment';
    $handler->display->display_options['fields']['actions']['field'] = 'actions';
    $handler->display->display_options['fields']['actions']['label'] = '';
    $handler->display->display_options['fields']['actions']['element_type'] = 'p';
    $handler->display->display_options['fields']['actions']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['actions']['element_default_classes'] = FALSE;
    /* Field: Global: Custom text */
    $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['table'] = 'views';
    $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['label'] = '';
    $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Back to comment moderation';
    $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['nothing']['alter']['path'] = 'widget/comments/moderation';
    $handler->display->display_options['fields']['nothing']['element_type'] = 'p';
    $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
    /* Contextual filter: P4A Reviews: Comment ID */
    $handler->display->display_options['arguments']['id']['id'] = 'id';
    $handler->display->display_options['arguments']['id']['table'] = 'p4a_comment';
    $handler->display->display_options['arguments']['id']['field'] = 'id';
    $handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
    $handler->display->display_options['arguments']['id']['exception']['title'] = 'All';
    $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
    $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

    /* Display: Comment detail */
    $handler = $view->new_display('page', 'Comment detail', 'page');
    $handler->display->display_options['path'] = 'widget/comments/moderation/%';
    $translatables['p4a_comment_detail'] = array(
      t('Master'),
      t('P4A, Comment detail'),
      t('more'),
      t('Apply'),
      t('Reset'),
      t('Sort by'),
      t('Asc'),
      t('Desc'),
      t('Title'),
      t('Date'),
      t('Comment'),
      t('Status'),
      t('Flagged'),
      t('Comment ID'),
      t('.'),
      t(','),
      t('Back to comment moderation'),
      t('All'),
      t('Comment detail'),
    );


    // Add view to list of views to provide.
    $views[$view->name] = $view;

    // At the end, return array of default views.
    return $views;
}