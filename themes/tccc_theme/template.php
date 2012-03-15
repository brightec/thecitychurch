<?php


function tccc_theme_preprocess_html(&$variables) {

  if (module_exists('panels') && function_exists('panels_get_current_page_display')) {
    if ($pd = panels_get_current_page_display()) {
      foreach ($pd->context as $context) {
        
        // if there is an area defined, use that
        if ($context->type == 'string' && $context->keyword == 'area') {
          $variables['classes_array'][] = 'area-' . $context->data;
        }
        
      }
    }
  }
  
}


function tccc_theme_preprocess_page(&$variables) {
  
  if (module_exists('panels') && function_exists('panels_get_current_page_display')) {
    $pd = panels_get_current_page_display();
    if ($pd) {
      foreach ($pd->content as $pane) {
                
        if (($pane->type == 'page_tabs') && $pane->shown) {
          $variables['tabs'] = '';          
        }
        
        if (($pane->type == 'standard_header') && $pane->shown) {
          $variables['title'] = '';
          $variables['tabs'] = '';
          $variables['show_messages'] = FALSE;
        }

        if (($pane->type == 'resources_header') && $pane->shown) {
          $variables['title'] = '';
          $variables['tabs'] = '';
          $variables['show_messages'] = FALSE;
        }
      }
    }
  }

}


/**
 * Returns HTML for a menu link and submenu.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @ingroup themeable
 */
function tccc_theme_menu_link(array $variables) {
  
  $element = $variables['element'];
  $output = '';
  $sub_menu = '';
  
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  
  
  //If dummy output different markup 
  if($element['#href'] == 'dummy'){
    $output .= '<div class="category-link">' . $element['#title'] . '</div>';
  }
  
  elseif($element['#href'] == 'column'){
    
    $element['#attributes']['class'][] = 'column';
    $output .= '';
        
  }
  
  else {
    $output .= l($element['#title'], $element['#href'], $element['#localized_options']);    

    if($element['#original_link']['depth'] == 1){
      $output .= '<div class="arrow-pointer"></div>';
    }    
    
  }
  
  
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
