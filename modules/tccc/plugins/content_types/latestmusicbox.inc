<?php

$plugin = array(
  'title' => 'Latest music Box',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_latestmusicbox_content_type_render($subtype, $conf, $args, $context) {

  $result = _tccc_get_media('music', 1);    
  $output = '';
  
  if($result){
    
    foreach($result as $track){
      
      $img = _tccc_media_image($track, 'resources_feature');
      $img .= '<div class="shine-resource-button"></div>';
      
      $output .= l($img, 'node/' . $track->nid, array('html' => TRUE, 'attributes' => array('class' => array('box-image'))));
      
      $output .= '<div class="text">';
      $output .= l($track->title, 'node/' . $track->nid);
      $output .= '<br>';
      
      if (!empty($track->field_person)) {
        $artist = taxonomy_term_load($track->field_person['und'][0]['tid']);
        $output .= check_plain($artist->name) . '<br>';
      }
      
      $output .= !(empty($track->field_recording_date)) ? '<div>' . date('l jS F Y',strtotime($track->field_recording_date['und'][0]['value'])) . '</div>' : '';
      
      $output .= '</div>';
    }
    
  }
                                 
  $block = new stdClass;
  $block->title = 'Music';
  $block->content = $output;
  return $block;
}


function tccc_latestmusicbox_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_latestmusicbox_content_type_admin_title($subtype, $conf, $context) {
  return 'Latest music Box';
}


function theme_latestmusicbox($items){
  
}
