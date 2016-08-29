<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */

// Strip unwanted paragraph classes
// TODO: 'paragraphs-item-taxonomy-item'
$classes_array = array_diff($classes_array, array('entity', 'entity-paragraphs-item'));

// Get the root host entity
$rootHostEntity = _paragraphs_root_entity($paragraphs_item);
$rootHostEntityType = _paragraphs_root_entity_type($paragraphs_item);

// Determine the BEM block
$css_block = 'layout';
if (!is_null($rootHostEntity) && !is_null($rootHostEntityType)) {
  switch ($rootHostEntityType) {
    case 'node':
      $block_type = $rootHostEntity->type;
      break;
    case 'taxonomy_term':
      $block_type = $rootHostEntity->vocabulary_machine_name;
      break;
    default:
      $block_type = 'layout';
      break;
  }
  $css_block = drupal_clean_css_identifier($block_type);
}

// Determine the BEM element
$css_element = 'item';
if (isset($elements['#bundle'])) {
  $bundle = $elements['#bundle'];
  $css_element = drupal_clean_css_identifier($bundle);

  // Remove the class with bundle name from the array
  if(($key = array_search('paragraphs-item-'.$css_element, $classes_array)) !== false) {
    unset($classes_array[$key]);
  }

}

// Add the BEM style classes
$classes_array[] = $css_element;
if (!empty($css_block)) {
  $classes_array[] = $css_block . '__' . $css_element;
}

// Update the attributes array with the new classes array
$attributes_array['class'] = $classes_array;

$label_attributes['class'][] = $css_element . '-label';
if (!empty($css_block)) {
  $label_attributes['class'][] = $css_block . '__' . $css_element . '-label';
}

$session_attributes['class'][] = $css_element . '-session';
if (!empty($css_block)) {
  $session_attributes['class'][] = $css_block . '__' . $css_element . '-session';
}

$presenter_attributes['class'][] = $css_element . '-presenter';
if (!empty($css_block)) {
  $presenter_attributes['class'][] = $css_block . '__' . $css_element . '-presenter';
}

$file_attributes['class'][] = $css_element . '-file';
if (!empty($css_block)) {
  $file_attributes['class'][] = $css_block . '__' . $css_element . '-file';
}

?>

<div <?php print drupal_attributes($attributes_array); ?>>

  <span <?php print drupal_attributes($label_attributes); ?>>
    <?php print render($content['field_label']); ?>
  </span>

  <?php if (!empty($content['field_session'])): ?>
    <span <?php print drupal_attributes($session_attributes); ?>>
      <?php print render($content['field_session']); ?>
    </span>
  <?php endif; ?>

  <?php if (!empty($content['field_presenter'])): ?>
    <span <?php print drupal_attributes($presenter_attributes); ?>>
      <?php print render($content['field_presenter']); ?>
    </span>
  <?php endif; ?>

  <?php if (!empty($content['field_file'])): ?>
    <div <?php print drupal_attributes($file_attributes); ?>>
      <?php print render($content['field_file']); ?>
    </div>
  <?php endif; ?>

</div>
