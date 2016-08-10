<?php theme_helper(__FILE__); ?>

<?php
// tpl file for user login form
extract($form);
// Hide password stuff so we can wrap it in a seperate wrapper
hide($account['pass']);
?>

<div class="user-details">
	<h3><?php print t('User details'); ?></h3>
	<?php print render($account); ?>
</div>

<div class="user-psw">
	<h3><?php print t('Password'); ?></h3>
	<?php print render($account['pass']); ?>
</div>

<?php if (isset($field_user_address)) { ?>
  <div class="user-address">
    <?php print render($field_user_address); ?>
  </div>
<?php } ?>

<?php print render($actions); ?>

<?php print render($form_id); // Display hidden elements ?>
<?php print render($form_build_id); // Display hidden elements ?>
