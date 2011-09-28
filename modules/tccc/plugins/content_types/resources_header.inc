<?php

$plugin = array(
  'title' => 'Resources Header',
  'category' => 'TCCC',
  'required context' => new ctools_context_optional(t('Resource Filter'), 'resource_filter'),
);


function tccc_resources_header_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context)) {
    return;
  }
  
  $filter = $context->data;

  $output = '';
  $output .= '<h1>Resource Library</h1>';
  $output .= '<ul id="topnav">';
  $output .= '<li>' . l('Latest', 'resources') . '</li>';
  
  $output .= '<li>';
  $output .= l('Sermons', 'resources/sermon/', array('attributes' => array('class' => array('item-sermons'))));
  $output .= '<ul class="subnav">';
  $output .= '<li>' . l('Date', 'resources/sermon/date') . '</li>';
  $output .= '<li>' . l('Speakers', 'resources/sermon/people') . '</li>';
  $output .= '<li>' . l('Series', 'resources/sermon/series') . '</li>';
  $output .= '<li>' . l('Topic', 'resources/sermon/tag') . '</li>';
  $output .= '<li>' . l('Scripture', 'resources/sermon/bible') . '</li>';
  $output .= '</ul>';
  $output .= '</li>';
  
  $output .= '<li>' . l('Papers', 'resources/paper') . '</li>';
  $output .= '<li>' . l('Music', 'resources/music') . '</li>';
  $output .= '<li class="last"></li>';
  $output .= '</ul>';
  
  $output .= '<div id="resources-sub-nav"></div>';
  
  $output .= theme('status_messages');
  $output .= drupal_render(menu_local_tabs());

  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_resources_header_content_type_edit_form($form, &$form_state) {
  return $form;
}


function tccc_resources_header_content_type_admin_title($subtype, $conf, $context) {
  return 'Resources Header';
}
