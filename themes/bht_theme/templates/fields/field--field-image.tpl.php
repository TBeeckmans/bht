<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 *  HTML structure for image block
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

// Catch paragraph bundle as inline__image
if ($field_type_css == 'image' && $field_name_css == 'image') {
  $field_type_css = '';
  $field_name_css = 'inline-image';
}

// Build the item attributes array
$attributes = array('class' => array());
$attributes['class'][] = $field_name_css;
if (strlen($field_type_css) > 0) $attributes['class'][] = $field_type_css . '__' . $field_name_css;
?>


<?php if (isset($items) && !empty($items)): ?>

  <?php if (!$label_hidden): ?>
    <label<?php print $title_attributes; ?>><?php print $label ?></label>
  <?php endif; ?>

  <?php
  // Add default link classes
  $link_attributes = array('class' => array());
  foreach ($attributes['class'] as $class) {
    $link_attributes['class'][] = $class . '-link';
  }
  ?>

  <?php foreach ($items as $key => $item): ?>
    <?php
    if (isset($item['#item']['attributes'])) {
      $item_attributes = &$item['#item']['attributes'];
      $item_attributes = array_merge_recursive($item_attributes, $attributes);
    }
    else {
      $item['#item']['attributes'] = $attributes;
    }

    $item['#path']['options']['attributes'] = $link_attributes;

    ?>

    <?php print render($item); ?>

  <?php endforeach; ?>

<?php endif; ?>
