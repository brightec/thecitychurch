<?php

$plugin = array(
  'title' => 'Vimeo Videos',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_disc_video_content_type_render($subtype, $conf, $args, $context) {
 
  $output = '';

  $node = node_load($args[0]);
  $video_field  = $node->$conf['field_select'];


  $vimeo_items = field_get_items('node', $node, 'field_vimeo_id');
dpm($vimeo_items);
  if ($vimeo_items){
    foreach ($vimeo_items as $item) {
      $feed = 'http://vimeo.com/api/v2/video/' . $item['value'] .'.xml';
      $videos =new SimpleXMLElement($feed, null, true);

      foreach($videos as $video){
        $output .= '<a href="' . $video->url . '" class="vimeo" rel="vimeo">';
        $output .= theme('image_style', array('path' => get_remote_image_from_url($video->thumbnail_medium), 'style_name' => 'video_medium'));
        $output .= '</a>';
      }
    }
 } 
 else {
  $image = field_get_items('node', $node, 'field_image');
  dpm($image);
  if($image) {

    $variables = array(
      'path' => $image[0]['uri'], 
      'style_name' => 'video_medium', 
      'alt' => $image[0]['alt'], 
      'title' => $image[0]['title'],
      );


    $output .= '<div class="vimeo">';
    $output .= theme('image_style', $variables);
    $output .= '</div>';

  }
 }
                                 
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_disc_video_content_type_edit_form($form, &$form_state) {
  $node = node_load(18);
  $form['field_select'] = array(
   '#type' => 'select',
   '#title' => t('Display of fields for Vimeo videos'),
   '#default_value' => '',
   '#options' => array(
     'field_body_videos' => t('Field Video #1'),
     'field_body_videos_2' => t('Field Video #2'),
     'field_body_videos_3' => t('Field Video #3'),
   ),
  );
  return $form;
}


function tccc_disc_video_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function tccc_disc_video_content_type_admin_title($subtype, $conf, $context) {
  return 'Vimeo Videos';
}
