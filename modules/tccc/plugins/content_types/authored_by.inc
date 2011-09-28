<?php

$plugin = array(
  'title' => t('Authored By'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Author'), 'taxonomy_term'),
  'category' => t('TCCC'),
);


function tccc_authored_by_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $person = $context->data;
  
  $output = '';
  $output .= _tccc_render_image('taxonomy_term', $person, 'field_image', 'author_thumbnail', TRUE);
  $output .= '<div class="author-details">Article by<br/> ' . check_plain($person->name);
  $role = field_get_items('taxonomy_term', $person, 'field_subtitle');
  if (!empty($role)) {
    $output .= ',<br/> ' . $role[0]['safe_value'];
  }
  $output .= '</div>';
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_authored_by_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_authored_by_content_type_admin_title($subtype, $conf, $context) {
  return 'Authored by';
}
