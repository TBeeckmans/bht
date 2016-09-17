<?php
// This function is invoked as theme wrapper, but the rendered form element
// may not necessarily have been processed by form_builder().
$element['#title_display'] = 'before';

if (!isset($attributes_array)) {
  $attributes_array = array();
}

if (!empty($element['#attributes_array'])) {
  $attributes_array = drupal_array_merge_deep($attributes_array, $element['#attributes_array']);
}

// Add element #id for #type 'item'.
if (isset($element['#markup']) && !empty($element['#id'])) {
  $attributes_array['id'] = $element['#id'];
}
// Add element's #type and #name as class to aid with JS/CSS selectors.
$attributes_array['class'][] = 'form-item';
$attributes_array['class'][] = 'member';
$attributes_array['class'][] = 'js-radio-dynamic';
if (!empty($element['#type'])) {
  $attributes_array['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
}
if (!empty($element['#name'])) {
  $attributes_array['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
}
// Add a class for disabled elements to facilitate cross-browser styling.
if (!empty($element['#attributes']['disabled'])) {
  $attributes_array['class'][] = 'form-disabled';
}

// If #title is not set, we don't display any label or required marker.
if (!isset($element['#title'])) {
  $element['#title_display'] = 'none';
}
$prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
$suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';


$title = $element['#title'];

$label_text = t('Yes, I\'d like to become a %title', array(
  '%title' => $title,
));

?>

<div<?php print drupal_attributes($attributes_array); ?>>
  <?php print $prefix . $element['#children'] . $suffix; ?>

  <label class="member-check" for="<?php print $element['#id']; ?>">
    <h3><?php print $label_text; ?></h3>

    <?php if (!empty($attributes_array['data-price'])): ?>
      <div class="member-price">
        <?php print _bht_format_price($attributes_array['data-price']); ?>
      </div>
    <?php endif; ?>

    <small>&nbsp;</small>
  </label>

</div>
