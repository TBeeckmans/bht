<?php theme_helper(__FILE__); ?>

<?php
// If a link is set, get the link address
$linkurl = NULL;
if (isset($link) && !empty($link)) {
  // Parse the link address from the link array
  if (isset($link['#element']['url']) && strlen($link['#element']['url']) > 0) {
    $linkurl = $link['#element']['url'];

    // Add the title to the text if one is provided
    if (isset($link['#element']['title']) && strlen($link['#element']['title']) > 0 && $link['#element']['title'] !== $link['#element']['url']) {
      $link['#element']['attributes'] = array('class' => 'btn btn--more');
      $text = array($text, $link);
    }
  }
}
?>

<div class="banner__item">
<?php if (!is_null($linkurl)): ?>
  <a href="<?php print $linkurl; ?>" class="banner__link">
<?php endif; ?>

  <?php print render($item); ?>

  <?php if (!empty($text)): ?>
    <div class="banner__text">
      <?php if (!is_null($linkurl)): ?>
        <?php print theme_strip_links(render($text)); ?>
      <?php else: ?>
        <?php print render($text); ?>
      <?php endif; ?>
    </div>
  <?php endif; ?>

<?php if (!is_null($linkurl)): ?>
  </a>
<?php endif; ?>
</div>
