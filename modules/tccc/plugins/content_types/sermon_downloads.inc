<?php

$plugin = array(
  'title' => 'Sermon downloads',
  'category' => 'TCCC',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);


function tccc_sermon_downloads_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $node = $context->data;
  $output = '';
  
  $output .= '<span class="caption">Downloads</span>';
  
  foreach (field_get_items('node', $node, 'field_vimeo_id') as $item) {
    $output .= l('Vimeo', 'http://vimeo.com/' . $item['safe_value'], array('attributes' => array('class' => 'vimeo')));
  }
  
  foreach (field_get_items('node', $node, 'field_audio_file') as $item) {
    $output .= l('Audio only', file_create_url($item['uri']), array('attributes' => array('class' => array('audio'))));
  }
  
  foreach (field_get_items('node', $node, 'field_notes_file') as $item) {
    $output .= l('Notes', file_create_url($item['uri']), array('attributes' => array('class' => array('notes'))));
  }
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_sermon_downloads_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_sermon_downloads_content_type_admin_title($subtype, $conf, $context) {
  return 'Sermon downloads';
}

