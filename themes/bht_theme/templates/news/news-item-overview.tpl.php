<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 * Theme implementation to display an overview of news items.
 *
 * Available variables:
 * - $items: the list of renderable nodes.
 */
?>

<?php $i = 0; ?>

<?php foreach (element_children($items) as $nid): ?>
  <?php $item_attributes = array('class' => array('')); ?>
  <?php $item_attributes['class'][] = (++$i%2 !== 0) ? 'odd' : 'even'; ?>
  <?php if ($i%3 === 0) $item_attributes['class'][] = 'third'; ?>
  <?php if ($i%4 === 0) $item_attributes['class'][] = 'fourth'; ?>
  <?php $items[$nid]['#node']->attributes_array = $item_attributes; ?>
  <?php print render($items[$nid]) ?>
<?php endforeach; ?>

  <?php if (isset($pager)):?>
    <?php print render($pager);?>
  <?php endif; ?>
