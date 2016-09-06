<?php
/**
 * Created by PhpStorm.
 * User: tbeeckmans
 * Date: 16/04/16
 * Time: 10:52
 */
hide($user_profile);

?>
<div class="physician__employee" itemprop="employee" itemscope itemtype="http://schema.org/Person">
  <span itemprop="givenName">
    <?php print render($user_profile['firstname']); ?>
  </span>
  <span itemprop="familyName">
    <?php print render($user_profile['lastname']); ?>
  </span>
  <?php if (!empty($user_profile['certification'])): ?>
    <div class="physician__certification">
      <?php print render($user_profile['certification']); ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($user_profile['mobile_phone'])): ?>
    <div class="physician__mobile-phone physician--icon" itemprop="telephone">
      <?php print render($user_profile['mobile_phone']); ?>
    </div>
  <?php endif; ?>
</div>
