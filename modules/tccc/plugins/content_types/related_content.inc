<?php

$plugin = array(
  'title' => 'Related Content',
  'category' => 'TCCC',
  'single' => TRUE,
  'required context' => new ctools_context_optional(t('Node'), 'node'),
);


function tccc_related_content_content_type_render($subtype, $conf, $args, $context) {
	if (empty($context) || empty($context->data)) {
	  return;
	}

  $output = '';

  $node = $context->data;
  $medias =array();
  
  foreach($conf['type'] as $type){
    if($type){
      $elements[$type] = _tccc_get_media($type);
    }
  }
  
  
  foreach($elements as $element){
    foreach($element as $media){
      $medias[] = $media; 
    }
  }
  
  
  // TODO: looks like this will produce duplicates if nodes match by more than one tag
  // TODO: ignore node if it is the same as this context's node
  
  if(!empty($node->field_tags)){
    if(!empty($medias)){
      
      foreach($medias as $media){
          foreach($media->field_tags['und'] as $tag){
            
            if($tag['tid'] == $node->field_tags['und'][0]['tid']){
              
              switch($media->type){
                
                case 'sermon':
                  $output .= _tccc_render_sermon_resource($media);
                  break;
                
                case 'book':
                  $output .= _tccc_render_book_resource($media);
                  break;
                  
                case 'website':
                  $output .= _tccc_render_website_resource($media);
                  break;
                
                case 'paper':
                  $output .= _tccc_render_paper_resource($media);
                  break;
                
                default:
                  break;
              }
              
            }
          }
          
      }
    }
  }
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function _tccc_render_sermon_resource($node) {
  $output = '';
  $output .= '<div class="sermon">';
  $output .= l($node->title, 'node/' . $node->nid);
  $output .= '</div>';
  return $output;
}


function _tccc_render_book_resource($node) {
  $output = '';
  $output .= '<div class="book">';
  $output .= _tccc_render_image('node', $node, 'field_image', 'thumbnail');
  $output .= '<div class="title">' . check_plain($node->title) . '</div>';
  $output .= drupal_render(field_view_field('node', $node, 'field_author_string', array('label' => 'hidden')));
  $output .= drupal_render(field_view_field('node', $node, 'field_summary', array('label' => 'hidden')));
  
  $links = field_get_items('node', $node, 'field_links');
  if (!empty($links)) {
    $str = array();
    foreach ($links as $item) {
      $str[] = drupal_render(field_view_value('node', $node, 'field_links', $item));
    }
    $output .= '<p class="links">';
    $output .= '<span>Available online: </span>';
    $output .= implode(' ', $str);
    $output .= '</p>';
  }
  
  $output .= '</div>';
  return $output;
}


function _tccc_render_paper_resource($node) {
  $output = '';
  $output .= '<div class="paper">';
  $output .= '<span class="caption">Paper:</span> ';
  $output .= l($node->title, 'node/' . $node->nid);
  $output .= '</div>';
  return $output;
}


function _tccc_render_website_resource($node) {
  $value = $node->field_url['und'][0]['value'];
  $full_value = (substr($value, 0, 7) === 'http://') ? $value : 'http://' . $value;
  $link = l($value, $full_value, array('external' => TRUE, 'absolute' => TRUE));
  
  $output = '';
  $output .= '<div class="website">';
  $output .= '<div class="title"><span>' . check_plain($node->title) . '</span> ' . $link . '</div>';
  $output .= drupal_render(field_view_field('node', $node, 'field_summary', array('label' => 'hidden')));
  $output .= '</div>';
  return $output;
}


function tccc_related_content_content_type_edit_form($form, &$form_state) {
  
  $node_types = node_type_get_types();
  $options = array('none' => 'None');
  
  foreach($node_types as $type => $info){
    $options[$type] = $info->name;
  }

  $form['type'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Display of types for Related content'),
   '#default_value' => $form_state['conf']['type'],
   '#options' => $options
  );
  
  return $form;
}


function tccc_related_content_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function tccc_related_content_content_type_admin_title($subtype, $conf, $context) {
  return 'Related Content';
}
