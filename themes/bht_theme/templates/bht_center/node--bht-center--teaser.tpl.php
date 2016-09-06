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
if (isset($content['language'])) {
  hide($content['language']);
}
if (isset($content['lat'])) {
  hide($content['lat']);
}
if (isset($content['long'])) {
  hide($content['long']);
}
if (isset($content['street'])) {
  hide($content['street']);
}
if (isset($content['number'])) {
  hide($content['number']);
}
if (isset($content['bus'])) {
  hide($content['bus']);
}
if (isset($content['postal_code'])) {
  hide($content['postal_code']);
}
if (isset($content['city'])) {
  hide($content['city']);
}
if (isset($content['country'])) {
  hide($content['country']);
}
if (isset($content['email'])) {
  hide($content['email']);
}
if (isset($content['phone'])) {
  hide($content['phone']);
}
if (isset($content['therapist'])) {
  hide($content['therapist']);
}

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

<div itemscope itemtype="http://schema.org/Physician"
     class="physician__item"
  <?php if (isset($lat)): ?>
    data-lat="<?php print $lat; ?>"
  <?php endif; ?>
  <?php if (isset($lng)): ?>
    data-long="<?php print $lng; ?>"
  <?php endif; ?>
     data-title="<?php print $title; ?>">

  <div class="physician__name" itemprop="legalName"><?php print $title; ?></div>

  <div class="physician__memberof" itemprop="memberOf">
    <?php
    print l(
      t('Belgian Hand Therapists'),
      'http://www.belgianhandtherapists.be',
      array(
        'attributes' => array(
          'class' => array('physician__link'),
          'itemprop' => 'url',
        ),
      )
    );
    ?>
  </div>

  <div class="physician__specialty">
    <?php print t('Treatment specialty:') ?>
    <span itemprop="medicalSpecialty">
      <?php print t('hand therapy'); ?>,
    </span>
    <span itemprop="medicalSpecialty">
      <?php print t('hand injury revalidation'); ?>,
    </span>
    <span itemprop="medicalSpecialty">
    <?php print t('upper limb revalidation'); ?>
    </span>
  </div>

  <?php if (isset($content['street']) || isset($content['postal_code']) || isset($content['city']) || isset($content['country'])) : ?>
    <div class="physician__address physician--icon" itemprop="address" itemscope
         itemtype="http://schema.org/PostalAddress">

      <?php if (isset($content['street'])): ?>
        <span itemprop="streetAddress">
        <?php print render($content['street']); ?>
        <?php if (isset($content['number'])) {
          print render($content['number']);
        } ?>
        <?php if (isset($content['bus'])) {
          print render($content['bus']);
        } ?>
      </span><br>
      <?php endif; ?>

      <?php if (isset($content['postal_code'])): ?>
        <span itemprop="postalCode">
          <?php print render($content['postal_code']); ?>
        </span>
      <?php endif; ?>

      <?php if (isset($content['city'])): ?>
        <span itemprop="addressLocality">
          <?php print render($content['city']); ?>
        </span>
        <br>
      <?php endif; ?>

      <?php if (isset($content['country'])): ?>
        <span itemprop="addressCountry">
          <?php print render($content['country']); ?>
        </span>
      <?php endif; ?>

    </div>
  <?php endif; ?>


  <?php if (isset($content['email'])): ?>
    <div class="physician__email physician--icon" itemprop="email">
      <?php print render($content['email']); ?>
    </div>
  <?php endif; ?>
  <?php if (isset($content['phone'])): ?>
    <div class="physician__phone physician--icon" itemprop="telephone">
      <?php print render($content['phone']); ?>
    </div>
  <?php endif; ?>
  <?php if (isset($content['fax'])): ?>
    <div class="physician__fax physician--icon" itemprop="faxNumber">
      <?php print render($content['fax']); ?>
    </div>
  <?php endif; ?>

  <?php if (isset($content['therapist'])): ?>
    <div class="physician__employees physician--icon">
    <?php foreach (element_children($content['therapist']) as $thid): ?>
      <?php print render($content['therapist'][$thid]); ?>
    <?php endforeach; ?>
    </div>
  <?php endif; ?>

  <?php print render($content); ?>

  <a
    href="https://maps.google.com?daddr=<?php print $lat; ?>,<?php print $lng; ?>"
    class="physician__save physician--icon"><?php print t('Get directions'); ?></a>

</div>
