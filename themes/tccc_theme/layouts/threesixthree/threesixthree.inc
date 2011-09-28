<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_threesixthree_panels_layouts() {
  $items['threesixthree'] = array(
    'title' => t('3/6/3 layout with wide area at top'),
    'category' => t('TCCC'),
    'icon' => 'threesixthree.png',
    'theme' => 'threesixthree',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'left-sidebar' => t('Left Sidebar'),
      'middle-column' => t('Middle Column'),
      'right-sidebar' => t('Right Sidebar'),
    ),
  );
  return $items;
}
