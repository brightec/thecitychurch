<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_discipleshiplanding_panels_layouts() {
  $items['discipleshiplanding'] = array(
    'title' => t('Discipleship landing'),
    'category' => t('TCCC'),
    'theme' => 'discipleshiplanding',
    'regions' => array(
      'main' => t('Main'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}
