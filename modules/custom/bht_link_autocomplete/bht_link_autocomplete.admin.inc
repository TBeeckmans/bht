<?php

/**
 * Implements hook_FORM()
 */
function _bht_link_autocomplete_settings_form($form, &$form_state) {
  $storage = variable_get(BHT_LINK_AUTOCOMPLETE_SETTINGS, array());

  $form['bundle'] = array(
    '#type' => 'containter',
  );
  $enabled_entity_types = array(
    'node' => array(
      'title' => t("Content type"),
      'description' => t("Select the content type(s) the autocomplete should search in."),
    ),
    'taxonomy_term' => array(
      'title' => t("Taxonomy term"),
      'description' => t("Select the taxonomy vocabulary(ies) the autocomplete should search in."),
    ),
    'entityform_type' => array(
      'title' => t("Entity form"),
      'description' => t("Select the EForm type the autocomplete should search in."),
    ),
  );

  foreach ($enabled_entity_types as $entity_type => $info) {
    $options = _bht_link_autocomplete_get_bundle_list($entity_type);
    $form['bundle'][$entity_type] = array(
      '#type' => 'checkboxes',
      '#title' => $info['title'],
      '#description' => $info['description'],
      '#options' => $options,
      '#default_value' => isset($storage[$entity_type]) ? $storage[$entity_type] : array(),
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save"),
  );

  return $form;
}

/**
 * Implements hook_FORM_validate() for _bht_link_autocomplete_settings_form
 */
function _bht_link_autocomplete_settings_form_validate($form, &$form_state) {
}

/**
 * Implements hook_FORM_submit() for _bht_link_autocomplete_settings_form
 */
function _bht_link_autocomplete_settings_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  // Clean the submitted form data.
  foreach (array_keys($values) as $key) {
    if (in_array(
      $key,
      array(
        'submit',
        'form_build_id',
        'form_token',
        'form_id',
        'op',
      )
    )) {
      unset($values[$key]);
    }
  }

  // Check submitted data.
  foreach ($values as &$info) {
    foreach ($info as $key => $value) {
      if ($key !== $value) {
        unset($info[$key]);
      }
    }
  }

  // Store the new values.
  variable_set(BHT_LINK_AUTOCOMPLETE_SETTINGS, $values);

  drupal_set_message(t("Settings saved."));
}

/**
 * @param string $entity_type
 *
 * @return array
 * @throws Exception
 */
function _bht_link_autocomplete_get_bundle_list($entity_type = 'node') {
  $info = entity_get_info($entity_type);

  if (is_null($info)) {
    throw new \Exception(
      t(
        "The entity type @type is not configured on this website.", array(
                                                                    '@type' => $entity_type,
                                                                  )
      )
    );
  }

  $bundles = array();

  $excluded = variable_get(BHT_LINK_AUTOCOMPLETE_EXCLUDED, array());

  foreach ($info['bundles'] as $key => $value) {
    if (!isset($excluded[$entity_type]) || !in_array($key, $excluded[$entity_type])) {
      $bundles[$key] = $value['label'];
    }
  }

  return $bundles;
}