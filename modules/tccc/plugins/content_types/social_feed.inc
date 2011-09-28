<?php

$plugin = array(
  'title' => 'Social Media Feed',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_social_feed_content_type_render($subtype, $conf, $args, $context) {
 
  $output = _tccc_social_feeds(3);
  $output .= l('Older posts', 'feeds');
//  
//  unset($feed);
//  
//  $output .= l('Older posts', 'feeds');
  
                                 
  $block = new stdClass;
  $block->title = 'The City Pulse';
  $block->content = $output;
  return $block;
}


function tccc_social_feed_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_social_feed_content_type_admin_title($subtype, $conf, $context) {
  return 'Social Media Feed';
}


