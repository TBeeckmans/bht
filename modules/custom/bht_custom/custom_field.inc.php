<?php
/**
 * @file bht_custom.entities.inc
 *
 * @description
 * Alter entities by adding view modes and/of fields to them
 */

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
  // Check the display settings of our extra fields.
  $display = field_extra_fields_get_display('node', $node->type, $view_mode);

}

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
    // @TODO: Here is where Stijns magic performs.
    //$date = _paragraphs_date_content($paragraphs_item);
    $date = array();
    // Set field content.
    $paragraphs_item->content['date'] = $date;
  }

}
