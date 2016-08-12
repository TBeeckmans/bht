<?php theme_helper(__FILE__); ?>

<?php if (!empty($items)): ?>
  <?php $children = element_children($items); ?>
  <?php $i = 0; ?>
  <?php foreach ($children as $child): ?>
    <?php $item_attributes['class'] = array(); ?>
    <?php $item_attributes['class'][] = (++$i % 2 !== 0) ? 'odd' : 'even'; ?>
    <?php $items[$child]['#node']->attributes_array = $item_attributes; ?>
    <?php print render($items[$child]); ?>
  <?php endforeach; ?>
<?php endif; ?>
