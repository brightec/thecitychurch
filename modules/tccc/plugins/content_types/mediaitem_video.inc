<?php

$plugin = array(
  'title' => 'Media Item - Video',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_mediaitem_video_content_type_render($subtype, $conf, $args, $context) {
  
  $output = '';
  $sermon = node_load($args[0]);
  if($sermon){
    $output .= '<div id="media-items">';
    if (!empty($sermon->field_media_series)){
      
      $media_series = taxonomy_term_load($sermon->field_media_series['und'][0]['tid']);
      $output .= '<div id="player-wrapper">';
      $output .= theme('image', array('path' => $media_series->field_video_image['und'][0]['uri']));
      $output .= '<div id="player">';
      $output .= '</div>';
      $output .= '</div>';
      $output .= (!empty($sermon->field_video_url)) ? '<span id="vimeo-id">' . $sermon->field_video_url['und'][0]['value'] . '</span>' : '';
    }
    
    $output .= '<div><a class="audio-only" href="http://media.corven.com/Wendy_Lung_IBM_Gaule_QT_Mar_2011.mp3">Audio Only</a></div>';
    
    $output .= (!empty($sermon->field_notes_file)) ? '<div class="notes">' .drupal_render(field_view_field('node', $sermon, 'field_notes_file', array('label' => 'hidden', 'type' => 'download_pdf'))) . '</div>' : '';
    $output .= '</div>';
  }
  
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_mediaitem_video_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_mediaitem_video_content_type_admin_title($subtype, $conf, $context) {
  return 'Media Item - Video';
}

