<?php


$plugin = array(
  'title' => t("Resource filter from arguments"),
  'keyword' => 'resource_filter',
  // 'settings form' => 'simplecontext_arg_settings_form',
  'context' => 'tccc_resource_filter_context_arg',
  // placeholder_form is used in panels preview, for example, so we can
  // preview without getting the arg from a URL
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the resource filter argument'),
  ),
  'path placeholder' => '%pm_arg_tail',
);


function tccc_resource_filter_context_arg($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('resource_filter');
  }

  $tokens = explode('/', $arg);
  $result = new tccc_media_filter;

  if (empty($tokens)) {
    return ctools_context_create_empty('resource_filter');
  }

  // token 0 is always the node type
  if ($tokens[0] == 'sermon') {
    $result->bundle = 'sermon';
  } else if ($tokens[0] == 'paper') {
    $result->bundle = 'paper';
  } else if ($tokens[0] == 'music') {
    $result->bundle = 'music';
  } else {
    $result->nid = -1;
  }

  // token 1 describes what token 2 is
  // token 2 is a filtering value of some sort
  if (isset($tokens[1])) { 
    if ($tokens[1] == 'date') {
      $result->type = 'date';
      if (isset($tokens[2])) { $result->date = $tokens[2]; }

    } else if ($tokens[1] == 'tag') {
      
      $result->type = 'tag';
      if (isset($tokens[2])) { $result->tag = $tokens[2]; }

    } else if ($tokens[1] == 'series') {
      
      $result->type = 'series';
      if (isset($tokens[2])) { $result->series = $tokens[2]; }

    } else if ($tokens[1] == 'people') {

      $result->type = 'person';
      if (isset($tokens[2])) { $result->person = $tokens[2]; }

    } else if ($tokens[1] == 'bible') {

      $result->type = 'bible';
      if (isset($tokens[2])) { $result->bible = $tokens[2]; }

    }
  }

  // Sites - check if user has selected to view specific sites.
  $result->sites = isset($_POST['sites']) ? implode(',', $_POST['sites']) : NULL;
  // to make the view show no rows instead of all rows, pass in a non-existent nid here
  //if ($result->bundle == 'sermon' && empty($tokens[2])) {
  //  $result->nid = -1;
  //}
  

  $context = ctools_context_create('resource_filter', $result);
  $context->original_argument = $arg;

  return $context;
}

