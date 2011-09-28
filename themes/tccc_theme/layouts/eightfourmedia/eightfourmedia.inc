<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_eightfourmedia_panels_layouts() {
  $items['eightfourmedia'] = array(
    'title' => t('8/4 layout with wide area at top & bottom & bespoke media section'),
    'category' => t('TCCC'),
    'icon' => 'eightfourmedia.png',
    'theme' => 'eightfourmedia',
    'regions' => array(
      'wide-top' => t('Wide Top'),
      'media-section' => t('Media Section'),
      'left' => t('Left'),
      'right' => t('Right'),
      'wide-bottom' => t('Wide Bottom'),
    ),
  );
  return $items;
}
