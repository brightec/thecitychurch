<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_home_panels_layouts() {
  $items['home'] = array(
    'title' => t('Home'),
    'category' => t('TCCC'),
    'icon' => 'home.png',
    'theme' => 'home',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'column-1' => t('Column 1'),
      'column-2' => t('Column 2'),
      'column-3' => t('Column 3'),
    ),
  );
  return $items;
}
