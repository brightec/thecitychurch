<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_foureight_panels_layouts() {
  $items['foureight'] = array(
    'title' => t('4/8 layout with wide area at top'),
    'category' => t('TCCC'),
    'icon' => 'foureight.png',
    'theme' => 'foureight',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'wide-bottom' => t('Wide Bottom'),
    ),
  );
  return $items;
}
