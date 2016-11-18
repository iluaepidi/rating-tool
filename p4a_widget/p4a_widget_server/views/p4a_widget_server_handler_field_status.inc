<?php

class p4a_widget_server_handler_field_status extends views_handler_field {
    
    /**
     * Render field.
     */
    function render($values) {
        $states = array(
            0 => t('Unapproved'),
            1 => t('Rejected'),
            2 => t('Approved')
        );
        return $states[$values->p4a_comment_status];
    }
}
