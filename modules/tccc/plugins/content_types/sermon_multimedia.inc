<?php

$plugin = array(
  'title' => 'Sermon multimedia',
  'category' => 'TCCC',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);



function tccc_sermon_multimedia_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $node = $context->data;
  $output = '';

  foreach (field_get_items('node', $node, 'field_vimeo_id') as $item) {
    $output .= '<div class="video">';
    $output .= '<iframe id="player_1" src="http://player.vimeo.com/video/' . $item['safe_value'] . '?title=0&amp;byline=0&amp;portrait=0&amp;autoplay=0&amp;api=1&amp;player_id=player_1" width="640" height="360"></iframe>';
    $output .= '</div>';		
  }

  foreach (field_get_items('node', $node, 'field_audio_file') as $item) {
		
		// URL for the Audio Source
		$url =  file_create_url($item['uri']);
		
		// Get the image for when there is no vimeo or the user selects audio
		$image_url = _tccc_media_image($node);
	
		$output .= '<div class="audio-player" >';
		$output .= $image_url;
		$output .= '<audio class="html-audio-player" controls="controls" src="' . $url . '">';
		$output .= '<source src="'.$url.'" type="audio/mp3" />';
		$output .= '<a href="'.$url.'" id="player"></a>';

		$output .= '</audio>';
		$output .= '</div>';
				
		$output .= '<div id="video-audio-switch">';
    $output .= '<a href="#" class="pause audio-toggle"></a>';
    $output .= '<a href="#" class="video-toggle"></a>';
		$output .= '</div>';

  }
  
  foreach (field_get_items('node', $node, 'field_notes_file') as $item) {
    $output .= l('Notes', file_create_url($item['uri']), array('attributes' => array('class' => array('notes'))));
  }
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_sermon_multimedia_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_sermon_multimedia_content_type_admin_title($subtype, $conf, $context) {
  return 'Sermon multimedia';
}
