<?php

$plugin = array(
  'title' => 'Media Display',
  'category' => 'TCCC',
  'single' => TRUE,
);


function tccc_mediadisplay_content_type_render($subtype, $conf, $args, $context) {

  switch($args[0]){
    case 'sermons':
      $result = _tccc_get_media('sermon');          
      break;
    case 'papers':
      $result = _tccc_get_media('paper');    
      break;
    case 'music':
      $result = _tccc_get_media('music');    
      break;
    case 'recommended':
    case 'recommended':
      $sermons  = _tccc_get_media('sermon');    
      $papers   = _tccc_get_media('paper');    
      $music    = _tccc_get_media('music'); 
      $result   = array_merge($sermons, $papers, $music);
      break;
    default:
      $result = NULL;
      break;
  }
  
  $output = '';

  if($result){
    switch($args[1]){
      case 'series':
        $output = _tccc_series_display($result, $args);
        break;
      case 'speaker':
      case 'artist':
      case 'author':
        $output = _tccc_person_display($result, $args);
        break;
      case 'topic':
        $output = _tccc_topic_display($result, $args);
        break;
      case 'scripture':
        $output = _tccc_scripture_display($result, $args);
        break;
      case 'date':
        $output = _tccc_date_display($result, $args);
        break;
      default:
	$output = '<h2>Type not recognised</h2>';
    }
    
  } else {
    $output = '<h2>Media not recognised.</h2>';
  }
  
                               
  $block = new stdClass;
  $block->title = '';
  $block->content = $output;
  return $block;
}


function tccc_mediadisplay_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_mediadisplay_content_type_admin_title($subtype, $conf, $context) {
  return 'Media Display';
}

function _tccc_person_display($medias, $args){
 $output = '';
 $arg = taxonomy_term_load($args[2]);
  //if argument display list of book linked to argument      
 $s = $arg->tid;

 
  if (isset($medias)){

    foreach ($medias as $delta => $media) {

      if(!empty($media->field_person)){

        foreach($media->field_person['und'] as $speaker){
          if ($s == $speaker['tid']){
            $output .= theme( 'media', array('item'=> $media, 'person' => $arg, 'section' => $args[0]));                   
          }
        }
      }

    }
  }

  return $output;
}


function _tccc_topic_display($medias, $args){
  $output = '';
  $arg = taxonomy_get_term_by_name($args[2]);
  //if argument display list of book linked to argument      
  $t = key($arg);

  if (isset($medias)) {

    foreach ($medias as $delta => $media) {
      if(!empty($media->field_tags)){
        foreach($media->field_tags['und'] as $tag){
          if ($t == $tag['tid']){
      $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
            $output .= theme( 'media', array('item'=> $media, 'person' => $person, 'section' => $args[0]));                                   
          }
        }
      }
    }
  }
  
  return $output;
}

function _tccc_series_display($medias, $args){
  
  $output = '';
  $arg = taxonomy_term_load($args[2]);
  //if argument display list of book linked to argument      
  $t = $arg->tid;

  if (isset($medias)) {

    foreach ($medias as $delta => $media) {
      if(!empty($media->field_media_series)){
        foreach($media->field_media_series['und'] as $tag){
          if ($t == $tag['tid']){
      $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
            $output .= theme( 'media', array('item'=> $media, 'person' => $person, 'section' => $args[0]));                                   
          }
        }
      }
    }
  }
  
  return $output;
}



function _tccc_scripture_display($medias, $args){
  
  $output = '';
  $book = $args[2];

  foreach($medias as $mid => $media){
    if(!empty($media->field_bible_references)){
        $ref = $media->field_bible_references['und'][0]['safe_value'];
        $ref = _tccc_parse_book($ref);
	
        $b = drupal_clean_css_identifier($ref);

      if($book == $b){
	      $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
              $output .= theme( 'media', array('item'=> $media, 'person' => $person, 'section' => $args[0]));                   
      } 
    } 
  }        
  return $output;  
} 


function _tccc_date_display($medias, $args){
  $output = '';
  
  foreach($medias as $sid => $media){
    $y = date('Y', strtotime($media->field_recording_date['und']['0']['value']));			
    $m = date('n', strtotime($media->field_recording_date['und']['0']['value']));    
    
    $year = explode('/', $args[2] );
    $year = $year[0];
      
    if ($year == $y && $args[3] == $m){
      $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
      $output .= theme( 'media', array('item'=> $media, 'person' => $person, 'section' => $args[0]));                   
    } 
  }    
  return $output;  
}