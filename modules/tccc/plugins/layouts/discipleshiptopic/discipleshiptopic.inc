<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_discipleshiptopic_panels_layouts() {
  $items['discipleshiptopic'] = array(
    'title' => t('Discipleship topic'),
    'category' => t('TCCC'),
    'theme' => 'discipleshiptopic',
    'regions' => array(
      'header' => t('Header'),
      'content-left' => t('Content (Left)'),
  		'content-right' => t('Content (Right)'),
      'resources' => t('Resources'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}
