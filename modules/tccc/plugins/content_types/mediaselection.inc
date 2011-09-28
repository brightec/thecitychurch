<?php

$plugin = array(
  'title' => 'Media Selection',
  'category' => 'TCCC',
  'single' => TRUE,
);


function tccc_mediaselection_content_type_render($subtype, $conf, $args, $context) {

  $title = '';
  $output = '<h2>Media not recognised.<h2>';
  
  //First argument determines what to retrieve
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
      $result = TRUE;
      break;    
    default:
      $result = NULL;
      break;
    
  }
  
  //Second argument renders display for menu
  if($result){
    switch($args[1]){
      case 'series':
        $output = _tccc_series_selection($result, $args);
        $title = 'Series';
        break;
      case 'speaker':
        $output = _tccc_person_selection($result, $args);
        $title = 'Speakers';
        break;
      case 'artist':
        $output = _tccc_person_selection($result, $args);
        $title = 'Artist';
        break;
      case 'author':
        $output = _tccc_person_selection($result, $args);
        $title = 'Author';
        break;
      case 'topic':
        $output = _tccc_topic_selection($result, $args);
        $title = 'Topics';
        break;
      case 'scripture':
        $output = _tccc_scripture_selection($result, $args);
        $title = 'Scripture';
        break;
      case 'date':
        $output = _tccc_date_selection($result, $args);
        $title = 'Dates';        
        break;
      case 'sermons':
        if ($args[0] == 'recommended'){
          $result = _tccc_get_media('sermon', 0, TRUE);             
          $output = _tccc_rec_media_selection($result);
          $title  = 'Recommended Sermons';        
        }
        break;
      case 'papers':
        if ($args[0] == 'recommended'){
          $result = _tccc_get_media('paper', 0, TRUE);    
          $output = _tccc_rec_media_selection($result);
          $title  = 'Recommended Papers';        
          break;
        }
      case 'music':
        if ($args[0] == 'recommended'){
          $result = _tccc_get_media('music', 0, TRUE); 
          $output = _tccc_rec_media_selection($result);
          $title  = 'Recommended Music';        
          break;
        }
      case 'books':
        if ($args[0] == 'recommended'){
          $result = _tccc_get_media('book', 0, TRUE); 
          $output = _tccc_rec_media_selection($result);
          $title  = 'Recommended Books';        
          break;
        }
      case 'websites':
        if ($args[0] == 'recommended'){
          $result = _tccc_get_media('website', 0, TRUE); 
          $output = _tccc_rec_media_selection($result);
          $title  = 'Recommended Websites';        
          break;
        }
    }
    
  }
  
  $block = new stdClass;
  $block->title = $title;
  $block->content = $output;
  return $block;
}


function tccc_mediaselection_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_mediaselection_content_type_admin_title($subtype, $conf, $context) {
  return 'Media Selection';
}



// redirects to latest media
function _tccc_series_selection($medias, $args){

  $output = '';
  $all_series = array();

  if(isset($medias) && count($medias) > 0) {
    foreach($medias as $nid => $media) {
      if (!empty($media->field_media_series)){  
	$series = taxonomy_term_load($media->field_media_series['und'][0]['tid']);
	$all_series[$series->name][] = $series;	        
      }
    }
    $output .= theme('series', array('items'=> $all_series, 'args' => $args));   
  }

  return $output; 
}

// Displays menu for speaker/artist/author
function _tccc_person_selection($medias, $args){
  $output = '';
  $people = array();

  if(isset($medias) && count($medias) > 0) {
    foreach($medias as $nid => $media) {
      if (!empty($media->field_person)){  
        $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
        $people[$person->name][] = $person;	        
      }
    }
  }
  
  if($args[1] == 'speaker'){
    $output .= theme('speakers', array('items'=> $people));   
  } else {
    $output .= theme('people', array('items'=> $people, 'args' => $args));   
  }
  
  return $output; 
}


// Displays menu for topic
function _tccc_topic_selection($medias, $args){
      
      $output = '';

      $elements = array();
      // Build array of medias grouped by month/year	
      if(isset($medias) && count($medias) > 0) {
        
        
        foreach($medias as $mid => $media) {	
        
          if(!empty($media->field_tags)){
            foreach($media->field_tags['und'] as $tag){        
              $topic = taxonomy_term_load($tag['tid']);
              $element = new stdClass();
              $element->nid = $mid;			
              $element->title = filter_xss($media->title);
              $element->path = $media->vid;
              $elements[$topic->name][] = $element;
            }
          }
        }
      }

      $output .= theme('topics', array('items'=> $elements));   
      
      return $output;
}


// Displays menu for scripture
function _tccc_scripture_selection($medias, $args){

  $output = '';

  $elements = array();
  // Build array of medias grouped by month/year	
  if(isset($medias) && count($medias) > 0) {

    foreach($medias as $sid => $media) {	

      if (!empty($media->field_bible_references)){      
	$ref = $media->field_bible_references['und'][0]['safe_value'];

	$book = _tccc_parse_book($ref);         

	// If year filter argument is present then filter out years that dont match year param
	$element = new stdClass();
	$element->nid = $sid;			
	$element->biblebook = $book;
	$element->title = filter_xss($media->title);
	$element->path = 'resources/' . $args[0] . '/scripture/'. drupal_clean_css_identifier($book);

	$elements[$element->biblebook][] = $element;
      }
    }
  }
  $output .= theme( 'bible', array('item'=> $elements));  

  return $output;  
} 

// Displays menu for dates
function _tccc_date_selection($medias, $args){
  $output = '';
  $elements = array();
  
  // Build array of medias grouped by month/year	
  if(isset($medias) && count($medias) > 0) {

    foreach($medias as $mid => $media) {	

      $y = date('Y', strtotime($media->field_recording_date['und']['0']['value']));			
      $m = date('n', strtotime($media->field_recording_date['und']['0']['value']));

      $full = date('F Y', strtotime($media->field_recording_date['und']['0']['value']));

      // If year filter argument is present then filter out years that dont match year param

      $element = new stdClass();
      $element->nid = $mid;			
      $element->date = filter_xss(date('jS l', strtotime($media->field_recording_date['und']['0']['value'])));
      $element->title = filter_xss($media->title);
      $element->path = 'resources/' . $args[0] . '/date/' . $y . '/' . $m;

      $elements[$full][] = $element;
    }
  }

  $output .= theme( 'dates', array('items'=> $elements));  
  return $output;  
}

/**
 * Functions for retrieving recommended resources
 */
function _tccc_rec_media_selection($medias, $title){
  $output = '';
  
  foreach($medias as $sid => $media) {
    $person = taxonomy_term_load($media->field_person['und'][0]['tid']);
    $output .= theme( 'media', array('item'=> $media, 'person' => $person));                   
  }
  return $output;
  
}

function _tccc_rec_papers_selection(){
  return 'HI papers';
  
}

function _tccc_rec_music_selection(){
  return 'HI music';
  
}