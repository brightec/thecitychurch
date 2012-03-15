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

  //sites form
  $form = drupal_get_form('_tccc_resources_sidebar_sites_form');


  //filter
  $resource_list = '';
  $filter = $context->data;

  switch ($filter->type) {
    case 'data':
      $resource_list = _tccc_resources_sidebar_dates($filter);
      break;
    case 'tag':
      $resource_list = _tccc_resources_sidebar_tags($filter);
      break;
    case 'series':
      $resource_list = _tccc_resources_sidebar_series($filter);
      break;
    case 'person':
      $resource_list = _tccc_resources_sidebar_person($filter);
      break;
    case 'bible':
      $resource_list = _tccc_resources_sidebar_bible($filter);
      break;
  }


  $output = array(
    'site form' => array(
      '#prefix' => '<h2>Sites</h2>',
      $form,
    ),
    'filter' => array(
      '#markup' => $resource_list,
    )
  );

  $block = new stdClass;
  $block->content = $output;
  return $block;
}

function _tccc_resources_sidebar_sites_form($form, &$form_state) {

  $IS_FIRST = 'FALSE';
  if (empty($form_state['input'])) {
    $IS_FIRST = 'TRUE';
  }

  $vocab = taxonomy_vocabulary_machine_name_load('sites');
  $sites = taxonomy_get_tree($vocab->vid);
  $options = array();

  foreach ($sites as $site) {
    $options[$site->tid] = $site->name;
  }

  $form['sites'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#title' => '',
    '#default_value' => array_keys($options),
  );

  $form['is_first'] = array(
    '#type' => 'hidden',
    '#value' => $IS_FIRST,
  );

  drupal_add_js(path_to_theme() . '/js/resource_site.js', array('type' => 'file', 'scope' => 'footer'));

  return $form;
}

function _tccc_resources_sidebar_sites_form_submit($form, &$form_state) {
  $_SESSION['first'] = FALSE;
  return $form;
}

function _tccc_resources_sidebar_sites_form_callback($form, &$form_state) {
  drupal_form_submit('_tccc_resources_sidebar_sites_form', $form_state);
  return $form['sites'];
}

// TODO: expand old years. make sure that if the filter has a date selected,
// that that year is expanded regardless

function _tccc_resources_sidebar_dates($filter) {
  $this_year = date('Y');
  $this_month = date('n');

  $output = '';
  $sermons = _tccc_get_media();
  $dates = array();

  foreach ($sermons as $sermon) {
    if (!empty($sermon->field_recording_date)) {
      $date = strtotime($sermon->field_recording_date['und'][0]['value']);
      $year = date('Y', $date);
      $month = date('m', $date);
      $f_month = date('F', $date);

      $dates[$year][$f_month] = l($f_month . ' ' . $year, 'resources/' . $filter->bundle . '/date/' . $year . '-' . $month);
    }
  }

  foreach ($dates as $year => $date) {
    $output .= '<div class="year">';
    $output .= '<h2>' . $year . '</h2>';
    $output .= '<ul class="child">';

    foreach ($date as $month => $link) {
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

  $sql = 'select distinct t.tid, t.name from {taxonomy_term_data} t, {field_data_field_person} p ' .
      'where t.tid = p.field_person_tid and p.entity_type = :entity_type and p.bundle = :bundle ' .
      'order by t.name';
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
