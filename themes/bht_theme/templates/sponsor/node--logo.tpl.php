<?php
// Merge in any custom attributes set in the renderable array.
if (isset($node->attributes_array) && is_array($node->attributes_array) ) {
  $attributes_array = drupal_array_merge_deep($attributes_array, $node->attributes_array);
}
$attributes_array['class'][] = 'sponsor__item';
if ($sticky) {
  $attributes_array['class'][] = 'sticky';
}
?>

<div <?php print drupal_attributes($attributes_array); ?>>
  <?php print render($content); ?>
</div>
