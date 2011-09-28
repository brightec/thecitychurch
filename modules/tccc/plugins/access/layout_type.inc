<?php

/**
 * @file
 * Plugin to provide access control based upon node type.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Taxonomy: Layout"),
  'description' => t('Control access by taxonomy layout.'),
  'callback' => 'ctools_layout_type_ctools_access_check',
  'default' => array('layout' => array()),
  'settings form' => 'ctools_layout_type_ctools_access_settings',
  'settings form submit' => 'ctools_layout_type_ctools_access_settings_submit',
  'summary' => 'ctools_layout_type_ctools_access_summary',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'restrictions' => 'ctools_layout_type_ctools_access_restrictions',
);

/**
 * Settings form for the 'by node_type' access plugin
 */
function ctools_layout_type_ctools_access_settings($form, &$form_state, $conf) {
  
  $layouts = taxonomy_get_tree(6);
  
  foreach ($layouts as $delta => $layout){
    $name = $layout->name;
    $options[$layout->tid] = check_plain($layout->name);
  }  
  
  $form['settings']['layout'] = array(
    '#title' => t('Layout type'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#description' => t('Only the checked layouts will be valid.'),
    '#default_value' => $conf['layout'],
  );
  return $form;
}

/**
 * Compress the node_types allowed to the minimum.
 */
function ctools_layout_type_ctools_access_settings_submit($form, &$form_state) {
  $form_state['values']['settings']['layout'] = array_filter($form_state['values']['settings']['layout']);
}

/**
 * Check for access.
 */
function ctools_layout_type_ctools_access_check($conf, $context) {
  // As far as I know there should always be a context at this point, but this
  // is safe.
  if (empty($context) || empty($context->data) || empty($context->data->field_layout['und'][0]['tid'])) {
    return FALSE;
  }
  

  if (array_filter($conf['layout']) && empty($conf['layout'][$context->data->field_layout['und'][0]['tid']])) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Inform the UI that we've eliminated a bunch of possibilities for this
 * context.
 */
function ctools_layout_type_ctools_access_restrictions($conf, &$context) {

  if (isset($context->restrictions['layout'])) {
    $context->restrictions['layout'] = array_unique(array_merge($context->restrictions['layout'], array_keys(array_filter($conf['layout']))));
  }
  else {
    $context->restrictions['layout'] = array_keys(array_filter($conf['layout']));
  }
}

/**
 * Provide a summary description based upon the checked node_types.
 */
function ctools_layout_type_ctools_access_summary($conf, $context) {
    
  if (!isset($conf['layout'])) {
    $conf['layout'] = array();
  }
  
  $layouts = array();
  $elements = taxonomy_get_tree(6);
  foreach($elements as $element){
    $layouts[$element->tid] = $element;
  }
    
  $names = array();
  
  // If a node type doesn't exist, let the user know, but prevent a notice.
  $missing_layouts = array();

  foreach (array_filter($conf['layout']) as $layout){
    if (!empty($layouts[$layout])) {
      $names[] = check_plain($layouts[$layout]->name);
    }
    else {
      $missing_layouts[] = check_plain($layout);
    }
  }

  if (empty($names) && empty($missing_layouts)) {
    return t('@identifier is any layout ADDED THIS type', array('@identifier' => $context->identifier));
  }

  if (!empty($missing_layouts)) {
    $output = array();
    if (!empty($names)) {
      $output[] = format_plural(count($names), '@identifier is layout "@layouts"', '@identifier layout is one of "@layouts"', array('@layouts' => implode(', ', $names), '@identifier' => $context->identifier));
    }
    $output[] = format_plural(count($missing_layouts), 'Missing/ deleted layout "@layouts"', 'Missing/ deleted layout is one of "@layouts"', array('@layouts' => implode(', ', $missing_layouts)));
    return implode(' | ', $output);
  }

  return format_plural(count($names), '@identifier is layout "@layouts"', '@identifier type is  one of "@layouts"', array('@layouts' => implode(', ', $names), '@identifier' => $context->identifier));
}

