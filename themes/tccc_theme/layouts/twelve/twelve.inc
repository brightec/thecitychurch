<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_twelve_panels_layouts() {
  $items['twelve'] = array(
    'title' => t('12 layout with wide area at top'),
    'category' => t('TCCC'),
    'icon' => 'twelve.png',
    'theme' => 'twelve',
    'regions' => array(
      'wide' => t('Wide Top'),
      'heading' => t('Heading'),
      'main' => t('Main'),
    ),
  );
  return $items;
}
