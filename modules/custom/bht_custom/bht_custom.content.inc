<?php
/**
 * @file bht_custom.content.inc
 *
 * Generate the renderable arrays for the custom content.
 */


/**
 * Generate the paragraphs date field.
 *
 * @param object $entity
 *    The Paragraph entity.
 *
 * @return array $output
 *    Renderable array of the date field.
 */
function _paragraphs_date_content($entity) {
  $output = array();
  $date_field = NULL;
  $date_fieldname = NULL;

  // Fetch the host entity of the paragraph.
  $rootEntity = _paragraphs_root_entity($entity);
  $rootEntityType = _paragraphs_root_entity_type($entity);

  if (is_null($rootEntity) || is_null($rootEntityType)) {
    return $output;
  }

  // Determine the BEM block.
  switch ($rootEntityType) {
    case 'node':
      $css_block = drupal_clean_css_identifier($rootEntity->type);
      break;

    case 'taxonomy_term':
      $css_block = drupal_clean_css_identifier($rootEntity->vocabulary_machine_name);
      break;

    default:
      $css_block = '';
      break;
  }

  // Set created date as default.
  $output = array(
    '#theme' => 'date_created',
    '#timestamp' => $rootEntity->created,
    '#css_block' => $css_block,
  );

  // Set date field if available.
  if (isset($rootEntity->field_date)) {
    $date_fieldname = 'field_date';
    $date_field = &$rootEntity->field_date;
  }

  // If a date field is found, parse the content.
  if (!is_null($date_field) && !is_null($date_fieldname)) {
    $output = _format_date($rootEntityType, $rootEntity, $date_fieldname);
  }

  return $output;
}


/**
 * Generate a renderable array with the start and / or the end date.
 *
 * @param string $entityType
 *    The kind of entity from which to render the date.
 * @param object $entity
 *    The entity to render the date from.
 * @param string $date_fieldname
 *    The date field to process.
 *
 * @return array $output
 *    Renderable array of the date(s).
 */
function _format_date($entityType, $entity, $date_fieldname) {
  $output = array();
  $view_mode = NULL;
  $start_date = '';
  $end_date = NULL;

  // Determine the BEM block
  switch ($entityType) {
    case 'node':
      $css_block = drupal_clean_css_identifier($entity->type);
      break;
    case 'taxonomy_term':
      $css_block = drupal_clean_css_identifier($entity->vocabulary_machine_name);
      break;
    default:
      $css_block = '';
      break;
  }

  // Determine the BEM modifier
  $css_modifier = NULL;
  if (isset($entity->css_modifier)) {
    $css_modifier = $entity->css_modifier;
  }

  $date = field_get_items($entityType, $entity, $date_fieldname);

  // Fetch the date value
  if (!empty($date)) {
    $date = reset($date);
    if (isset($date['value'])) {
      $start_date = $date['value'];
    }
    if (isset($date['value2'])) {
      $end_date = $date['value2'];
    }
  }

  // Build the date markup
  if (!empty($start_date)) {
    $output = array(
      '#theme' => 'date_field',
      '#timestamp_1' => $start_date,
      '#timestamp_2' => $end_date,
      '#css_block' => $css_block,
      '#css_modifier' => $css_modifier,
    );
  }

  return $output;
}

/**
 * Generate the news overview.
 *
 * @return array $output
 *    Renderable array of news nodes.
 */
function _content_news_overview() {
  $output = array();

  //// BUILD QUERY
  ////////////////
  //// Select the table
  //$query = db_select('node', 'n')->extend('PagerDefault')->element(1);
  //// Join tables
  //$query->leftJoin('field_data_field_action_date', 'd', 'd.entity_id = n.nid');
  //// Pick the fields
  //$query->fields('n', array('nid'));
  //// Add conditions
  //$query->condition('n.status', '1')
  //      ->condition('n.type', 'action')
  //      ->condition("d.field_action_date_value2", time(), '>=');
  //// Filtered by language
  //if (module_exists('i18n_node')) {
  //  global $language;
  //  $query->condition('n.language', $language->language);
  //}
  //// Add sorting
  //$query->orderBy('n.sticky', 'DESC')
  //      ->orderBy('d.field_action_date_value2', 'DESC')
  //      ->orderBy('n.title', 'ASC');
  //// Limit the pager range
  //$query->limit(variable_get('action_current_count', '3'));
  //// Process query
  //$nids = $query->execute()->fetchCol();
  //
  //if (!empty($nids)) {
  //  // Load the nodes
  //  $nodes = node_load_multiple($nids);
  //  $nodes = node_view_multiple($nodes, 'teaser');
  //
  //  $output[] = array(
  //    '#theme' => 'news',
  //    '#items' => $nodes['nodes'],
  //  );
  //  $output[] = array(
  //    '#theme' => 'pager',
  //    '#element' => 1,
  //  );
  //}

  return $output;
}


/**
 * Generate the latest news list.
 *
 * @return array $output
 *    Renderable array of news nodes.
 */
