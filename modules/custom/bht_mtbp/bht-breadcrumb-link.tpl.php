<?php
/**
 * @file
 *
 * Default implementation of theme the_aim_breadcrumb_link
 *
 * available variables
 * @var String $title
 * @var String $path
 */
?>
<a class="breadcrumb__link" itemprop="item" href="<?php print $path ?>">
  <span class="breadcrumb__text" itemprop="name"><?php print $title ?></span>
</a>