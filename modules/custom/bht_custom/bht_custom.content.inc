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
  $output = [];
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
  $output = [
    '#theme' => 'date_created',
    '#timestamp' => $rootEntity->created,
    '#css_block' => $css_block,
  ];

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
  $output = [];
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
    $output = [
      '#theme' => 'date_field',
      '#timestamp_1' => $start_date,
      '#timestamp_2' => $end_date,
      '#css_block' => $css_block,
      '#css_modifier' => $css_modifier,
    ];
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
  return _content_news_latest();
}

/**
 * Generate the latest news list.
 *
 * @return array $output
 *    Renderable array of news nodes.
 */
function _content_news_latest() {
  $output = [];

  // Get the results of the news and events with a calculated publication date.
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_date', 'd', 'd.entity_id = n.nid');
  $query->addExpression('CASE WHEN d.field_date_value IS NULL THEN FROM_UNIXTIME(n.created) ELSE FROM_UNIXTIME(d.field_date_value) - INTERVAL 2 MONTH END', 'publish');
  $query->fields('n', ['nid', 'type', 'title']);
  $query->condition('n.status', '1')
    ->condition('n.type', ['news', 'events']);
  if (drupal_is_front_page()) {
    $and_events = db_and();
    $and_events->condition('n.type', 'events');
    $and_events->condition('n.promote', '0');
    $and_news = db_and();
    $and_news->condition('n.type', 'news');
    $and_news->condition('n.promote', '1');
    $or = db_or()->condition($and_events)
      ->condition($and_news);
    $query->condition($or);
  }
  $query->where('FROM_UNIXTIME(d.field_date_value) - INTERVAL 10 MONTH <= NOW() OR (d.field_date_value IS NULL AND n.created <= NOW())')
    ->where('FROM_UNIXTIME(d.field_date_value2) - INTERVAL 1 MONTH >= NOW() OR (d.field_date_value2 IS NULL AND FROM_UNIXTIME(n.created) >= DATE_SUB(NOW(), INTERVAL 1 MONTH))');
  // Reactivated the greater than within 1 months check, due to no results.
  //->where('FROM_UNIXTIME(d.field_date_value2) - INTERVAL 0 MONTH >= NOW() OR (d.field_date_value2 IS NULL AND FROM_UNIXTIME(n.created) >= DATE_SUB(NOW(), INTERVAL 0 MONTH))');
  if (!drupal_is_front_page()) {
    $query->orderBy('sticky', 'DESC');
  }
  $query->orderBy('publish', 'DESC');
  $results = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_OBJ);

  if (empty($results) || count($results) < 2) {
    // Get the results of blogs.
    $query = db_select('node', 'n');
    $query->fields('n', ['nid', 'type', 'title']);
    $query->addField('n', 'created', 'publish');
    $query->condition('n.status', '1')
      ->condition('n.type', ['blog']);
    if (!drupal_is_front_page()) {
      $query->orderBy('sticky', 'DESC');
    }
    $query->orderBy('publish', 'DESC');
    $blog_results = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_OBJ);
    array_merge($results, $blog_results);
  }

  // Add a weight count based on the incremental total of each entity type.
  $event_count = 0;
  $news_count = 0;
  $blog_count = 0;
  foreach ($results as $nid => $node) {
    switch ($node->type) {
      case 'events':
        $results[$nid]->weight = ++$event_count;
        break;

      case 'news':
        $results[$nid]->weight = ++$news_count;
        break;

      case 'blog':
        $results[$nid]->weight = ++$blog_count;
        break;

      default:
        break;
    }
  }

  // Sort by the given weight.
  usort($results, '_bht_news_weight_sort');

  // Only return the first two items.
  $results = array_slice($results, 0, 2);


  if (!empty($results)) {
    $nids = [];
    foreach ($results as $node) {
      $nids[] = $node->nid;
    }

    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'teaser');

    $output[] = [
      '#theme' => 'news_latest',
      '#items' => $nodes['nodes'],
    ];
  }

  return $output;
}

