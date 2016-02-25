<?php
/**
 * Template for the custom taxonomy implementation
 * Displays taxonomy children
 */

$css_block = '';
if (isset($vid)) {
  // Load the vocabulary
  $vocab = taxonomy_vocabulary_load($vid);

  // Determine the BEM block name
  $css_block = drupal_clean_css_identifier($vocab->machine_name);
}

// Add the BEM default class
$attributes_array['class'][] = 'taxonomy-children';

// Add the BEM specific vocab class
if (strlen($css_block) > 0) {
  $attributes_array['class'][] = $css_block . '__taxonomy-children';
}
?>

<?php if (!empty($items)): ?>
  <?php $children = element_children($items); ?>
  <section <?php print drupal_attributes($attributes_array); ?>>
    <?php $i = 0; ?>
    <?php foreach ($children as $child): ?>
      <?php $item_attributes['class'] = array(); ?>
      <?php $item_attributes['class'][] = (++$i % 2 !== 0) ? 'odd' : 'even'; ?>
      <?php if ($i % 3 === 0) $item_attributes['class'][] = 'third'; ?>
      <?php if ($i % 4 === 0) $item_attributes['class'][] = 'fourth'; ?>
      <?php if ($i % 5 === 0) $item_attributes['class'][] = 'fifth'; ?>
      <?php $items[$child]['#term']->attributes_array = $item_attributes; ?>
      <?php print render($items[$child]); ?>
    <?php endforeach; ?>
  </section>
<?php endif; ?>
