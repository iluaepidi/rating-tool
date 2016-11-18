<?php

class p4a_widget_server_handler_filter_status extends views_handler_filter_in_operator {
    function get_value_options() {
        $states = array(
            0 => t('Unapproved'),
            1 => t('Rejected'),
            2 => t('Approved')
        );
        $this->value_options = $states;
        return $states;
    }
}
