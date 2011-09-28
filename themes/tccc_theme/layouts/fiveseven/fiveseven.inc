<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_fiveseven_panels_layouts() {
  $items['fiveseven'] = array(
    'title' => t('5/7 layout with wide area at top'),
    'category' => t('TCCC'),
    'icon' => 'fiveseven.png',
    'theme' => 'fiveseven',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'wide-bottom' => t('Wide Bottom'),
    ),
  );
  return $items;
}
