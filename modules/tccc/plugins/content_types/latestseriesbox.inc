<?php

$plugin = array(
  'title' => 'Latest Series Box',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_latestseriesbox_content_type_render($subtype, $conf, $args, $context) {

  // to find the latest series, we traverse backwards through the sermons
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'sermon');
  $query->propertyCondition('status', 1);
  $query->fieldCondition('field_media_series', 'tid', 0, '>');
  $query->fieldOrderBy('field_recording_date', 'value', 'DESC');
  $query->range(0, 1);
  $result = $query->execute();
  $sermons = node_load_multiple(array_keys($result['node']));
  
  foreach ($sermons as $sermon) {
    foreach (field_get_items('node', $sermon, 'field_media_series') as $item) {
      $series = taxonomy_term_load($item['tid']);
      $img = _tccc_render_image('taxonomy_term', $series, 'field_video_image', 'resources_feature');
    }
  }
  
  $path = 'resources/sermon/series/' . $series->tid;
  $output = '';
  if ($img) {
    $img .= '<div class="shine-resource-button"></div>';
    $output .= l($img, $path, array('html' => TRUE, 'attributes' => array('class' => array('box-image'))));
  }

  $output .= '<div class="text">';
  $output .= l($series->name, $path) . '<br>';
  $output .= _tccc_latestseriesbox_date_range($series->tid);
  $output .= '<p>' . $series->description . '</p>';
  $output .= '</div>';
  
  $block = new stdClass;
  $block->title = 'Sermons';
  $block->content = $output;
  return $block;
}


// date range

function _tccc_latestseriesbox_date_range($series_tid) {
  
  $sql = 'select min(field_recording_date_value), max(field_recording_date_value) ' . 
    'from {field_data_field_recording_date} d, {field_data_field_media_series} s ' .
    'where d.entity_id=s.entity_id and s.field_media_series_tid = :series_tid';
  $query = db_query($sql, array('series_tid' => $series_tid));
  
  foreach ($query as $result) {
    $min_date = strtotime($result->min);
    $max_date = strtotime($result->max);
    if ($min_date && $max_date) {
      if (date('Y', $min_date) == date('Y', $max_date)) {
        return date('F', $min_date) . ' to ' . date('F Y', $max_date) . '<br>';
      } else {
        return date('F Y', $min_date) . ' to ' . date('F Y', $max_date) . '<br>';
      }
    }
  }
}


function tccc_latestseriesbox_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_latestseriesbox_content_type_admin_title($subtype, $conf, $context) {
  return 'Latest Series Box';
}


