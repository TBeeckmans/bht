<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 * Basetheme implementation to display a menu block.
 * All we do is change div to nav
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php
// Initialize
$tag = 'nav';
$no_wrapper = FALSE;
$class = '';

// Check if we have any classes at all
if ($classes) {
  // Prevent the wrapper from rendering
  if(preg_match('/(\<none\>){1}/', $classes, $matches) !== FALSE) {
    if((bool)array_shift($matches)) {
      // Don't wrap the content
      $no_wrapper = TRUE;
      // Remove the <none> class from the list
      $classes = str_replace($matches[0], '', $classes);
    }
  }

  // Show contextual links inside the wrapper with the original classes
  if(preg_match('/(contextual-links-region){1}/', $classes, $matches) !== FALSE && $no_wrapper === TRUE) {
    if((bool)array_shift($matches)) {
      // Add the wrapper again
      $no_wrapper = FALSE;
    }
  }

  if(preg_match('/(\<none:force\>){1}/', $classes, $matches) !== FALSE) {
    if((bool)array_shift($matches)) {
      // Don't wrap the content
      $no_wrapper = TRUE;
      // Remove the <none:force> class from the list
      $classes = str_replace($matches[0], '', $classes);
    }
  }

  // Change the wrapper tag
  if(preg_match('/(\<tag\:){1}([a-z]*){1}(\>){1}/', $classes, $matches) !== FALSE) {
    if(count($matches) == 4) {
      // Set the tag for the wrapper around the content
      $tag = $matches[2];
      // Remove the <tag:*> class from the list
      $classes = str_replace($matches[0], '', $classes);
    }
  }

  // Set the class attribute
  if(strlen($classes) > 0) {
    $class = 'class="' . $classes . '"';
  }
}
?>

<?php if (!$no_wrapper): ?>
  <<?php print $tag; ?> <?php print $class; ?>>
<?php endif; ?>

<?php if (!$no_wrapper): ?>
  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <div class="nav__title"><?php print $block->subject ?></div>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
<?php endif; ?>

<?php print $content ?>

<?php if (!$no_wrapper): ?>
  </<?php print $tag; ?>>
<?php endif; ?>
