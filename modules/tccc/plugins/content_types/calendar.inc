<?php

$plugin = array(
  'title' => 'Calendar Of Events',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_calendar_content_type_render($subtype, $conf, $args, $context) {
  $output = '';
  $output .= '<div id="calendar-wrapper">';
  $output .= '<div id="calendar"></div>';

  $output .= '<div class="calendar-actions clearfix">';
  $output .= l('back', '', array('attributes' => array('class' => array('back'))));	
  $output .= l('next', '', array('attributes' => array('class' => array('next'))));	
  $output .= '</div>';

  $output .= '</div>';

  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_calendar_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_calendar_content_type_admin_title($subtype, $conf, $context) {
  return 'Calendar';
}

