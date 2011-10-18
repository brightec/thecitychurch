<?php

$plugin = array(
  'title' => 'Resources Sidebar',
  'category' => 'TCCC',
  'required context' => new ctools_context_required(t('Resource Filter'), 'resource_filter'),
);


function tccc_resources_sidebar_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }
  
  $filter = $context->data;
  if ($filter->type == 'date') {
    $block = new stdClass;
    $block->content = _tccc_resources_sidebar_dates($filter);
    return $block;
  
  } else if ($filter->type == 'tag') {
    $block = new stdClass;
    $block->content = _tccc_resources_sidebar_tags($filter);
    return $block;
    
  } else if ($filter->type == 'series') {
    $block = new stdClass;
    $block->content = _tccc_resources_sidebar_series($filter);
    return $block;
    
  } else if ($filter->type == 'person') {
    $block = new stdClass;
    $block->content = _tccc_resources_sidebar_person($filter);
    return $block;
    
  } else if ($filter->type == 'bible') {
    $block = new stdClass;
    $block->content = _tccc_resources_sidebar_bible($filter);
    return $block;
  }
}


// TODO: expand old years. make sure that if the filter has a date selected,
// that that year is expanded regardless

function _tccc_resources_sidebar_dates($filter) {
  $this_year = date('Y');
  $this_month = date('n');
  
  $output = '';
  $sermons = _tccc_get_media();
  $dates = array();
  
  foreach($sermons as $sermon){
    if(!empty($sermon->field_recording_date)){
      $date = strtotime($sermon->field_recording_date['und'][0]['value']);
      $year = date('Y', $date);
      $month = date('m', $date);
      $f_month = date('F', $date);
      
      $dates[$year][$f_month] = l($f_month . ' ' . $year, 'resources/' . $filter->bundle . '/date/' . $year . '-' . $month ); 
    }
  }
  
  foreach($dates as $year => $date){
    $output .= '<div class="year">';
    $output .= '<h2>' . $year . '</h2>';
    $output .= '<ul class="child">';

    foreach($date as $month => $link){
      $output .= '<li class="child">' . $link . '</li>';
    }
    
    $output .= '</ul>';
    $output .= '</div>';
  }
  
  return $output;
}


function _tccc_resources_sidebar_tags($filter) {
  
  $sql = 'select distinct td.tid, td.name from {taxonomy_term_data} td, {field_data_field_tags} ft where td.tid = ft.field_tags_tid and ft.entity_type = :entity_type and ft.bundle = :bundle';
  $params = array(
    'entity_type' => 'node',
    'bundle' => $filter->bundle,
  );
  $query = db_query($sql, $params);
  
  $output = '';
  $output .= '<h2>Tags</h2>';
  $output .= '<ul class="child">';
  
  foreach ($query as $term) {
    $path = 'resources/' . $filter->bundle . '/tag/' . $term->tid;
    $output .= '<li class="child">' . l($term->name, $path) . '</li>';
  }
  
  $output .= '</ul>';
  return $output;
}


// TODO: remove hardcoded vocabulary id

function _tccc_resources_sidebar_series($filter) {
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term');
  $query->propertyCondition('vid', 2);
  $query->propertyOrderBy('name', 'ASC');
  $result = $query->execute();
  
  $tids = array_keys($result['taxonomy_term']);
  $terms = taxonomy_term_load_multiple($tids);
  
  $output = '';
  $output .= '<h2>Series</h2>';
  $output .= '<ul class="child">';
  
  foreach ($terms as $term) {
    $path = 'resources/' . $filter->bundle . '/series/' . $term->tid;
    $output .= '<li class="child">' . l($term->name, $path) . '</li>';
  }
  
  $output .= '</ul>';
  return $output;
}


function _tccc_resources_sidebar_person($filter) {
  
  $sql = 'select distinct t.tid, t.name from {taxonomy_term_data} t, {field_data_field_person} p where t.tid = p.field_person_tid and p.entity_type = :entity_type and p.bundle = :bundle';
  $params = array(
    'entity_type' => 'node',
    'bundle' => $filter->bundle,
  );
  $query = db_query($sql, $params);
  
  $output = '';
  $output .= '<h2>Speakers</h2>';
  $output .= '<ul class="child">';

  foreach ($query as $term) {
    $path = 'resources/' . $filter->bundle . '/people/' . $term->tid;
    $output .= '<li class="child">' . l($term->name, $path) . '</li>';
  }
  
  $output .= '</ul>';
  return $output;
}


function _tccc_resources_sidebar_bible($filter) {
  
  $ot = array(
    'title' => 'Old Testament',
    'books' => array(
      "Genesis", "Exodus", "Leviticus", "Numbers", "Deuteronomy", "Joshua", "Judges", "Ruth", "1 Samuel", "2 Samuel",
      "1 Kings", "2 Kings", "1 Chronicles", "2 Chronicles", "Ezra", "Nehemiah", "Esther", "Job", "Psalms", "Proverbs",
      "Ecclesiastes", "Song of Songs", "Isaiah", "Jeremiah", "Lamentations", "Ezekiel", "Daniel", "Hosea", "Joel",
      "Amos", "Obadiah", "Jonah", "Micah", "Nahum", "Habakkuk", "Zephaniah", "Haggai", "Zechariah", "Malachi",
    ),
  );
  
  $nt = array(
    'title' => 'New Testament',
    'books' => array(
      "Matthew", "Mark", "Luke", "John", "Acts", "Romans", "1 Corinthians", "2 Corinthians", "Galatians", "Ephesians",
      "Philippians", "Colossians", "1 Thessalonians", "2 Thessalonians", "1 Timothy", "2 Timothy", "Titus",
      "Philemon ", "Hebrews", "James", "1 Peter", "2 Peter", "1 John", "2 John", "3 John", "Jude ", "Revelation",
    ),    
  );

  $used_books = array();
  $sql = 'select distinct(field_scriptures_book) from {field_data_field_scriptures}';
  $query = db_query($sql);
  foreach ($query as $book) {
    $used_books[] = $book->field_scriptures_book;
  }
  
  $output = '';
  
  foreach (array($ot, $nt) as $testament) {
    $output .= '<h2>' . check_plain($testament['title']) . '</h2>';
    $output .= '<ul class="child">';
    foreach ($testament['books'] as $book) {
      $id = bible_parse_book($book);
      if (in_array($id, $used_books)) {
        $path = 'resources/' . $filter->bundle . '/bible/' . $id;
        $output .= '<li class="child">' . l($book, $path) . '</li>';
      }
    }
    $output .= '</ul>';
  }
  
  return $output;
}


function tccc_resources_sidebar_content_type_edit_form($form, &$form_state) {
  return $form;
}


function tccc_resources_sidebar_content_type_admin_title($subtype, $conf, $context) {
  return 'Resources Sidebar';
}
