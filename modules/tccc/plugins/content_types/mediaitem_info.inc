<?php

$plugin = array(
  'title' => 'Media Item - Info',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_mediaitem_info_content_type_render($subtype, $conf, $args, $context) {
  
  $output = '';
  $sermon = node_load($args[0]);
  $person = taxonomy_term_load($sermon->field_person['und'][0]['tid']);
  
  if($sermon){
    $output .= '<div class="info">';
    $output .= '<span>' . $person->name . '</span>';
    $output .= !(empty($sermon->field_recording_date)) ? ' &#124; <span>' . date('l jS F Y',strtotime($sermon->field_recording_date['und'][0]['value'])) . '</span>' : '';
    $output .= !(empty($sermon->field_media_length)) ? ' &#124; <span>' . $sermon->field_media_length['und'][0]['value'] . '</span>' : ''; 
    
    $output .= '<br/>';
    
    if(!(empty($sermon->field_media_series))) {
      $series = taxonomy_term_load($sermon->field_media_series['und'][0]['tid']);
      $output .= '<span>' . $series->name . '</span>';
    }    

    $output .= !(empty($sermon->field_bible_references)) ? ' &#124; <span>' . $sermon->field_bible_references['und'][0]['safe_value'] . '</span>' : '';
    $output .= '</div>';
    
    if (!(empty($sermon->field_main_text))){
      $output .= '<div class="description">';
      $output .= '<h2>Description</h2>';
      $output .= $sermon->field_main_text['und'][0]['safe_value'];
      $output .= '</div>';
    }


  }
  
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_mediaitem_info_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_mediaitem_info_content_type_admin_title($subtype, $conf, $context) {
  return 'Media Item - Info';
}

