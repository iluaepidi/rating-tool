<?php

class p4a_widget_server_handler_field_actions extends views_handler_field {

    /**
     * Add some required fields needed on render().
     */
    function construct() {
        parent::construct();
        $this->additional_fields['status'] = array(
            'table' => 'p4a_comment',
            'field' => 'status'
        );
    }

    /**
     * Loads additional fields.
     */
    function query() {
        $this->ensure_my_table();
        $this->add_additional_fields();
    }

    /**
     * Render field.
     */
    function render($values) {
        $moderate = '';
        switch($values->p4a_comment_status){
            case 0:
                $moderate .= l(t('Approve'), 'widget/moderation/comment/' . $values->p4a_comment_id . '/approve');
                $moderate .= ' ';
                $moderate .= l(t('Reject'), 'widget/moderation/comment/' . $values->p4a_comment_id . '/reject');
                break;
            case 1:
            case 2:
                $moderate .= l(t('Unapprove'), 'widget/moderation/comment/' . $values->p4a_comment_id . '/unapprove');
                break;
        }
        $delete = l(t('Delete'), 'widget/moderation/comment/' . $values->p4a_comment_id . '/delete');
        $links = $moderate . ' ' . $delete;
        return $links;
    }
}
