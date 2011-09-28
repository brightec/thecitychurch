<?php

/*
 * Include file for database call functions
 */


class tccc_media_filter {
  
  var $bundle;
  var $type;
  
  function load_nodes() {
    return _tccc_get_media($this->bundle);
  }
  
}



function _tccc_get_media($media = 'sermon', $limit = 0, $rec = false){

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', $media);
  $query->propertyCondition('status', 1);
  $query->fieldOrderBy('field_recording_date', 'value', 'DESC');
  
  if ($rec){
    $query->fieldCondition('field_recommended', 'value', 1,'=');
  }
  
  if ($limit != 0){
    $query->range(0, $limit);
  }
    
  $result = $query->execute();
  return $medias = node_load_multiple(array_keys($result['node']));  
}

function _tccc_get_promoted_events($limit = 0){

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'event');
  $query->propertyCondition('status', 1);
  $query->fieldOrderBy('field_event_date', 'value', 'ASC');

  
  if ($limit != 0){
    $query->range(0, $limit);
  }
    
  return $result = $query->execute();
}
