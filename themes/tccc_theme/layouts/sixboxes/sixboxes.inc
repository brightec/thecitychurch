<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_theme_sixboxes_panels_layouts() {
  $items['sixboxes'] = array(
    'title' => t('6 boxes mini panel layout'),
    'category' => t('TCCC'),
    'icon' => 'sixboxes.png',
    'theme' => 'sixboxes',
    'regions' => array(
      'box_1' => t('Box 1'),
      'box_2' => t('Box 2'),
      'box_3' => t('Box 3'),
      'box_4' => t('Box 4'),
      'box_5' => t('Box 5'),
      'box_6' => t('Box 6'),
    ),
  );
  return $items;
}