/**
 * Generate the promoted event list.
 *
 * @return array $output
 *    Renderable array of event nodes.
 */
function _content_event_promoted() {
  $output = [];

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', ['nid']);
  // Add conditions.
  $query->condition('n.type', 'events')
    ->condition('n.status', '1')
    ->condition('n.promote', '1');
  // Limit the results.
  $query->range(0, 1);
  // Order by latest changes.
  $query->orderBy('n.changed', 'DESC');
  // Process query.
  $nids = $query->execute()->fetchCol();

  if (!empty($nids)) {
    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'promoted');

    $output = [
      '#theme' => 'event_promoted',
      '#items' => $nodes['nodes'],
    ];
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
  $output = [];

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', ['nid']);
  // Add conditions.
  $query->condition('n.type', 'events')
    ->condition('n.status', '1')
    ->condition('n.promote', '1');
  // Limit the results.
  $query->range(0, 1);
  // Order by latest changes.
  $query->orderBy('n.changed', 'DESC');
  // Process query.
  $nids = $query->execute()->fetchCol();

  if (!empty($nids)) {
    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'teaser_promoted');

    $output = [
      '#theme' => 'event_promoted_cta',
      '#items' => $nodes['nodes'],
    ];
  }

  return $output;
}

/**
 * Generate the scientific program information.
 *
 * @return array $output
 *    Renderable array with the event node information.
 */
function _content_event_program() {
  $output = [];

  $object = menu_get_object();

  if (is_null($object)) {
    return $output;
  }

  if ($object->type !== 'events') {
    return $output;
  }

  $node = node_load($object->nid);
  $output = node_view($node, 'program');

  return $output;
}

/**
 * Generate the event venue block.
 *
 * @return array $output
 *    Renderable array of the related venue node.
 */
function _content_event_venue() {
  $output = [];

  $object = menu_get_object();

  if (is_null($object)) {
    return $output;
  }

  if ($object->type !== 'events' && !$object->promote) {
    return $output;
  }

  $node = node_load($object->nid);
  $venue_items = field_get_items('node', $node, 'field_venue');

  $venue_items = reset($venue_items);
  while (gettype($venue_items) == 'array' && !isset($venue_items['target_id'])) {
    $venue_items = reset($venue_items);
  }
  if (isset($venue_items['target_id'])) {
    $venue_id = $venue_items['target_id'];

    $venue = node_load($venue_id);
    $output = node_view($venue, 'full');
  }

  return $output;
}

/**
 * Generate the thank you block for the event sponsors.
 *
 * @return array $output
 *    Renderable array with all the event sponsors.
 */
function _content_event_sponsors() {
  $output = [];

  $object = menu_get_object();

  if (is_null($object)) {
    return $output;
  }

  if ($object->type !== 'events' && !$object->promote) {
    return $output;
  }

  $node = node_load($object->nid);
  $output = node_view($node, 'logo');

  return $output;
}

/**
 * Generate the sponsor banner list.
 *
 * @return array $output
 *    Renderable array of sponsor nodes.
 */
function content_sponsor_banner() {
  $output = [];

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', ['nid']);
  // Add conditions.
  $query->condition('n.type', 'sponsor')
    ->condition('n.status', '1');
  // Limit the results.
  $query->range(0, 4);
  // Order by latest changes.
  $query->orderBy('n.sticky', 'DESC');
  $query->orderRandom();
  // Process query.
  $nids = $query->execute()->fetchCol();

  if (!empty($nids)) {
    // Load the nodes.
    $nodes = node_load_multiple($nids);
    $nodes = node_view_multiple($nodes, 'logo');

    $output = [
      '#theme' => 'sponsor_banner',
      '#items' => $nodes['nodes'],
    ];
  }

  return $output;
}
