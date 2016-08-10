<?php theme_helper(__FILE__); ?>

<?php
/** 
 * tpl file for user login form
 */
extract($form);
?>

<div class="user__title">
  <?php print render($intro_message); ?>
</div>

<?php print render($name); ?>
<?php print render($pass); ?>

<div class="user__links">
	<?php print l(t('Forgot password'), 'user/password'); ?>
</div>

<?php print render($actions); ?>

<?php print render($form_id); // Display hidden elements (required for successful login) ?>
<?php print render($form_build_id); // Display hidden elements (required for successful login) ?>
