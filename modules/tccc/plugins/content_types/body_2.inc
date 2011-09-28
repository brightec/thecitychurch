<?php

$plugin = array(
  'title' => 'Body field - Delta #2',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_body_2_content_type_render($subtype, $conf, $args, $context) {
 
  $output = '';

  $node = node_load($args[0]);
  
  if ($node){
    if(isset($node->field_body['und'][1])){
      $output .= $node->field_body['und'][1]['value'];
    }
  }
                                 
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_body_2_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_body_2_content_type_admin_title($subtype, $conf, $context) {
  return 'Body field - Delta #2';
}
