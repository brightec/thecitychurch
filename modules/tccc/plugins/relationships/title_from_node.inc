<?php

$plugin = array(
  'title' => t("Title from node"),
  'keyword' => 'area',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'context' => 'tccc_title_from_node_context',
);

/**
 * Return a new context based on an existing context.
 */
function tccc_title_from_node_context($context = NULL, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data)) {
    return ctools_context_create_empty('string', NULL);
  }

  $node = $context->data;
  
  // use the node to determine what the area should be
  $area = 'foo'; 
  
  return ctools_context_create('string', $area);
}

