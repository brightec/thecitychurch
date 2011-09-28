<?php

/**
 * Implementation of hook_panels_layouts().
 */
function tccc_rows_panels_layouts() {
  $items['rows'] = array(
    'title' => t('Full width rows'),
    'category' => t('TCCC'),
    'theme' => 'rows',
    'regions' => array(
      'row-1' => t('Row 1'),
      'row-2' => t('Row 2'),
      'row-3' => t('Row 3'),
      'row-4' => t('Row 4'),
      'row-5' => t('Row 5'),
      'row-6' => t('Row 6'),
      'row-7' => t('Row 7'),
      'row-8' => t('Row 8'),
    ),
  );
  return $items;
}
