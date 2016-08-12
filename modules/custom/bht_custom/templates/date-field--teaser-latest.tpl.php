<?php global $language; ?>

<?php if (is_null($timestamp_2)): ?>
  <div class="<?php print $css_block; ?>__date<?php if (!is_null($css_modifier)): ?> <?php print $css_block; ?>__date--<?php print $css_modifier; ?><?php endif; ?>">
      <?php print format_date($timestamp_1, 'custom', 'j F', NULL, $language->language); ?>
  </div>
<?php else: ?>
  <div class="<?php print $css_block; ?>__date<?php if (!is_null($css_modifier)): ?> <?php print $css_block; ?>__date--<?php print $css_modifier; ?><?php endif; ?>">
    <?php $start_date = format_date($timestamp_1, 'custom', 'j F', NULL, $language->language); ?>
    <?php $end_date = format_date($timestamp_2, 'custom', 'j F', NULL, $language->language); ?>
    <?php print t('From !startdate till !enddate', array('!startdate' => $start_date, '!enddate' => $end_date)); ?>
  </div>
<?php endif; ?>
