<?php

$plugin = array(
  'title' => t('Fixed site area'),
  'context' => 'tccc_context_create_fixed_area',
  'keyword' => 'area',
  'no ui' => TRUE,
  'context name' => 'string',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the string for this context.'),
  ),
);

function tccc_context_create_fixed_area($empty, $data = NULL, $conf = FALSE) {
  
  // The input is expected to be an object as created by ctools_break_phrase
  // which contains a group of string.
  $context = new ctools_context('string');
  $context->plugin = 'tccc_fixed_area';

  if ($empty) {
    return $context;
  }

  $context->data = 'fixed';
  return $context;
}

