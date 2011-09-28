<?php

$plugin = array(
  'title' => 'Topic Related Content',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_disc_topic_related_content_type_render($subtype, $conf, $args, $context) {
 
  $output = '';

  $node = node_load($args[0]);
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
  
  
  if(!empty($node->field_tags)){
    if(!empty($medias)){
      
      foreach($medias as $media){
          foreach($media->field_tags['und'] as $tag){
            
            if($tag['tid'] == $node->field_tags['und'][0]['tid']){
              
              $output .= '<div class="media-item">';

              switch($media->type){
                
                case 'sermon':
                  $output .= l($media->title, 'node/' . $media->nid);
                  break;
                
                case 'book':

                  $image = !empty($media->field_video_image) ? theme('image_style', array('path' => $media->field_video_image['und'][0]['uri'], 'style_name' => 'thumbnail')) : '';
                  
                  $output .= $image;
                  $output .= '<span>' . check_plain($media->title) . '</span><br>';
                  $output .= drupal_render(field_view_field('node', $media, 'field_summary', array('label' => 'hidden')));
                  $output .= ' <span>Available online: </span>';                  
                  
                  if(!empty($media->field_online_links)){
                    
                    $links = array();
                    
                    foreach($media->field_online_links['und'] as $l){
                      $links[] = l($l['title'], $l['text'], array('attributes' => array('target' => '_blank'))) . ' ';
                    }
                    
                    $output .= implode(' ', $links);
                    
                  }         
                  
                  break;
                  
                case 'website':
                  $output .= '<span>' . check_plain($media->title) . l($media->field_url['und'][0]['value'], $media->field_url['und'][0]['value']) . '</span><br>';
                  $output .= drupal_render(field_view_field('node', $media, 'field_summary', array('label' => 'hidden')));
                  break;
                
                case 'paper':
                  $output .= '<span>Paper:</span> ';
                  $output .= l($media->title, 'node/' . $media->nid);
                  $output .= ' (PDF)';
                  break;
                
                default:
                  break;
              }
              
              $output .= '</div>';
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


function tccc_disc_topic_related_content_type_edit_form($form, &$form_state) {
  
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


function tccc_disc_topic_related_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function tccc_disc_topic_related_content_type_admin_title($subtype, $conf, $context) {
  return 'Topic Related Content';
}
