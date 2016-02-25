<?php

/**
 * Example for hook_term_get_nodes
 *
 * Create a list of content linked to the current taxonomy term
 * and his children
 *
 * @param stdClass $term
 *   the current taxonomy term the content is being overwritten
 *   for
 *
 * @return
 *   renderable array
 */
function hook_term_get_nodes(\stdClass $term) {
  $output = FALSE;

  // Create a list of underlying terms
  $children = _bht_taxonomy_get_child_tids($term->vid, $term->tid);

  $query = db_select('taxonomy_index', 't')->extend('PagerDefault');
  $query->leftJoin('node', 'n', 'n.nid=t.nid');

  // Restrict the return value to return node ids only
  $query->fields('n', array('nid'));

  // Check if the children have content
  $query->condition('t.tid', $children, 'IN');
  // Active nodes only
  $query->condition('n.status', (int) TRUE, '=');

  // Check if the translation module is enabled
  if (module_exists('translation')) {
    global $language;
    $query->condition('n.language', $language->language, '=');
  }

  // Set the number of items on the overview page
  $query->limit(variable_get("taxonomy_content_items", 12));

  // Check if the current vocabulary's sticky items should be shown first
  if (isset($order['sticky']) && $order['sticky']) {
    $query->orderBy('n.sticky', 'DESC');
  }

  $results = $query->execute()->fetchCol();

  if ($results) {
    $output = array();

    // load the nodes
    $nodes = node_load_multiple($results);
    // make them renderable
    $nodes = node_view_multiple($nodes);

    $output[] = array(
      '#theme' => 'taxonomy_content', // theme function is defined in bht_taxonomy
      '#items' => $nodes['nodes'],
      '#pager' => array('#theme' => 'pager'),
      '#vid' => $term->vid,
    );

    return $output;
  }

  return $output;
}
