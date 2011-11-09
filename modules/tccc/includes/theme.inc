<?php

/*
 * The theming functions for the TCCC module
 */

/**
  * Implements hook_theme().
  */
function tccc_theme() {
  return array(
    'media' => array (
      'variables' => array('item' => NULL, 'person' => NULL, 'section' => NULL),
    ),
    'bible' => array (
      'variables' => array('item' => NULL),
    ),
    'dates' => array (
      'variables' => array('items' => NULL),
    ),
    'topics' => array (
      'variables' => array('items' => NULL),
    ),
    'speakers' => array (
      'variables' => array('items' => NULL),
    ),
    'series' => array (
      'variables' => array('items' => NULL, 'args' => NULL),
    ),
    'people' => array (
      'variables' => array('items' => NULL, 'args' => NULL),
    ),
    'event' => array (
      'variables' => array('event' => NULL),
    ),
    'vimeo' => array(
      'variables' => array('id' => NULL),
    ),
  );
}

function theme_speakers($variables) {
	$output = '';
	$items = $variables['items'];
	if(count($items) > 0) {
	  $output = '<div class="speakers">';
	  
	  $home = array();
	  $guests = array();
	  
	  foreach($items as $name => $speakers){
	    $parents = taxonomy_get_parents($speakers[0]->tid);
	    
	    foreach($parents as $parent){
	      if ($parent->name == "Guest"){
		$guests[] = $speakers[0];
	      } elseif ($parent->name == "Home") {
		$home[] = $speakers[0];
	      }
	    }
	    
	  }
	  
	  if(!empty($home)){
	    $output .= '<ul>';
	    foreach($home as $speaker){
	      $output .= '<li>' . l($speaker->name, 'resources/sermons/speaker/' . $speaker->tid) . '</li>';
	    }  
	    $output .= '</ul>';
	    
	  }
	  
	  if(!empty($guests)){
	    $output .= '<h3>Guest speakers</h3>';
	    $output .= '<ul>';
	    foreach($guests as $speaker){
	      $output .= '<li>' . l($speaker->name, 'resources/sermons/speaker/' . $speaker->tid) . '</li>';
	    }  
	    $output .= '</ul>';
	  }
	    
	  $output .= '</div>';
	  }

	return $output;
}

function theme_people($variables) {
  $output = '';
  $items = $variables['items'];
  $args = $variables['args'];
  if(count($items) > 0) {
    $output = '<ul class="artists">';
    foreach($items as $name => $artists){
      $output .= '<li>' . l($artists[0]->name, 'resources/' . $args[0]. '/' . $args[1] . '/' . $artists[0]->tid) . '</li>';
    }
    $output .= '</ul>';
  }

  return $output;
}

function theme_series($variables) {
  $output = '';
  $items = $variables['items'];
  $args = $variables['args'];

  
  if(count($items) > 0) {
    
    $output = '<ul class="series">';
    foreach($items as $seriesname => $series){
      $output .= '<li>' . l($seriesname, 'resources/' . $args[0]. '/' . $args[1] . '/' . $series[0]->tid) . '</li>';
    }
    $output .= '</ul>';
    
  }
  return $output;
}

function theme_topics($variables) {
	$output = '';
	$items = $variables['items'];
	
	if(count($items) > 0) {
	  $output = '<div class="topics">';
		//$output .= '<h2>Upcoming Events</h2>';
		foreach($items as $topic => $medias) {
		  $output .= '<div class="topic">';
			$output .= '<h3>' . $topic . '</h3>';
			$output .= '<div class="topic-media">';
			  $output .= '<ul class="media">';
			foreach($medias as $media) {
				$output .= '<li>' . l($media->title, 'node/' . $media->path) . '</li>';
			}
				$output .= '</ul>';
			$output .= '</div>';
			$output .= '</div>';
		}
		$output .= '</div>';
	}

	return $output;
}

function theme_media($variables) {
  
  $output = '';
  $item = $variables['item'];
  $person = $variables['person'];
  $section = $variables['section'];
  

  if(count($item) > 0){

    $output = '<div class="media">';
    
    $output .= '<h2>' . l($item->title, 'node/' . $item->vid) . '</h2>';
    $output .= '<span class="name">' . $person->name . '</span>';
    $output .= !(empty($item->field_recording_date)) ? ' &#124; <span class="date">' . date('l jS F Y',strtotime($item->field_recording_date['und'][0]['value'])) . '</span>' : '';
    $output .= !(empty($item->field_media_length)) ? ' &#124; <span class="length">' . $item->field_media_length['und'][0]['value'] . '</span>' : ''; 
    
    if(!(empty($item->field_media_series))) {
      $series = taxonomy_term_load($item->field_media_series['und'][0]['tid']);
      $output .= ' &#124; <span class="series">' . $series->name . '</span>';
    }    
    
    $bible = _tccc_linked_bible_references('node', $item, 'field_scriptures');
    if (!empty($bible)) {
      $output .= ' &#124; <span class="bible">' . $bible . '</span>';
    }

    if (!empty($item->field_main_text)) {
      
      
      //display a word limit of 30
      $wordlimit = 30;
      
      //Clean, count & iterate
      $fulltext = strip_tags($item->field_main_text['und'][0]['value']);
      $fulltext = str_word_count($fulltext, 1, '0123456789,.');
      
      $text = array();
      foreach($fulltext as $delta => $word){
        $text[] = $word;
        if($delta == $wordlimit){
          break;
        }
      }
      
      $output .= '<p>';
      $output .= implode(' ', $text);
      $output .= '...</p>';
      
    }
    
    $output .= '</div>';
  }
  return $output;
}

