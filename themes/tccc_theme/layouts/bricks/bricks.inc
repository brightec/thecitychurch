<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_bricks_panels_layouts() {
  $items['bricks'] = array(
    'title' => t('Bricked layout with wide area at top and bottom'),
    'category' => t('TCCC'),
    'icon' => 'bricks.png',
    'theme' => 'bricks',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'above-left' => t('Left Above'),
      'above-right' => t('Right Above'),
      'middle-left' => t('Left Middle'),
      'middle-right' => t('Right Middle'),
      'lower-left' => t('Left Lower'),
      'lower-right' => t('Right Lower'),
      'wide-bottom' => t('Wide Bottom'),
    ),
  );
  return $items;
}
