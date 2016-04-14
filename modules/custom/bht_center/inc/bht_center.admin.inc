<?php

/**
 * Implements hook_form().
 */
function _bht_center_settings_form($node, &$form_state) {
  $form = array();
  $map_options = variable_get(BHT_CENTER_JS_MAP_OPTIONS, 'a:0:{}');

  $form['node_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('BHT Center node bundle options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['node_options']['generate_lat_long'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto generate lat long cors'),
    '#default_value' => variable_get(BHT_CENTER_GENERATE_LAT_LNG, 1),
  );

  $form['map_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google map options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // Group map_option elements for processing purposes.
    '#tree' => TRUE,
  );

  // The MapType control lets the user toggle between map types
  // (such as ROADMAP and SATELLITE).
  // This control appears by default in the top right corner of the map.
  $form['map_options']['map_type_control'] = array(
    '#type' => 'radios',
    '#title' => t('Map type control'),
    '#description' => t('The MapType control lets the user toggle between map types (such as ROADMAP and SATELLITE). This control appears by default in the top right corner of the map.'),
    '#default_value' => isset($map_options['map_type_control']) ? $map_options['map_type_control'] : 0,
    '#options' => array(0 => t('False'), 1 => t('True')),
  );

  // The streetViewControl enables/disables the Pegman control that lets
  // the user activate a Street View panorama.
  // This control appears by default near the bottom right of the map.
  $form['map_options']['street_view_control'] = array(
    '#type' => 'radios',
    '#title' => t('Street view control'),
    '#description' => t('The streetViewControl property lets the user activate a Street View panorama on the map.'),
    '#default_value' => isset($map_options['street_view_control']) ? $map_options['street_view_control'] : 0,
    '#options' => array(0 => t('False'), 1 => t('True')),
  );

  // The disableDefaultUI property disables any automatic UI behavior
  // from the Google Maps API.
  $form['map_options']['disable_default_ui'] = array(
    '#type' => 'radios',
    '#title' => t('Disable default map ui'),
    '#description' => t('The disableDefaultUI property disables any automatic UI behavior from the Google Maps API.'),
    '#default_value' => isset($map_options['disable_default_ui']) ? $map_options['disable_default_ui'] : 0,
    '#options' => array(0 => t('False'), 1 => t('True')),
  );

  $form['map_options']['default_zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Default zoom'),
    '#required' => TRUE,
    '#default_value' => isset($map_options['default_zoom']) ? $map_options['default_zoom'] : 8,
  );

  $form['map_options']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google maps API key'),
    '#required' => FALSE,
    '#default_value' => isset($map_options['api_key']) ? $map_options['api_key'] : '',
  );

  // Set custom styles as a JSON object generated on
  // http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/index.html
  $form['map_options']['custom_style'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom style JSON object'),
    '#description' => t('Add a JSON object to alter the google map, generate JSON object on http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/index.html.'),
    '#default_value' => isset($map_options['custom_style']) ? $map_options['custom_style'] : '',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validation _bht_center_settings_form validation handler.
 */
function _bht_center_settings_form_validate($node, &$form_state) {
  $values = (object) $form_state['values'];

  // Validate JSON.
  if (!empty($values->map_options['custom_style'])) {
    json_decode($values->map_options['custom_style']);
    switch (json_last_error()) {
      case JSON_ERROR_NONE:
        break;
      
      case JSON_ERROR_DEPTH:
        form_set_error('custom_style', 'Maximum stack depth exceeded');
        break;
      
      case JSON_ERROR_STATE_MISMATCH:
        form_set_error('custom_style', 'Underflow or the modes mismatch');
        break;
      
      case JSON_ERROR_CTRL_CHAR:
        form_set_error('custom_style', 'Unexpected control character found');
        break;
      
      case JSON_ERROR_SYNTAX:
        form_set_error('custom_style', 'Syntax error, malformed JSON');
        break;
      
      case JSON_ERROR_UTF8:
        form_set_error('custom_style', 'Malformed UTF-8 characters, possibly incorrectly encoded');
        break;
      
      default:
        form_set_error('custom_style', 'Unknown error');
        break;
    }
  }
}

/**
 * _bht_center_settings_form submit handler.
 */
function _bht_center_settings_form_submit($node, &$form_state) {
  $values = (object)$form_state['values'];

  variable_set(BHT_CENTER_GENERATE_LAT_LNG, $values->generate_lat_long);

  // Create a variable containing all custom javascript map options.
  variable_set(BHT_CENTER_JS_MAP_OPTIONS, $values->map_options);

  drupal_set_message(t('Values saved'));
}
