<?php

$plugin = array(
  'title' => t('Standard Header'),
  'category' => t('TCCC'),
  'single' => TRUE,
  'required context' => new ctools_context_optional(t('Node'), 'node'),
);


function tccc_standard_header_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context)) {
    return;
  }

  $node = $context->data;

  // header text might be custom, otherwise get it from the node

  if ($conf['html']) {
    $header_text = ctools_context_keyword_substitute($conf['html'], array(), array($context));
  } else if ($node) {
    $header_text = check_plain($node->title);
  } else {
    return;
  }

  $output = '';
  $output .= '<h1>' . $header_text . '</h1>';
  
  $subtitle = field_get_items('node', $node, 'field_subtitle');
  if (!empty($subtitle)) {
    $output .= '<h2>' . $subtitle[0]['safe_value'] . '</h2>';
  }
  
  $output .= theme('status_messages');
  $output .= drupal_render(menu_local_tabs());
  $output .= '<div style="clear: both"></div>';

  $block = new stdClass();
  $block->content = $output;
  return $block;
}


function tccc_standard_header_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['html'] = array(
    '#type' => 'textfield',
    '#title' => t('HTML'),
    '#size' => 50,
    '#description' => t('The HTML to include within the H1 tag. Substitutions are allowed.'),
    '#default_value' => !empty($conf['html']) ? $conf['html'] : '',
    '#prefix' => '<div class="clear-block no-float">',
    '#suffix' => '</div>',
  );
  return $form;
}


function tccc_standard_header_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array('html') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}


function tccc_standard_header_content_type_admin_title($subtype, $conf, $context) {
  if ($context->identifier) {
    return t('Standard header based on "@s"', array('@s' => $context->identifier));
  } else {
    return 'Standard header not based on node';
  }
}