function theme_bible($variables) {
  
  global $ot, $nt;

  $ot = array( 
  "Genesis",
  "Exodus",
  "Leviticus",
  "Numbers",
  "Deuteronomy",
  "Joshua",
  "Judges",
  "Ruth",
  "1 Samuel",
  "2 Samuel",
  "1 Kings",
  "2 Kings",
  "1 Chronicles",
  "2 Chronicles",
  "Ezra",
  "Nehemiah",
  "Esther",
  "Job",
  "Psalms",
  "Proverbs",
  "Ecclesiastes",
  "Song of Songs",
  "Isaiah",
  "Jeremiah",
  "Lamentations",
  "Ezekiel",
  "Daniel",
  "Hosea",
  "Joel",
  "Amos",
  "Obadiah",
  "Jonah",
  "Micah",
  "Nahum",
  "Habakkuk",
  "Zephaniah",
  "Haggai",
  "Zechariah",
  "Malachi",);

  $nt = array(
  "Matthew",
  "Mark",
  "Luke",
  "John",
  "Acts",
  "Romans",
  "1 Corinthians",
  "2 Corinthians",
  "Galatians",
  "Ephesians",
  "Philippians",
  "Colossians",
  "1 Thessalonians",
  "2 Thessalonians",
  "1 Timothy",
  "2 Timothy",
  "Titus",
  "Philemon ",
  "Hebrews",
  "James",
  "1 Peter",
  "2 Peter",
  "1 John",
  "2 John",
  "3 John",
  "Jude ",     
  );  
	$output = '';
	$items = $variables['item'];
	$ot_list = array();
	$nt_list = array();
  
	if(count($items) > 0) {
	  $output .= '<div class="bible">';

		foreach($items as $i => $sermons) {
      $book = _tccc_strtoproper($sermons[0]->biblebook);
      $link = l($sermons[0]->biblebook, $sermons[0]->path);
    
     if(in_array($book, $ot)){
       $ot_list[] = $link;
     }
     if(in_array($book, $nt)){
       $nt_list[] = $link;
     }
		}
    
    if(!empty($ot_list)){
      $output .= '<div class="ot">';
      $output .= '<h3>Old Testament</h3>';
      $output .= implode('<br>', $ot_list);
      $output .= '</div>';

    }
    if(!empty($nt_list)){
      $output .= '<div class="nt">';
      $output .= '<h3>New Testament</h3>';
      $output .=implode('<br>', $nt_list);
      $output .= '</div>';

    }
    
		$output .= '</div>';
	}
    return $output;
}

function theme_dates($variables) {
  
	$output = '';
	$items = $variables['items'];
	if(count($items) > 0) {
	  $output = '<div class="dates">';
		foreach($items as $monthYear => $media) {
			$output .= '<h3>' . l($monthYear, $media[0]->path) . '</h3>';      
		}
		$output .= '</div>';
	}
	return $output;

}

function theme_event($variables) {
  
	$output = '';
	$event = $variables['event'];
	if(count($event) > 0) {
	  $output .= '<div class="promoted-event">';
	  $output .= '<div class="promoted-event-inner clearfix">';
	  $output .= '<div class="details">';
		if($image = $event->field_event_image['und'][0]){
	  $output .= '<div class="image">';
	  $output .= theme('image_style', array('path' => $image['uri'], 'alt' => $image['alt'], 'style_name' => 'featured_events'));
    $output .= '<div class="shine-calendar"></div>';
	  $output .= '</div>';
		}
    $output .= '<div class="detail">';
	  $output .= '<h3>' . $event->title . '</h3>';
	  if (!empty($event->field_summary)) {
	    $output .= '<div class="summary">';
	    $output .= drupal_render(field_view_field('node', $event, 'field_summary', array('label' => 'hidden')));
	    $output .= '</div>';
	  }
	  $output .= !empty($event->field_event_date) ? '<div class="when"><span>When: </span>' . date('jS F Y @ g:ia,', strtotime($event->field_event_date['und'][0]['value'])) . '</div>' : '';
	  $output .= !empty($event->field_event_location) ? '<div class="where"><span>Where: </span>' . $event->field_event_location['und'][0]['safe_value'] . '</div>' : '';
	  $output .= !empty($event->field_event_cost) ? '<div class="vost"><span>Cost: </span>' . $event->field_event_cost['und'][0]['safe_value'] . '</div>' : '';
	  $output .= !empty($event->field_event_contact) ? '<div class="contact"><span>Contact: </span>' . $event->field_event_contact['und'][0]['safe_value'] . '</div>' : '';
	  $output .= '</div>';
	  $output .= '</div>';
	  $output .= '</div>';
	  $output .= '</div>';
	}
	return $output;

}


function theme_vimeo($variables) {
  $id = $variables['id'];
  if ($id) {
    $output = '';
    $feed = 'http://vimeo.com/api/v2/video/' . $id .'.xml';
    $videos = new SimpleXMLElement($feed, null, true);
    foreach($videos as $video){
      $output .= '<a href="' . $video->url . '" class="vimeo" rel="vimeo">';
			$output .= '<div class="play-overlay"></div>';
      $output .= theme('image_style', array('path' => get_remote_image_from_url($video->thumbnail_medium), 'style_name' => 'video_medium'));
      $output .= '</a>';
    }
    return $output;
  }
}


