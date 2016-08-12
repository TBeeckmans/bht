<?php global $language; ?>

<div class="<?php print $css_block; ?>__date">
  <span class="<?php print $css_block; ?>__day">
    <?php print format_date($timestamp, 'custom', 'j', NULL, $language->language); ?>
  </span>
  <span class="<?php print $css_block; ?>__month">
    <?php print format_date($timestamp, 'custom', 'F', NULL, $language->language); ?>
  </span>
  <span class="<?php print $css_block; ?>__year">
    <?php print format_date($timestamp, 'custom', 'Y', NULL, $language->language); ?>
  </span>
</div>
