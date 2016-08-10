<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 *  HTML structure for image block
 */

$classes_array = array('gallery__list', 'gallery__list--block', 'js-gallery-fade');
if (!empty($items)) {
  $item = current($items);
  if (isset($item['#path']['path']) && strlen($item['#path']['path']) > 0) {
    $classes_array[] = 'js-colorbox';
  }
}
$classes = implode(' ', $classes_array);
?>


<?php if (isset($items) && !empty($items)): ?>

  <?php if (!$label_hidden): ?>
    <label<?php print $title_attributes; ?>><?php print $label ?></label>
  <?php endif; ?>

  <ul class="<?php print $classes; ?>">
    <?php $i = 0; ?>
    <?php foreach ($items as $key => $item): ?>
      <?php $li_attributes = array('class' => array('gallery__item')); ?>
      <?php // Add attributes to the list item ?>
      <?php if (++$i == 1) $li_attributes['class'][] = 'first'; ?>
      <?php $li_attributes['class'][] = ($i%2 === 0) ? 'even' : 'odd'; ?>
      <?php if ($i%3 === 0) $li_attributes['class'][] = 'third'; ?>
      <?php if ($i%4 === 0) $li_attributes['class'][] = 'fourth'; ?>
      <?php if ($i%5 === 0) $li_attributes['class'][] = 'fifth'; ?>

      <?php // Add attributes to the image link ?>
      <?php if (isset($item['#path']['path']) && strlen($item['#path']['path']) > 0): ?>
        <?php $item['#path']['options'] = array('attributes' => array('class' => array('gallery__item-link'))); ?>
      <?php endif; ?>

      <?php // Add attributes to the image ?>
      <?php $attributes = array('class' => array('gallery__image'));
      if (isset($item['#item']['attributes'])) {
        $item_attributes = &$item['#item']['attributes'];
        $item_attributes = array_merge_recursive($item_attributes, $attributes);
      }
      else {
        $item['#item']['attributes'] = $attributes;
      }
      ?>

      <li <?php print drupal_attributes($li_attributes); ?>>
        <?php print render($item); ?>
      </li>
    <?php endforeach; ?>
  </ul>

<?php endif; ?>
