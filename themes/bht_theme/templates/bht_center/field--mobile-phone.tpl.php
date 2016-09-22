<?php theme_helper(__FILE__); ?>

<?php if (isset($items) && !empty($items)): ?>

  <?php if (!$label_hidden): ?>
    <?php // Define default label classes ?>
    <?php $label_attributes = array('class' => array('label')); ?>
    <?php if (isset($element['#label_display'])) $label_attributes['class'][] = "label--{$element['#label_display']}"; ?>
    <?php // Rebuild the title attributes ?>
    <?php $variables['title_attributes_array'] = array_merge_recursive($variables['title_attributes_array'], $label_attributes); ?>
    <?php $title_attributes = drupal_attributes($variables['title_attributes_array']); ?>
    <label<?php print $title_attributes; ?>><?php print $label ?></label>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>

    <?php if (isset($item['#markup']) && strlen($item['#markup']) > 0): ?>
      <?php $item['#markup'] = l($item['#markup'], 'tel:' . str_replace(array('(0)', ' '), array('', ''), $item['#markup']), array('attributes' => array('class' => array('contact__link', 'contact__link--mobile-phone')), 'html' => FALSE, 'external' => TRUE)); ?>
    <?php endif; ?>

    <?php print render($item); ?>

  <?php endforeach; ?>

<?php endif; ?>
