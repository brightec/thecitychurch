<?php

$plugin = array(
  'title' => 'Discipleship Topics',
  'category' => 'TCCC',
  'single' => TRUE,
    
);


function tccc_disc_topics_content_type_render($subtype, $conf, $args, $context) {
 
  $output = '';
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'discipleship_topic');
  $query->propertyCondition('status', 1);
      
  $result = $query->execute();
  $topic_nodes = node_load_multiple(array_keys($result['node']));  
  
  
  $tree = taxonomy_get_nested_tree(8);
  $output = theme_taxonomy_nested_tree_output($tree, $topic_nodes);

  $block = new stdClass;
  $block->title = NULL;
  $block->content = $output;
  return $block;
}


function tccc_disc_topics_content_type_edit_form($form, &$form_state) {
  return $form;
}

function tccc_disc_topics_content_type_admin_title($subtype, $conf, $context) {
  return 'Discipleship Topics';
}



/* Build tree from flat array */
function taxonomy_get_nested_tree($terms = array(), $max_depth = NULL, $parent = 0, $parents_index = array(), $depth = 0) {
  if (is_int($terms)) {
    $terms = taxonomy_get_tree($terms);
  }

  foreach($terms as $term) {
    foreach($term->parents as $term_parent) {
      if ($term_parent == $parent) {
        $return[$term->tid] = $term;
      }
      else {
        $parents_index[$term_parent][$term->tid] = $term;
      }
    }
  }

  foreach($return as &$term) {
    if (isset($parents_index[$term->tid]) && (is_null($max_depth) || $depth < $max_depth)) {
      $term->children = taxonomy_get_nested_tree($parents_index[$term->tid], $max_depth, $term->tid, $parents_index, $depth + 1);
    }
  }

  return $return;
}

/* Display tree */
function theme_taxonomy_nested_tree_output($tree, $topic_nodes) {

  if (!empty($tree)) {
    $output = '';
    foreach($tree as $tid => $term){
      $depth = $term->depth;
      $data = array(
        'title' => $term->name,
        'href' => 'taxonomy/term/'. $tid,
      );
      
      if($depth == 0){
        $title = '</h3>' . $data['title'] . '</h3>';
      } elseif ($depth == 1) {
        $title = '</h4>' . $data['title'] . '</h4>';
      } else {
        $title = $data['title'];
        
      }
      $has_children = $term->children ? TRUE : FALSE;      

      if ($has_children) {
        foreach($term->children as $child_tid => $child) {
          if ('taxonomy/term/'. $child_tid == $q) {
            $in_active_trail = TRUE;
          }
        }
        $output .= theme_topic_li($title, theme_taxonomy_nested_tree_output($term->children, $topic_nodes), array('topic-heading'));
      }
      
      else {
        $output .= theme_topic_li($title, '', array('topic-heading'));
        $items = '';
        foreach($topic_nodes as $node){

          if(!empty($node->field_subtopic['und'][0]['tid'])){  
            if($node->field_subtopic['und'][0]['tid'] == $term->tid){
              $items .= theme_topic_li (l($node->title, 'node/' . $node->nid), NULL, array('topic-item'));
            }
          }
        }
        $output .= '<ul class="topic-list">' . $items . '</ul>'; 
      }        
    }
  }

  return theme_dmenu_tree($output, ($depth + 1));
}


function theme_topic_li($link, $menu = '', $classes = array()){
    
    $classes = implode(' ', $classes);
  
    return '<li class="' . $classes . '">' . $link . $menu . "</li>";
}


function theme_dmenu_tree($tree, $depth){
    return '<ul class="topic-tree-' . $depth . '">' . $tree . "</ul>";
}