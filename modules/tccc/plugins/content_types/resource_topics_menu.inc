<?php

$plugin = array(
  'title' => 'Resource topics menu',
  'category' => 'TCCC',
  'required context' => array(
    new ctools_context_optional(t('Topic'), 'taxonomy_term'),
    new ctools_context_optional(t('Media filter'), 'media_filter'),
  ),
);


function tccc_resource_topics_menu_content_type_render($subtype, $conf, $args, $contexts) {
  list($taxonomy_term_context, $media_filter_context) = $contexts;

  return;
  
  if (!empty($context)) {
    $selected_term = $context->data;
  }

  $v = _tccc_get_vocabulary_by_name('tags');
  $tree = taxonomy_get_tree($v->vid);
  
  $output = '';
  $output .= '<ul>';
  
  foreach ($tree as $term) {
    
    if ($term->tid == $selected_term->tid) {
      $output .= '<li><b>' . check_plain($term->name) . '</b></li>';
    } else {
      $output .= '<li>' . check_plain($term->name) . '</li>';
    }
    
  }
  
  $output .= '</ul>';
  

  $block = new stdClass;
  $block->title = t('Topics');
  $block->content = $output;
  return $block;
}
