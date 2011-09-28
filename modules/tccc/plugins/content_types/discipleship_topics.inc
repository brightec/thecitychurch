<?php

$plugin = array(
  'title' => t('Discipleship topics tree'),
  'category' => t('TCCC'),
  'single' => TRUE,
);


function tccc_discipleship_topics_content_type_render($subtype, $conf, $args, $context) {

  $nodes = _tccc_get_pages_grouped_by_topic();
  $tree = _tccc_build_discipleship_tree(8, 0, $nodes, 0);
  $trees = _tccc_split_tree($tree);
  
  $output = '';
  $output .= '<div class="topic-column column-alpha">' . _tccc_render_discipleship_tree($trees[0], 0) . '</div>';
  $output .= '<div class="topic-column">' . _tccc_render_discipleship_tree($trees[1], 0) . '</div>';
  $output .= '<div class="topic-column column-omega">' . _tccc_render_discipleship_tree($trees[2], 0) . '</div>';
  $output .= '<div style="clear: both"></div>';
  
  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function _tccc_get_pages_grouped_by_topic() {
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'discipleship_topic');
  $query->propertyCondition('status', 1);
  $result = $query->execute();
  $nodes = node_load_multiple(array_keys($result['node']));

  $result = array();
  foreach ($nodes as $node) {
    $tid = $node->field_subtopic['und'][0]['tid'];
    $result[$tid][] = $node;
  }
  
  return $result;
}


function _tccc_build_discipleship_tree($vid, $parent, &$nodes, $depth) {
  $results = array();
  
  foreach (taxonomy_get_tree($vid, $parent, 1) as $term) {
    $result = array();
    $result['name'] = $term->name;
    $result['depth'] = $depth;
    $result['children'] = _tccc_build_discipleship_tree($vid, $term->tid, $nodes, $depth+1);
    
    $term_nodes = $nodes[$term->tid];
    if (!empty($term_nodes)) {
      foreach ($term_nodes as $node) {
        $result['links'][] = l($node->title, 'node/' . $node->nid);
      }
    }
    
    $results[] = $result;
  }
  return $results;
}


// TODO: make this more intelligent for very unbalanced trees

function _tccc_split_tree($tree) {
  $trees = array();
  foreach ($tree as $delta => $branch) {
    $trees[$delta % 3][] = $branch;
  }
  return $trees;
}


function _tccc_render_discipleship_tree($tree) {
  $output = '';
  
  foreach ($tree as $item) {
    
    if ($item['depth'] == 0) {
      $output .= '<div class="b">';
    }
    
    $output .= '<div class="term term-depth-' . $item['depth'] . '">';
    
    // opening tag
    if ($item['depth'] == 0) {
      $output .= '<h2>' . check_plain($item['name']) . '</h2>';
    } else if ($item['depth'] == 1) {
      $output .= '<h3>' . check_plain($item['name']) . '</h3>';
    } else {
      $output .= '<span>' . check_plain($item['name']) . '</span>';
    }
    
    if (!empty($item['links'])) {
      $output .= '<ul>';
      foreach ($item['links'] as $link) {
        $output .= '<li>' . $link . '</li>';
      }
      $output .= '</ul>';
    }
    
    if (!empty($item['children'])) {
      $output .= _tccc_render_discipleship_tree($item['children']);
    }
    
    $output .= '</div>';
    
    if ($item['depth'] == 0) {
      $output .= '</div>';
    }
    
  }
  
  return $output;
}


function tccc_discipleship_topics_content_type_admin_title($subtype, $conf, $context) {
  return 'Discipleship topics tree';
}
