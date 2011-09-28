<?php

$plugin = array(
  'title' => t('Discipleship landing page - text and videos'),
  'category' => t('TCCC'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
);



// TODO: formatter for h2

function tccc_discipleship_landing_content_type_render($subtype, $conf, $args, $context) {
	if (empty($context) || empty($context->data)) {
	  return;
	}

  $output = '';

  $node = $context->data;
  
  $vimeo_ids = field_get_items('node', $node, 'field_vimeo_ids1');
  
  
  $subtitle_field = 'field_subtitle1';

  
  for ($x=1; $x<=3; $x++) {
    $output .= '<section class="group group' . $x . ' clearfix">';
    
    $subtitle_field = 'field_subtitle' . $x;
    $vimeo_field = 'field_vimeo_ids' . $x;
    $text_field = 'field_column' . $x;

    $output .= '<div class="grid_4 omega alpha left">';
    $output .= '<header>';
    $output .= drupal_render(field_view_field('node', $node, $subtitle_field, array('type' => 'tccc_h2', 'label' => 'hidden')));
    $output .= '</header>';
    $output .= drupal_render(field_view_field('node', $node, $text_field, array('label' => 'hidden')));
    $output .= '</div>';
    
    $videos = field_get_items('node', $node, $vimeo_field);
    $output .= '<div class="grid_8 alpha omega right">';
    $output .= (count($videos) % 2 == 0) ? '<div class="videos videos-2col clearfix">' : '<div class="videos videos-1col clearfix">';
    foreach ($videos as $video) {
      $output .= drupal_render(field_view_value('node', $node, $vimeo_field, $video, array('type' => 'tccc_vimeo')));
    }
    $output .= '</div>';
    $output .= '</div>';
    
    $output .= '</section>';
  }
  
  
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_discipleship_landing_content_type_admin_title($subtype, $conf, $context) {
  return 'Discipleship landing page - text and videos';
}
