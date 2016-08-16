<?php
/**
 * @file
 * Adds helper functions to the module.
 */

/**
 * Create a list of available view modes for use in select list.
 *
 * @return array $rtn
 *   A list of view modes.
 */
function _get_view_modes($entity = 'node') {
  $entity_info = entity_get_info($entity);

  $rtn = array();

  foreach ($entity_info['view modes'] as $key => $value) {
    $rtn[$key] = $value['label'];
  }

  return $rtn;
}


/**
 * Check if the referenced node is still active.
 *
 * @param int $nid
 *    The node ID.
 *
 * @return bool
 *    Success if the node still exists.
 */
function _node_exists($nid) {

  // BUILD QUERY.
  // Select the table.
  $query = db_select('node', 'n');
  // Pick the fields.
  $query->fields('n', array('nid'));
  // Add conditions.
  $query->condition('n.status', '1')
        ->condition('n.nid', (int) $nid);
  // Process query.
  $result = $query->execute()->rowCount();

  if ($result == 1) {
    return TRUE;
  }

  return FALSE;
}


/**
 * Clean the renderable array by checking on wanted fields and ignoring others.
 *
 * If there are no desired fields left to render, don't pass the
 * renderable array in order to prevent unwanted characters from the template.
 *
 * @param array $output
 *    Renderable array.
 */
function _clean_renderable(&$output, $ignore = array(
  'links',
  'comments',
  'language',
  'sharelinks',
)) {
  // Check if there are wanted renderable fields.
  if (!count(array_diff(element_children($output), $ignore))) {
    $output = array();
  }
}


/**
 * Get the translated entity id for the requested language.
 *
 * @param  integer $id
 * @param  string $entity_type
 * @param  string $langcode
 *
 * @return integer Returns the translated entity id if available.
 */
function _get_translated_id($id = NULL, $entity_type = 'node', $langcode = NULL) {
  global $language;

  // Set the desired language code
  if (is_null($langcode)) {
    $langcode = $language->language;
  }

  // Different approaches per entity type
  switch ($entity_type) {
    case 'node':
      if (module_exists('translation') && function_exists('translation_node_get_translations')) {
        // Load the node
        $node = node_load($id);
        // Get available node translations
        if (isset($node->tnid) && !empty($node->tnid)) {
          $node_translations = translation_node_get_translations($node->tnid);
          // Set the translation id as the requested id
          if (!empty($node_translations) && ($nid_translation = $node_translations[$langcode])) {
            $id = $nid_translation->nid;
          }
        }
      }
      break;

    case 'taxonomy_term':
      if (module_exists('i18n_taxonomy') && function_exists('i18n_taxonomy_term_get_translation')) {
        // Load the taxonomy term
        $term = taxonomy_term_load($id);
        // Get available term translations
        $term_translation = i18n_taxonomy_term_get_translation($term, $langcode);
        if (!is_null($term_translation)) {
          $id = $term_translation->tid;
        }
      }
      break;

    default:
      // TODO: check for a global alternative
      break;
  }

  // Return the translated id
  return $id;
}


/**
 * Get the renderable block array, including wrapper and title.
 *
 * @param string $module
 * @param string $delta
 *
 * @return array Returns the renderable block array.
 */
function _get_block_with_title($module, $delta) {
  $output = array();

  if (gettype($module) == 'string' && gettype($delta) == 'string') {
    // Get block instance content WITH WRAPPER
    $block = block_load($module, $delta);

    if (!empty($block)) {
      // Render the block
      $rendered_block = _block_render_blocks(array($block));

      if (!empty($rendered_block)) {
        // Grab the renderable array
        $output = _block_get_renderable_array($rendered_block);
      }
    }
  }

  return $output;
}


/**
 * Get the renderable block array, without wrapper and title.
 *
 * @param string $module
 * @param string $delta
 *
 * @return array Returns the renderable block array.
 */
function _get_block_without_title($module, $delta) {
  $output = array();

  if (gettype($module) == 'string' && gettype($delta) == 'string') {

    // Get block instance content WITHOUT WRAPPER
    $block = module_invoke($module, 'block_view', $delta);

    // Grab the renderable array
    if (isset($block['content']) && !empty($block['content'])) {
      $output = $block['content'];
    }
  }

  return $output;
}

/**
 * Get Paragraphs root entity.
 *
 * @param object $entity
 *    The paragraph entity.
 *
 * @return object $root_entity
 *    Root entity object.
 */
function _paragraphs_root_entity($entity) {
  $root_entity = NULL;

  if (is_object($entity)) {
    if (method_exists($entity, 'hostEntity')) {
      $root_entity = $entity->hostEntity();
      if (method_exists($root_entity, 'hostEntity')) {
        $root_entity = _paragraphs_root_entity($root_entity);
      }
    }
  }

  return $root_entity;
}

/**
 * Get Paragraphs root entity type.
 *
 * @param object $entity
 *    The paragraph entity.
 *
 * @return string $root_entity_type
 *    Root entity type.
 */
function _paragraphs_root_entity_type($entity) {
  $root_entity = NULL;
  $root_entity_type = NULL;

  if (is_object($entity)) {
    if (method_exists($entity, 'hostEntity') && method_exists($entity, 'hostEntityType')) {
      $root_entity = $entity->hostEntity();
      $root_entity_type = $entity->hostEntityType();
      if (method_exists($root_entity, 'hostEntity') && method_exists($root_entity, 'hostEntityType')) {
        $root_entity_type = _paragraphs_root_entity_type($root_entity);
      }
    }
  }

  return $root_entity_type;
}

/**
 * User sort function for the BHT News.
 *
 * @param object $a
 *    Object A t o compare.
 * @param object $b
 *    Object B t o compare.
 *
 * @return int
 *    The sort indicator.
 */
function _bht_news_weight_sort($a, $b) {
  if ($a->weight != $b->weight) {
    return $a->weight < $b->weight ? -1 : 1;
  }

  return 0;
}

/**
 * Theme helper function. Print location of template file.
 */
function theme_helper($file) {
  if ((bool) variable_get('bht_production', FALSE)) {
    print "<!-- " . $file . "-->";
  }
}
