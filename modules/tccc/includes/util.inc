<?php


/* for functions that can one day go into a generic module */


function _tccc_make_scale_and_crop_image_style($width, $height) {
  return array(
    'effects' => array(
      array(
        'name' => 'image_scale_and_crop',
        'data' => array('width' => $width, 'height' => $height),
        'weight' => 0,
      ),
    ),
  );
}

function _tccc_make_scale_image_style_height($height) {
  return array(
    'effects' => array(
      array(
        'name' => 'image_scale',
        'data' => array('height' => $height),
        'weight' => 0,
      ),
    ),
  );
}

function _tccc_make_scale_image_style_width($width) {
  return array(
    'effects' => array(
      array(
        'name' => 'image_scale',
        'data' => array('width' => $width),
        'weight' => 0,
      ),
    ),
  );
}

function _tccc_make_scale_image_style($width, $height) {
  return array(
    'effects' => array(
      array(
        'name' => 'image_scale',
        'data' => array('width' => $width, 'height' => $height),
        'weight' => 0,
      ),
    ),
  );
}


// utility function - shortcut for showing an image field with given style and no label

function _tccc_render_image($entity_type, $entity, $field_name, $image_style, $link = FALSE) {
  $formatter_settings = array();
  $formatter_settings['image_style'] = $image_style;
  if ($link) {
    $formatter_settings['image_link'] = 'content';
  }
  $display = array(
    'label' => 'hidden',
    'type' => 'image',
    'settings' => $formatter_settings,
  );
  
  return drupal_render(field_view_field($entity_type, $entity, $field_name, $display));
}



function _tccc_get_vocabulary_by_name($name) {
  foreach (taxonomy_get_vocabularies() as $v) {
    if ($v->machine_name == $name) {
      return $v;
    }
  }
}


function _tccc_linked_bible_references($entity_type, $entity, $field_name, $langcode = NULL) {
  foreach (field_get_items($entity_type, $entity, $field_name, $langcode) as $delta => $item) {
    $values[$delta] = l($item['value'], 'bible/' . drupal_encode_path($item['safe_value']));
  }
  return implode(', ', $values);
}
