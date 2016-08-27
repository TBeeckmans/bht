<?php
/**
 * @file
 * Template for a 2 column bricked panel layout.
 *
 * This template provides a two column panel display layout.
 * It is 5 rows high; the top middle and bottom rows contain 1 column,
 * while the second and fourth rows contain 2 columns.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left_above']: Content in the left column in row 2.
 *   - $content['right_above']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['left_below']: Content in the left column in row 4.
 *   - $content['right_below']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>

<div class="panel panel--2col-bricks"
  <?php if (!empty($css_id)): ?>
     id="<?php print $css_id; ?>"
  <?php endif; ?>
  >

  <?php if ($content['top']): ?>
    <div class="panel__item panel__item--top">
      <?php print $content['top']; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['left_above'] || $content['right_above']): ?>
    <div class="panel__item panel__item--above">
      <?php if ($content['left_above']): ?>
        <div class="panel__item panel__item--col-first">
          <?php print $content['left_above']; ?>
        </div>
      <?php endif; ?>

      <?php if ($content['right_above']): ?>
        <div class="panel__item panel__item--col-last">
          <?php print $content['right_above']; ?>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['middle']): ?>
    <div class="panel__item panel__item--middle">
      <?php print $content['middle']; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['left_below'] || $content['right_below']): ?>
    <div class="panel__item panel__item--below">
      <?php if ($content['left_below']): ?>
        <div class="panel__item panel__item--col-first">
          <?php print $content['left_below']; ?>
        </div>
      <?php endif; ?>

      <?php if ($content['right_below']): ?>
        <div class="panel__item panel__item--col-last">
          <?php print $content['right_below']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['bottom']): ?>
    <div class="panel__item panel__item--bottom">
      <?php print $content['bottom']; ?>
    </div>
  <?php endif; ?>

</div>
