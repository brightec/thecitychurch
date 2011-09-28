<?php

$plugin = array(
  'title' => t('Media filter'),
  'context' => 'tccc_context_create_media_filter',
  'keyword' => 'media_filter',
  'no ui' => TRUE,
  'context name' => 'tccc_media_filter',
  'convert list' => 'tccc_context_media_filter_convert_list',
  'convert' => 'tccc_context_media_filter_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the string for this context.'),
  ),
);

function tccc_context_create_media_filter($empty, $data = NULL, $conf = FALSE) {

  // The input is expected to be an object as created by ctools_break_phrase
  // which contains a group of string.
  $context = new ctools_context('tccc_media_filter');
  $context->plugin = 'media_filter';

  if ($empty) {
    return $context;
  }

  $tokens = explode('/', $data);
  $result = new tccc_media_filter;

  if (empty($tokens)) {
    return;
  }
  
  if ($tokens[0] == 'sermons') {
    $result->bundle = 'sermon';
  }
  
  if ($data !== FALSE) {
    $context->data = $result;
    $context->title = check_plain($data);
    return $context;
  }
}

/**
 * Provide a list of sub-keywords.
 *
 * This is used to provide keywords from the context for use in a content type,
 * pane, etc.
 */
function tccc_context_media_filter_convert_list() {
  return array(
    'type' => t('Type'),
  );
}

/**
 * Convert a context into a string to be used as a keyword by content types, etc.
 */
function tccc_context_media_filter_convert($context, $type) {
  switch ($type) {
    case 'type':
      return $context->data->bundle;
  }
}

