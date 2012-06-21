<?php

$plugin = array(
  'title' => 'Latest Paper Box',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_latestpaperbox_content_type_render($subtype, $conf, $args, $context) {

  $result = _tccc_get_media('paper', 1);    
  $output = '';
  
  if($result){
    
    foreach($result as $paper){
      
      $path = 'node/' . $paper->nid;
      
      $img = _tccc_media_image($paper, 'resources_feature');
      $img .= '<div class="shine-resource-button"></div>';
      
      $output .= l($img, $path, array('html' => TRUE, 'attributes' => array('class' => array('box-image'))));
      
      $output .= '<div class="text">';
      $output .= '<div>' . l($paper->title, $path) . '</div>' ;
      if (!empty($paper->field_tags)){
	      $topic = taxonomy_term_load($paper->field_tags['und'][0]['tid']);
	      $output .= '<div>' . check_plain($topic->name) . '</div>';
      }
      $person = taxonomy_term_load($paper->field_person['und'][0]['tid']);
      //$output .= 'by ' . l($person->name, 'resources/papers/author/' . $person->tid);
      $output .= 'by ' . check_plain($person->name);
      $output .= '</div>';
    }
    
  }
                                 
  $block = new stdClass;
  $block->title = 'Papers';
  $block->content = $output;
  return $block;
}


function tccc_latestpaperbox_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_latestpaperbox_content_type_admin_title($subtype, $conf, $context) {
  return 'Latest Paper Box';
}


function theme_latestpaperbox($items){
  
}
