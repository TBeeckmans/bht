<?php
/**
 * @file bht_custom.theme.inc
 *
 * @description
 * Add theming functions/templates etc.
 */



/**
 * Implements hook_theme().
 */
function bht_custom_theme() {
  $theme = array();

  $theme['date_created'] = array(
    'template' => 'templates/date-created',
    'variables' => array(
      'timestamp' => NULL,
      'css_block' => NULL,
      'css_modifier' => NULL,
    ),
  );

  $theme['date_field'] = array(
    'template' => 'templates/date-field',
    'variables' => array(
      'timestamp_1' => NULL,
      'timestamp_2' => NULL,
      'css_block' => NULL,
      'css_modifier' => NULL,
    ),
  );

  $theme['event_promoted'] = array(
    'template' => 'templates/event-promoted',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['action_current'] = array(
    'template' => 'templates/action-current',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['action_past'] = array(
    'template' => 'templates/action-past',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['recipe_related'] = array(
    'template' => 'templates/recipe-related',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['recipe_promoted'] = array(
    'template' => 'templates/recipe-promoted',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['recipe_sticky'] = array(
    'template' => 'templates/recipe-sticky',
    'variables' => array(
      'items' => NULL,
    ),
  );

  $theme['brand_banner'] = array(
    'template' => 'templates/brand-banner',
    'variables' => array(
      'items' => NULL,
    ),
  );

  return $theme;
}


/**
 * Add custom theme hook suggestions for the date field.
 * @param $variables
 */
function bht_custom_preprocess_date_field(&$variables) {
  if (isset($variables['css_block']) && !empty($variables['css_block'])) {
    $variables['theme_hook_suggestions'][] = $variables['theme_hook_original'] . '__' . drupal_clean_css_identifier($variables['css_block'], array(' ' => '_', '-' => '_', '/' => '_', '[' => '_', ']' => ''));
  }
  if (isset($variables['css_modifier']) && !empty($variables['css_modifier'])) {
    $variables['theme_hook_suggestions'][] = $variables['theme_hook_original'] . '__' . drupal_clean_css_identifier($variables['css_modifier'], array(' ' => '_', '-' => '_', '/' => '_', '[' => '_', ']' => ''));
  }
  if (isset($variables['css_block']) && !empty($variables['css_block'])
  && isset($variables['css_modifier']) && !empty($variables['css_modifier'])) {
    $variables['theme_hook_suggestions'][] = $variables['theme_hook_original'] . '__' . drupal_clean_css_identifier($variables['css_block'], array(' ' => '_', '-' => '_', '/' => '_', '[' => '_', ']' => '')) . '__' . drupal_clean_css_identifier($variables['css_modifier'], array(' ' => '_', '-' => '_', '/' => '_', '[' => '_', ']' => ''));
  }
}
