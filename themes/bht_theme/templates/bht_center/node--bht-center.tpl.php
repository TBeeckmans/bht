<?php theme_helper(__FILE__); ?>

<?
/**
 * @file
 * Default theme implementation to display a contact node.
 */
?>

<?php
hide($content['comments']);
hide($content['links']);
if (isset($content['language']))
  hide($content['language']);
if (isset($content['lat']))
  hide($content['lat']);
if (isset($content['long']))
  hide($content['long']);
if (isset($content['street']))
  hide($content['street']);
if (isset($content['number']))
  hide($content['number']);
if (isset($content['bus']))
  hide($content['bus']);
if (isset($content['postal_code']))
  hide($content['postal_code']);
if (isset($content['city']))
  hide($content['city']);
if (isset($content['country']))
  hide($content['country']);
if (isset($content['email']))
  hide($content['email']);
if (isset($content['phone']))
  hide($content['phone']);
if (isset($content['therapist']))
  hide($content['therapist']);
if (isset($content['fax']))
  hide($content['fax']);
if (isset($content['title']))
  hide($content['title']);

$lat = reset($lat);
while (gettype($lat) == 'array' && !isset($lat['value'])) {
  $lat = reset($lat);
}
if (isset($lat['value'])) {
  $lat = $lat['value'];
}
else {
  $lat = 0;
}

$lng = reset($lng);
while (gettype($lng) == 'array' && !isset($lng['value'])) {
  $lng = reset($lng);
}
if (isset($lng['value'])) {
  $lng = $lng['value'];
}
else {
  $lng = 0;
}
?>


<div itemscope itemtype="//schema.org/Physician"
     class="physician__item"
     <?php if (isset($lat)): ?>
       data-lat="<?php print $lat; ?>"
     <?php endif; ?>
     <?php if (isset($lng)): ?>
       data-long="<?php print $lng; ?>"
     <?php endif; ?>
     data-title="<?php print $title; ?>">

  <div class="layout__physician--left">

    <h1 class="physician__name" itemprop="name"><?php print $title; ?></h1>

    <?php if (isset($content['street']) || isset($content['postal_code']) || isset($content['city']) || isset($content['country'])) : ?>
      <div class="physician__address" itemprop="address" itemscope itemtype="//schema.org/PostalAddress">
        <?php if (isset($content['street'])): ?>
          <span itemprop="streetAddress">
        <?php print render($content['street']); ?>
        <?php if (isset($content['number'])) print render($content['number']); ?>
        <?php if (isset($content['bus'])) print render($content['bus']); ?>
      </span><br>
        <?php endif; ?>

        <?php if (isset($content['postal_code'])): ?>
          <span itemprop="postalCode"><?php print render($content['postal_code']); ?></span>
        <?php endif; ?>

        <?php if (isset($content['city'])): ?>
          <span itemprop="addressLocality"><?php print render($content['city']); ?></span><br>
        <?php endif; ?>

        <?php if (isset($content['country'])): ?>
          <span itemprop="addressCountry"><?php print render($content['country']); ?></span>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (isset($content['email'])): ?>
      <div class="physician__email"><?php print render($content['email']); ?></div>
    <?php endif; ?>
    <?php if (isset($content['phone'])): ?>
      <div class="physician__phone"><?php print render($content['phone']); ?></div>
    <?php endif; ?>
    <?php if (isset($content['fax'])): ?>
      <div class="physician__fax"><?php print render($content['fax']); ?></div>
    <?php endif; ?>

  </div>

  <div class="layout__physician--right">
    <?php print render($content); ?>
  </div>

</div>
