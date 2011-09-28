<?php

$plugin = array(
  'title' => 'Latest Recommended Box',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_latestrecbox_content_type_render($subtype, $conf, $args, $context) {

  $output = '';
  $node = node_load(17);
  
  
  if($node){
    
    if(!empty($node->field_recommeded_resource)){
      $rec = node_load($node->field_recommeded_resource['und'][0]['nid']);
      
      $output .= '<h2>' . $node->title . '</h2>'; 
      $output .= !empty($node->field_banner_images) ? theme('image', array('path' => $node->field_banner_images['und'][0]['uri'])) : 
      '<div class="grey-media-box">' . l('', 'node/' . $rec->nid ) .'</div>';;
    
      $output .= l($rec->title, 'node/' . $rec->nid);
      $output .= !empty($rec->field_summary) ? implode(' ',array_slice(explode(' ',$rec->field_summary['und'][0]['safe_value']),0, 15))  : '';
    }
  }
                                 
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_latestrecbox_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_latestrecbox_content_type_admin_title($subtype, $conf, $context) {
  return 'Latest Recommended Box';
}


function theme_latestrecbox($items){
  
}

