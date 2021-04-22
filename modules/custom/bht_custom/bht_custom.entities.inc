<?php
/**
 * @file bht_custom.entities.inc
 *
 * @description
 * Alter entities by adding view modes and/of fields to them
 */



/**
 * Implements hook_entity_info_alter().
 *
 * All properties that are available in hook_entity_info() can be
 * altered here.
 *
 * @param object $entity_info
 *   The entity info array, keyed by entity name.
 *
 * @see hook_entity_info()
 */
function bht_custom_entity_info_alter(&$entity_info) {

  $entity_info['node']['view modes']['promoted'] = array(
    'label' => t('Promoted'),
    'custom settings' => TRUE,
  );
  $entity_info['node']['view modes']['teaser_promoted'] = array(
    'label' => t('Promoted teaser'),
    'custom settings' => TRUE,
  );

  $entity_info['node']['view modes']['logo'] = array(
    'label' => t('Logo'),
    'custom settings' => TRUE,
  );

  $entity_info['node']['view modes']['program'] = array(
    'label' => t('Scientific program'),
    'custom settings' => TRUE,
  );

}



/**
 * Implements hook_field_extra_fields().
 *
 * Exposes "pseudo-field" components on fieldable entities.
 *
 * The user-defined settings (weight, visible) are automatically applied on
 * rendered forms and displayed entities in a #pre_render callback added by
 * field_attach_form() and field_attach_view().
 *
 * @see _field_extra_fields_pre_render()
 * @see hook_field_extra_fields_alter()
 *
 * @return array $extra
 *   A nested array of 'pseudo-field' elements. Each list is nested within the
 *   following keys: entity type, bundle name, context. The keys are the name of
 *   the elements as appearing in the renderable array (either the entity form
 *   or the displayed entity). The value is an associative array:
 *   - label: The human readable name of the element.
 *   - description: A short description of the element contents.
 *   - weight: The default weight of the element.
 *
 * @ingroup field_types
 */
function bht_custom_field_extra_fields() {
  $extra = array();

  $extra['paragraphs_item']['date']['display']['date'] = array(
    'label' => t('Date'),
    'description' => t('CF - Date'),
    'weight' => -99,
  );

  return $extra;
}

/**
 * Implements hook_entity_presave().
 */
function bht_custom_entityform_presave($entity) {
  if ($entity->type == 'elbow_quiz') {
    $percentage = 0;

    $answer1 = 'b';
    $question1 = $entity->field_answers_1[LANGUAGE_NONE][0]['value'];
    if ($question1 == $answer1) {
      $percentage += 20;
    }

    $answer2 = 'c';
    $question2 = $entity->field_answers_2[LANGUAGE_NONE][0]['value'];
    if ($question2 == $answer2) {
      $percentage += 20;
    }

    $answer3 = 'b';
    $question3 = $entity->field_answers_3[LANGUAGE_NONE][0]['value'];
    if ($question3 == $answer3) {
      $percentage += 20;
    }

    $answer4 = 'b';
    $question4 = $entity->field_answers_4[LANGUAGE_NONE][0]['value'];
    if ($question4 == $answer4) {
      $percentage += 20;
    }

    $answer5 = 'a';
    $question5 = $entity->field_answers_5[LANGUAGE_NONE][0]['value'];
    if ($question5 == $answer5) {
      $percentage += 20;
    }

    $entity->field_percentage[LANGUAGE_NONE][0]['value'] = $percentage;
  }
}


/**
 * Implements hook_node_presave().
 *
 * Act on a node being inserted or updated.
 *
 * This hook is invoked from node_save() before the node is saved to the
 * database.
 *
 * @param $node
 *   The node that is being inserted or updated.
 *
 * @ingroup node_api_hooks
 */
/*function bht_custom_node_presave($node) {
  $node->foo = 'bar';
}*/



