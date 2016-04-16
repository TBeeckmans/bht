<?php theme_helper(__FILE__); ?>
<?php
if(_the_aim_get_environment() == THE_AIM_ENVIRONMENT_DEVELOP) {
  print "<!-- View mode: " . $view_mode . " -->";
}
?>

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
if (isset($content['mobile_phone']))
  hide($content['mobile_phone']);
if (isset($content['fax']))
  hide($content['fax']);
if (isset($content['vatin']))
  hide($content['vatin']);
if (isset($content['render_map']))
  hide($content['render_map']);
if (isset($content['field_cover_image']))
  hide($content['field_cover_image']);

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

$long = reset($long);
while (gettype($long) == 'array' && !isset($long['value'])) {
  $long = reset($long);
}
if (isset($long['value'])) {
  $long = $long['value'];
}
else {
  $long = 0;
}
?>

<div itemscope itemtype="http://schema.org/LocalBusiness" class="contact__item"<?php if(isset($lat[0]['value'])) print " data-lat=\"{$lat[0]['value']}\""; ?> <?php if(isset($long[0]['value'])) print " data-long=\"{$long[0]['value']}\""; ?> data-title="<?php print $title; ?>">

  <div class="contact__name" itemprop="name"><?php print $title; ?></div>

  <?php if (isset($content['street']) || isset($content['postal_code']) || isset($content['city']) || isset($content['country'])) : ?>
    <div class="contact__address" itemprop="address" itemscope itemtype="http://schema.org/PostalAddress">

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
    <div class="contact__email"><?php print render($content['email']); ?></div>
  <?php endif; ?>
  <?php if (isset($content['phone'])): ?>
    <div class="contact__phone"><?php print render($content['phone']); ?></div>
  <?php endif; ?>
  <?php if (isset($content['mobile_phone'])): ?>
    <div class="contact__mobile-phone"><?php print render($content['mobile_phone']); ?></div>
  <?php endif; ?>
  <?php if (isset($content['fax'])): ?>
    <div class="contact__fax"><?php print render($content['fax']); ?></div>
  <?php endif; ?>

  <?php if (isset($content['vatin'])): ?>
    <div class="contact__vat"><?php print render($content['vatin']); ?></div>
  <?php endif; ?>

  <?php print render($content); ?>

  <a href="https://maps.google.com?daddr=<?php print $lat; ?>,<?php print $long; ?>" class="contact__save"><?php print t('Get directions'); ?></a>

</div>
