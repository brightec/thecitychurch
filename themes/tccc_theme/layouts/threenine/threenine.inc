<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_threenine_panels_layouts() {
  $items['threenine'] = array(
    'title' => t('3/9 layout with wide area at top & bottom'),
    'category' => t('TCCC'),
    'icon' => 'threenine.png',
    'theme' => 'threenine',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'wide-bottom' => t('Wide Bottom'),
    ),
  );
  return $items;
}
