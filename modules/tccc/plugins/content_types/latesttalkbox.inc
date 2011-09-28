<?php

$plugin = array(
  'title' => 'Latest Talk Box',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_latesttalkbox_content_type_render($subtype, $conf, $args, $context) {

  $result = _tccc_get_media('sermon', 1);    
  
  if($result){
    $output = '';
    
    foreach($result as $sermon){
      
      $img = _tccc_media_image($sermon, 'resources_feature');
      $img .= '<div class="shine-resource-button"></div>';

      $output .= l($img, 'node/' . $sermon->nid, array('html' => TRUE, 'attributes' => array('class' => array('box-image'))));

      $output .= '<div class="text">';
      $output .= l($sermon->title, 'node/' . $sermon->nid);
      $output .= '<br>';
      
      $speaker = (!empty($sermon->field_person)) ? taxonomy_term_load($sermon->field_person['und'][0]['tid']) : '';
      $output .= '<span>' . l($speaker->name, 'resources/sermons/speaker/' . $speaker->tid) . '</span>';
      
      $output .= !(empty($sermon->field_recording_date)) ? ' &#124; <span>' . date('l jS F Y',strtotime($sermon->field_recording_date['und'][0]['value'])) . '</span>' : '';
      
      if(!(empty($sermon->field_media_length))) {
        $output .= '<span>' . $sermon->field_media_length['und'][0]['value'] . '</span>';
      }
      
      if(!(empty($sermon->field_media_series))) {
        $series = taxonomy_term_load($sermon->field_media_series['und'][0]['tid']);
        $output .= ' &#124; <span>' . l($series->name, 'taxonomy/term/' . $series->tid ) . '</span>';
      }
      
      $output .= '<br>';
      if(!(empty($sermon->field_tags))) {
        $tags = taxonomy_term_load($sermon->field_tags['und'][0]['tid']);
        $output .= '<span>' . l($tags->name, 'taxonomy/term/' . $tags->tid ) . '</span>';
      }
      
      $output .= '</div>';
    }
  }
  
                               
  $block = new stdClass;
  $block->title = 'Latest';
  $block->content = $output;
  return $block;
}


function tccc_latesttalkbox_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_latesttalkbox_content_type_admin_title($subtype, $conf, $context) {
  return 'Latest Talk Box';
}


function theme_latesttalkbox($items){
  
}
