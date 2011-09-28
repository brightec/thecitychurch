<?php

$plugin = array(
  'title' => 'Promoted Events',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_promotedevents_content_type_render($subtype, $conf, $args, $context) {

  $result = _tccc_get_promoted_events();    
  $output = '';
  $title = '';
  
  if($result){
    $title = 'Promoted Events';
    $result = entity_load('node', array_keys($result['node']));

    $output .= '<div class="events-container clearfix">';
    foreach($result as $event){
      $output .= theme('event', array('event' => $event));
    }
    $output .= '</div>';
  }
                                 
  $block = new stdClass;
  $block->title = $title;
  $block->content = $output;
  return $block;
}


function tccc_promotedevents_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_promotedevents_content_type_admin_title($subtype, $conf, $context) {
  return 'Promoted Events';
}
