<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function bht_theme_form_system_theme_settings_alter(&$form, &$form_state) {
  // Create own settings.
  $bht_theme_settings = array(
    '#type' => 'fieldset',
    '#title' => t('BHT theme settings'),

    'css_to_keep' => array(
      '#type' => 'textarea',
      '#title' => t('CSS to keep'),
      '#description' => t('Enter the CSS files you wish to keep. Enter one filename per line. CSS from your own theme cannot be stripped.'),
      '#default_value' => theme_get_setting('css_to_keep'),
    ),

    'js_to_strip' => array(
      '#type' => 'textarea',
      '#title' => t('JS to strip'),
      '#description' => t('Enter the JS files you wish to strip. Enter one filename per line. JS from your own theme cannot be stripped.'),
      '#default_value' => theme_get_setting('js_to_strip'),
    ),
  );

  // Add settings to beginning of array.
  $form = array_reverse($form);
  $form['bht_theme_settings'] = $bht_theme_settings;
  $form = array_reverse($form);
}
