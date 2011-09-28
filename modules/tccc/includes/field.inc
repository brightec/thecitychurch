<?php


/**
 * Implements hook_field_formatter_info().
 */
function tccc_field_formatter_info() {
  return array(
    'tccc_h2' => array(
      'label' => t('H2'),
      'field types' => array('text'),
    ),
    'tccc_vimeo' => array(
      'label' => t('Vimeo'),
      'field types' => array('text'),
    ),
  );
}


/**
 * Implements hook_field_formatter_view().
 */
function tccc_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {

    case 'tccc_h2':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#markup' => '<h2>' . $item['safe_value'] . '</h2>',
        );
      }
      break;
    
    case 'tccc_vimeo':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'vimeo',
          '#id' => $item['safe_value'],
        );
      }
      break;
      
  }
  return $element;
}
