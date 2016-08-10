<?php theme_helper(__FILE__); ?>

<?php
/**
 * tpl file for user login form
 */
extract($form);
?>

<?php print render($name); ?>

<?php print render($actions); ?>

<?php print render($form_id); // Display hidden elements (required for successful login) ?>
<?php print render($form_build_id); // Display hidden elements (required for successful login) ?>
