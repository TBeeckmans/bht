<?php theme_helper(__FILE__); ?>

<?php if (!empty($items)): ?>
  <?php $children = element_children($items); ?>
  <?php foreach ($children as $child): ?>
    <?php print render($items[$child]); ?>
  <?php endforeach; ?>
<?php endif; ?>