/**
 * Implements hook_node_view().
 *
 * Act on a node that is being assembled before rendering.
 *
 * The module may add elements to $node->content prior to rendering. This hook
 * will be called after hook_view(). The structure of $node->content is a
 * renderable array as expected by drupal_render().
 *
 * @description
 *   Add the extra field content in bht_custom.theme.inc
 *
 * @param $node
 *   The node that is being assembled for rendering.
 * @param $view_mode
 *   The $view_mode parameter from node_view().
 * @param $langcode
 *   The language code used for rendering.
 *
 * @see hook_entity_view()
 *
 * @ingroup node_api_hooks
 */
function bht_custom_node_view($node, $view_mode, $langcode) {
  // Check the display settings of our extra fields
  $display = field_extra_fields_get_display('node', $node->type, $view_mode);

}


/**
 * Implements hook_taxonomy_term_presave().
 *
 * Act on taxonomy terms before they are saved.
 *
 * Modules implementing this hook can act on the term object before it is
 * inserted or updated.
 *
 * @param $term
 *   A term object.
 * @param $view_mode
 * @param $langcode
 */
/*function hook_taxonomy_term_presave($term) {
  $term->obj = 'foo';
}*/



/**
 * Implements hook taxonomy_term_view().
 *
 * Act on a taxonomy term that is being assembled before rendering.
 *
 * The module may add elements to $term->content prior to rendering. The
 * structure of $term->content is a renderable array as expected by
 * drupal_render().
 *
 * @description
 * Add the extra field content in bht_custom.theme.inc
 *
 *  @param $term
 *   The term that is being assembled for rendering.
 * @param $view_mode
 *   The $view_mode parameter from taxonomy_term_view().
 * @param $langcode
 *   The language code used for rendering.
 *
 * @see hook_entity_view()
 */
/*function bht_custom_taxonomy_term_view($term, $view_mode, $langcode) {
  // Check the display settings of our extra fields
  $display = field_extra_fields_get_display('taxonomy_term', $term->vocabulary_machine_name, $view_mode);
}*/


/**
 * Implements hook paragraphs_item_view().
 *
 * @see hook_entity_view()
 */
function bht_custom_paragraphs_item_view($paragraphs_item, $view_mode, $langcode) {
  // Check the display settings of our extra fields.
  $display = field_extra_fields_get_display('paragraphs_item', $paragraphs_item->bundle, $view_mode);

  // Check if the date field is active.
  if (isset($display['date']) && $display['date']['visible']) {
    // Build the date renderable array.
    $date = _paragraphs_date_content($paragraphs_item);
    // Set field content.
    $paragraphs_item->content['date'] = $date;
  }

}


/**
 * Implements hook_contextual_links_view_alter().
 *
 * Alter a contextual links element before it is rendered.
 *
 * This hook is invoked by contextual_pre_render_links(). The renderable array
 * of #type 'contextual_links', containing the entire contextual links data that
 * is passed in by reference. Further links may be added or existing links can
 * be altered.
 *
 * @param $element
 *   A renderable array representing the contextual links.
 * @param $items
 *   An associative array containing the original contextual link items, as
 *   generated by menu_contextual_links(), which were used to build
 *   $element['#links'].
 *
 * @see hook_menu_contextual_links_alter()
 * @see contextual_pre_render_links()
 * @see contextual_element_info()
 */
// function bht_custom_contextual_links_view_alter(&$element, &$items) {
//   global $language;

//   // This hook is called for EVERY set of contextual links on a page.
//   // We first want to check the $element to make sure we are adding a link to
//   // the correct list of contextual links. In this case we only want to add a
//   // link to blocks where ctsort module could alter the output. We just add
//   // links using the same array structure as is used by theme_links.
//   if (isset($element['#element']['#block']) && $element['#element']['#block']->delta == 'cb_hello_world') {
//     $element['#links']['ctlist'] = array(
//       'title' => t('Sort the world'),
//       'href' => url('ctlist/hello-world/sort', array('language' => $language, 'absolute' => TRUE)),
//     );
//   }
// }

