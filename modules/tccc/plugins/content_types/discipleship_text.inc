<?php

$plugin = array(
  'title' => 'Discipleship topic - main text',
  'category' => 'TCCC',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);


function tccc_discipleship_text_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }
  
  $node = $context->data;
  
  $output = '';
  $output .= drupal_render(field_view_field('node', $node, 'field_summary', array('label' => 'hidden')));
  $output .= '<a href="#" class="more">Read more</a>';
  $output .= drupal_render(field_view_field('node', $node, 'field_main_text', array('label' => 'hidden')));
  
  $block = new stdClass;
  $block->content = $output;
  return $block;
}


function tccc_discipleship_text_content_type_edit_form($form, &$form_state) {
  return $form;
}


function tccc_discipleship_text_content_type_admin_title($subtype, $conf, $context) {
  return 'Discipleship topic - main text';
}