function _content_news_latest() {
  $output = array();

  //// BUILD QUERY
  ////////////////
  //// Select the table
  //$query = db_select('node', 'n')->extend('PagerDefault')->element(2);
  //// Join tables
  //$query->leftJoin('field_data_field_action_date', 'd', 'd.entity_id = n.nid');
  //// Pick the fields
  //$query->fields('n', array('nid'));
  //// Add conditions
  //$query->condition('n.status', '1')
  //      ->condition('n.type', 'action')
  //      ->condition("d.field_action_date_value2", time(), '<');
  //// Filtered by language
  //if (module_exists('i18n_node')) {
  //  global $language;
  //  $query->condition('n.language', $language->language);
  //}
  //// Add sorting
  //$query->orderBy('n.sticky', 'DESC')
  //      ->orderBy('d.field_action_date_value2', 'DESC')
  //      ->orderBy('n.title', 'ASC');
  //// Limit the pager range
  //$query->limit(variable_get('action_past_count', '8'));
  //// Process query
  //$nids = $query->execute()->fetchCol();
  //
  //if (!empty($nids)) {
  //  // Load the nodes
  //  $nodes = node_load_multiple($nids);
  //  $nodes = node_view_multiple($nodes);
  //
  //  $output[] = array(
  //    '#theme' => 'action_past',
  //    '#items' => $nodes['nodes'],
  //  );
  //  $output[] = array(
  //    '#theme' => 'pager',
  //    '#element' => 2,
  //  );
  //}

  return $output;
}


/**
 * Generate the latest event list.
 *
 * @return array $output
 *    Renderable array of event nodes.
 */
function _content_event_latest() {
  $output = array();

  //// BUILD QUERY
  ////////////////
  //// Select the table
  //$query = db_select('node', 'n');
  //// Pick the fields
  //$query->fields('n', array('nid'));
  //// Add conditions
  //$query->condition('n.type', 'recipe')
  //      ->condition('n.status', '1');
  //$db_or = db_or()->condition('n.sticky', '1')
  //                ->condition('n.promote', '1');
  //$query->condition($db_or);
  //// Filtered by language
  //if (module_exists('i18n_node')) {
  //  global $language;
  //  $query->condition('n.language', $language->language);
  //}
  //// Sort the results
  //$query->orderBy('n.promote', 'DESC');
  //// Process query
  //$nids = $query->execute()->fetchCol();
  //
  //if (!empty($nids)) {
  //  // Load the nodes
  //  $nodes = node_load_multiple($nids);
  //  $nodes = node_view_multiple($nodes, 'teaser_sticky');
  //
  //  $output = array(
  //    '#theme' => 'recipe_sticky',
  //    '#items' => $nodes['nodes'],
  //  );
  //}

  return $output;
}

/**
 * Generate the promoted event list.
 *
 * @return array $output
 *    Renderable array of event nodes.
 */
function _content_event_promoted() {
  $output = array();

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', array('nid'));
  // Add conditions.
  $query->condition('n.type', 'event')
        ->condition('n.status', '1')
        ->condition('n.promote', '1');
  // Limit the results.
  $query->range(0, 1);
  // Process query.
  $nids = $query->execute()->fetchCol();

  if (!empty($nids)) {
    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'promoted');

    $output = array(
      '#theme' => 'event_promoted',
      '#items' => $nodes['nodes'],
    );
  }

  return $output;
}


/**
 * Generate the promoted event CTA.
 *
 * @return array $output
 *    Renderable array of event nodes.
 */
function _content_event_promoted_cta() {
  $output = array();

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', array('nid'));
  // Add conditions.
  $query->condition('n.type', 'event')
        ->condition('n.status', '1')
        ->condition('n.promote', '1');
  // Limit the results.
  $query->range(0, 1);
  // Process query.
  $nids = $query->execute()->fetchCol();

  if (!empty($nids)) {
    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'teaser_promoted');

    $output = array(
      '#theme' => 'event_promoted_cta',
      '#items' => $nodes['nodes'],
    );
  }

  return $output;

  return $output;
}

/**
 * Generate the scientific program information.
 *
 * @return array $output
 *    Renderable array with the event node information.
 */
function _content_event_program() {
  $output = array();

  return $output;
}

/**
 * Generate the event venue block.
 *
 * @return array $output
 *    Renderable array of the related venue node.
 */
function _content_event_venue() {
  $output = array();

  return $output;
}

/**
 * Generate the thank you block for the event sponsors.
 *
 * @return array $output
 *    Renderable array with all the event sponsors.
 */
function _content_event_sponsors() {
  $output = array();

  return $output;
}

/**
 * Generate the sponsor banner list.
 *
 * @return array $output
 *    Renderable array of sponsor nodes.
 */
function sponsor_banner() {
  $output = array();

  //// BUILD QUERY
  ////////////////
  //// Select the table
  //$query = db_select('taxonomy_term_data', 'td');
  //// Pick the fields
  //$query->fields('td', array('tid'));
  //// Add conditions
  //$query->condition('td.vid', BRAND_VID);
  //// Filtered by language
  //if (module_exists('i18n_taxonomy')) {
  //  global $language;
  //  $query->condition('td.language', $language->language);
  //}
  //// Add sorting
  //$query->orderBy('td.weight', 'ASC');
  //// Limit the results
  //$query->range(0,8);
  //// Process query
  //$tids = $query->execute()->fetchCol();
  //
  //// Process the terms
  //if (!empty($tids)) {
  //  // Load the terms
  //  $terms = taxonomy_term_load_multiple($tids);
  //  $terms = taxonomy_term_view_multiple($terms, variable_get('brand_banner_view_mode', 'logo'));
  //
  //  $output = array(
  //    '#theme' => 'brand_banner',
  //    '#items' => $terms['taxonomy_terms'],
  //  );
  //}

  return $output;
}
