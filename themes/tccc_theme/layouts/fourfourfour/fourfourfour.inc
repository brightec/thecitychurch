<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_fourfourfour_panels_layouts() {
  $items['fourfourfour'] = array(
    'title' => t('4/4/4 layout with wide area at top'),
    'category' => t('TCCC'),
    'icon' => 'fourfourfour.png',
    'theme' => 'fourfourfour',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'column-1' => t('Column 1'),
      'column-2' => t('Column 2'),
      'column-3' => t('Column 3'),
    ),
  );
  return $items;
}
