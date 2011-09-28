<?php

$plugin = array(
  'title' => t('Media item tags'),
  'category' => t('TCCC'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
);


function tccc_media_tags_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $node = $context->data;

  $output = '';
  
  $tags = field_get_items('node', $node, 'field_tags');
  $tids = array();
  foreach ($tags as $tag) {
    $tids[] = $tag['tid'];
  }
  $terms = taxonomy_term_load_multiple($tids);
  
  $links = array();
  foreach ($terms as $term) {
    $links[] = l($term->name, 'resources/sermons/tag/' . $term->tid);
  }

  $block = new stdClass();
  $block->title = 'Tags';
  $block->content = implode(' ', $links);
  return $block;
}


function tccc_media_tags_content_type_admin_title($subtype, $conf, $context) {
  return t('Media item tags based on "@s"', array('@s' => $context->identifier));
}
