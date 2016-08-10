<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file field.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable
 */

// Set the CSS BEM block name
if (isset($element['#bundle'])) {
  $bundle = $element['#bundle'];
  // Correctly format some bundles
  if ($bundle === 'shop_categories') {
    $bundle = 'shop_category';
  }
  if ($bundle === 'product_display') {
    $bundle = 'product';
  }
  // Clean up the css identifier
  $field_type_css = drupal_clean_css_identifier($bundle);
}

// Set the CSS BEM element name
if (isset($element['#field_name'])) {
  // Strip the field_ prefix if present
  $field_name = preg_replace(array('/field_/', '/[_-]{2,}/'), array('', '_'), $element['#field_name']);
  // Clean up the css identifier
  $field_name_css = drupal_clean_css_identifier($field_name);
}

// Build wrapper CSS BEM classes
$classes_array = array();
$classes_array[] = $field_name_css;
$classes_array[] = $field_type_css . '__' . $field_name_css;
$classes = implode(' ', $classes_array);
?>

<?php if (isset($items) && !empty($items)): ?>

  <?php if (!$label_hidden): ?>
    <div class="<?php print $classes; ?>">
  <?php endif; ?>

  <?php if (!$label_hidden): ?>
    <?php // Define default label classes ?>
    <?php $label_attributes = array('class' => array('label')); ?>
    <?php if (isset($element['#label_display'])) $label_attributes['class'][] = "label--{$element['#label_display']}"; ?>
    <?php if (isset($element['#label_display'])) $label_attributes['class'][] = "label--{$field_name_css}"; ?>
    <?php // Rebuild the title attributes ?>
    <?php $variables['title_attributes_array'] = array_merge_recursive($variables['title_attributes_array'], $label_attributes); ?>
    <?php $title_attributes = drupal_attributes($variables['title_attributes_array']); ?>
    <label<?php print $title_attributes; ?>><?php print $label ?></label>
  <?php endif; ?>

  <?php
  // Add default link classes
  $item = current($items);
  if (isset($item['#type']) && $item['#type'] === 'link') {
    $link_attributes = array('class' => array());
    foreach ($classes_array as $class) {
      $link_attributes['class'][] = $class . '-link';
    }
  }
  ?>

  <?php foreach ($items as $delta => $item): ?>
    <?php
    if (isset($item['#type']) && $item['#type'] === 'link') {
      if (isset($item['#options']['attributes'])) {
        $item_attributes = &$item['#options']['attributes'];
        $item_attributes = array_merge_recursive(
          $item_attributes, $link_attributes
        );
      }
      else {
        $item['#options']['attributes'] = $link_attributes;
      }
    }
    ?>
    <?php print render($item); ?>
  <?php endforeach; ?>

  <?php if (!$label_hidden): ?>
    </div>
  <?php endif; ?>

<?php endif; ?>
