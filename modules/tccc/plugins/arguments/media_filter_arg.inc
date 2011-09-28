<?php


$plugin = array(
  'title' => t("Media filter from arguments"),
  'keyword' => 'media_filter',
  // 'settings form' => 'simplecontext_arg_settings_form',
  'context' => 'tccc_media_filter_context_arg',
  // placeholder_form is used in panels preview, for example, so we can
  // preview without getting the arg from a URL
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the media filter argument'),
  ),
  'path placeholder' => '%pm_arg_tail',
);


function tccc_media_filter_context_arg($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('media_filter');
  }

  $context = ctools_context_create('media_filter', $arg);
  $context->original_argument = $arg;
  return $context;
}

