<?php

class p4a_widget_server_handler_filter_flagged extends views_handler_filter_in_operator {
  function op_simple() {
    if (empty($this->value)) {
      return;
    }
    $this->ensure_my_table();
    $comments = p4a_widget_server_get_comments_flagged();
    if($this->value[0] == 0){
        $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $comments, 'IN');
    }
    if($this->value[0] == 1){
        $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $comments, 'NOT IN');
    }
  }
}
