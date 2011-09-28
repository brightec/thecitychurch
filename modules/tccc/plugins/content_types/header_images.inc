<?php

$plugin = array(
  'title' => 'Header Images',
  'category' => 'TCCC',
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),    
);


function tccc_header_images_content_type_render($subtype, $conf, $args, $context) {

  $output = '';
 
  $node = $context->data;
  
  $output .= '<div id="slideshow">';
  
  
 if($items = $node->field_slideshow_images['und']){
      foreach ($items as $delta => $item) {
        if ($fc = field_collection_field_get_entity($item)) {
  
            $link =  (!empty($fc->field_content_link)) ? $fc->field_content_link['und'][0]['value'] : '';
            $image =  $fc->field_slideshow_image['und'][0];
            
            $output .= '<a tell="" href="' . $link . '">';
            $output .= theme('image_style', array('path' => $image['uri'], 'alt' => $image['alt'], 'style_name' => 'header_image'));
            $output .= '</a>';          

        }
      }
    
  }  
  
  
  
  
//  if (!empty($node->field_banner_image)){
//    foreach($node->field_banner_image['und'] as $image){
//      $output .= '<a href="' . $image['title'] . '">';
//      $output .= theme('image_style', array('path' => $image['uri'], 'style_name' => 'header_image'));
//      $output .= '</a>';
//    }
//  }
  
  $output .= '</div>';
  $output .= '<div id="slide-nav"></div>';
  
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_header_images_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_header_images_content_type_admin_title($subtype, $conf, $context) {
  return 'Header Images';
}
