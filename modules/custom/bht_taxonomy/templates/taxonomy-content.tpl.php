<?php
/**
 * Template for the custom taxonomy implementation
 * Displays taxonomy content
 */

$css_block = '';
if (isset($vid)) {
  // Load the vocabulary
  $vocab = taxonomy_vocabulary_load($vid);

  // Determine the BEM block name
  $css_block = drupal_clean_css_identifier($vocab->machine_name);
}
else {
  watchdog('taxonomy', 'The render array of taxonomy content is missing the vid. Did you override the taxonomy content without adding it back in?', array(), WATCHDOG_WARNING);
}

// Add the BEM default class
$attributes_array['class'][] = 'taxonomy-content';

// Add the BEM specific vocab class
if (strlen($css_block) > 0) {
  $attributes_array['class'][] = $css_block . '__taxonomy-content';
}
?>


<?php if (!empty($items)): ?>
  <?php $children = element_children($items); ?>
  <section <?php print drupal_attributes($attributes_array); ?>>
    <?php $i = 0; ?>
    <?php foreach($children as $child):  ?>
      <?php $item_attributes['class'] = array(); ?>
      <?php $css_modifier = ''; ?>
      <?php if (isset($items[$child]['#view_mode'])) $css_modifier = drupal_clean_css_identifier($items[$child]['#view_mode']); ?>
      <?php $item_attributes['class'][] = 'content-item'; ?>
      <?php if (strlen($css_block) > 0) $item_attributes['class'][] = $css_block . '__content-item'; ?>
      <?php if (strlen($css_block) > 0 && strlen($css_modifier) > 0) $item_attributes['class'][] = $css_block . '__content-item--' . $css_modifier; ?>
      <?php $item_attributes['class'][] = (++$i % 2 !== 0) ? 'odd' : 'even'; ?>
      <?php if ($i % 3 === 0) $item_attributes['class'][] = 'third'; ?>
      <?php if ($i % 4 === 0) $item_attributes['class'][] = 'fourth'; ?>
      <?php if ($i % 5 === 0) $item_attributes['class'][] = 'fifth'; ?>
      <?php $items[$child]['#node']->attributes_array = $item_attributes; ?>
      <?php print drupal_render($items[$child]); ?>
    <?php endforeach; ?>
  </section>
<?php endif; ?>
