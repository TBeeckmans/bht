<?php theme_helper(__FILE__); ?>

<?php if (isset($items) && !empty($items)): ?>

  <?php if (!$label_hidden): ?>
  	<label class="contact__label label--<?php print $element['#label_display']; ?> <?php print $element['#label_display']; ?>" <?php print $title_attributes; ?>><?php print $label ?></label>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
  <?php endforeach; ?>

<?php endif; ?>
