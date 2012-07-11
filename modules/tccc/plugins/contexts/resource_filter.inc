<?php

$plugin = array(
  'title' => t('Resource filter'),
  'context' => 'tccc_context_create_resource_filter',
  'keyword' => 'resource_filter',
  'no ui' => TRUE,
  'context name' => 'resource_filter',
  'convert list' => 'tccc_context_resource_filter_convert_list',
  'convert' => 'tccc_context_resource_filter_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the string for this context.'),
  ),
);

function tccc_context_create_resource_filter($empty, $data = NULL, $conf = FALSE) {

  // The input is expected to be an object as created by ctools_break_phrase
  // which contains a group of string.
  $context = new ctools_context('resource_filter');
  $context->plugin = 'resource_filter';

  if ($empty) {
    return $context;
  }

  if ($data !== FALSE) { 
    $context->data = $data;  
    $context->title = t('Resource filter');

    return $context;
  }
}

/**
 * Provide a list of sub-keywords.
 *
 * This is used to provide keywords from the context for use in a content type,
 * pane, etc.
 */
function tccc_context_resource_filter_convert_list() {
  return array(
    'date' => t('Date'),
    'type' => t('Type'),
    'tag' => t('Tag'),
    'series' => t('Series'),
    'person' => t('Person'),
    'bible' => t('Bible'),
    'nid' => t('Dummy node ID'),
    'sites' => t('Site'),

  );
}

/**
 * Convert a context into a string to be used as a keyword by content types, etc.
 */
function tccc_context_resource_filter_convert($context, $type) {

  switch ($type) {
    case 'date':
      return isset($context->data->date) ? $context->data->date : 'all';
    case 'type':
      return isset($context->data->bundle) ? $context->data->bundle : 'all';
    case 'tag':
      return isset($context->data->tag) ? $context->data->tag : 'all';
    case 'series':
      return isset($context->data->series) ? $context->data->series : 'all';
    case 'person':
      return isset($context->data->person) ? $context->data->person : 'all';
    case 'bible':
      return isset($context->data->bible) ? $context->data->bible : 'all';
    case 'nid':
      return isset($context->data->nid) ? $context->data->nid : NULL;
    case 'sites':
      return isset($context->data->sites) ? $context->data->sites : 'all';  
    default: 
      return 'all';
    break; 
  }
}

