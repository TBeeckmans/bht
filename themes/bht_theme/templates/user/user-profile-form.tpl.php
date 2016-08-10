<?php theme_helper(__FILE__); ?>

<?php
/**
 * tpl file for user profile form
 */

// Hide language settings 
hide($form['locale']);
?>

<?php print render($form['account']['current_pass']); ?>
<?php print render($form['account']['current_pass_required_values']); ?>
<?php print render($form['account']['name']); ?>
<?php print render($form['account']['mail']); ?>

<div class="user-psw">
	<h3><?php print t('New password'); ?></h3>
	<?php print render($form['account']['pass']); ?>
</div>

<?php foreach (element_children($form) as $key): ?>
	<?php // Print everything that we haven't explicitly printed already ?>
	<?php print drupal_render($form[$key]); ?>
<?php endforeach; ?>
