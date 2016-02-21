<?php
// If a link is set, get the link address
$linkurl = NULL;
if (isset($link) && !empty($link)) {
  // Get the link array
  while (!isset($link['url']) && gettype($link) == 'array') {
    $link = reset($link);
  }

  // Parse the link address from the link array
  if (isset($link['url']) && strlen($link['url']) > 0) {
    $linkurl = $link['url'];
    $text = preg_replace(
      array('/<a(\s+[^>]+)>/im', '/<a>/im'), array(
      '<span$1>',
      ''
    ), preg_replace(
        array(
          '/\s+href=[\'""](?:.+?)[\'""]/im',
          '/<\/a>/im'
        ), array('', '</span>'), $text
      )
    );
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
        <?php print render($text); ?>
      </div>
    <?php endif; ?>

    <?php if (!is_null($linkurl)): ?>
  </a>
<?php endif; ?>
</div>
