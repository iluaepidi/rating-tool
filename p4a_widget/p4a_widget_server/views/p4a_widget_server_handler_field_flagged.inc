<?php

class p4a_widget_server_handler_field_flagged extends views_handler_field {
    
    /**
     * Render field.
     */
    function render($values) {
        //$flagged = p4a_widget_server_get_comment_is_flagged($values->p4a_comment_id);
        $number_of_flags = p4a_widget_server_get_comment_flags($values->p4a_comment_id);
        if($number_of_flags > 0){
            return t('Yes') . ' (' . $number_of_flags . ')';
        }
        return t('No');
    }
}
