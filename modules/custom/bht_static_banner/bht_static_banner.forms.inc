<?php

/**
 * Callback for settings page.
 */
function bht_static_banner_form($form, &$form_state) {
  $values = variable_get(BHT_STATIC_BANNER_SETTINGS, array());
  
  $form = array();
  $form['#tree'] = TRUE;
  $form['#attached']['css'][] = drupal_get_path('module', 'bht_static_banner') . "/bht_static_banner.css";
  
  $form['settings_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Static banner settings')
  );
  $form['settings_fieldset']['bht_static_banner_frontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on frontpage'),
    '#description' => t('Should the static banner block appear on the frontpage?'),
    '#default_value' => isset($values['bht_static_banner_frontpage']) ? $values['bht_static_banner_frontpage'] : 0,
  );
  $form['settings_fieldset']['bht_static_banner_not_frontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on other pages'),
    '#description' => t('Should the static banner block appear on other pages than the frontpage?'),
    '#default_value' => isset($values['bht_static_banner_not_frontpage']) ? $values['bht_static_banner_not_frontpage'] : 1,
  );
  $form['settings_fieldset']['bht_static_banner_body'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show banner text'),
    '#description' => t('Does the static banner needs to contain text?'),
    '#default_value' => isset($values['bht_static_banner_body']) ? $values['bht_static_banner_body'] : 0,
  );
  
  // Content types of which we're sure they don't need a teaser and submenu overview.
  $to_exclude = array(
    'banner_slide' => TRUE,
    'block' => TRUE,
    'webform' => TRUE,
    'confirmation_mail' => TRUE,
  );
  $content_types = array();
  // Get all content types
  foreach (node_type_get_types() as $type) {
    if (!isset($to_exclude[$type->type]))
      $content_types[$type->type] = $type->name;
  }

  // Get all taxonomy vocabularies
  $vocabs = array();
  foreach (taxonomy_vocabulary_get_names() as $vocab) {
    $vocabs[$vocab->machine_name] = $vocab->name;
  }

  // Entity types to exclude
  $to_exclude = array(
    'i18n_translation' => TRUE,
    'node' => TRUE,
    'file' => TRUE,
    'taxonomy_term' => TRUE,
    'taxonomy_vocabulary' => TRUE,
    'user' => TRUE,
    'wysiwyg_profile' => TRUE,
    'commerce_customer_profile' => TRUE,
    'commerce_order' => TRUE,
    'commerce_line_item' => TRUE,
    'commerce_product' => TRUE,
  );
  $entities = array();
  // Get all entities
  foreach (entity_get_info() as $type => $info) {
    if (!isset($to_exclude[$type]))
      $entities[$type] = $info['label'];
  }  

  $form['static_banner_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Static banner instances')
  );
  $form['static_banner_fieldset']['bht_static_banner_ct_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Select the content types for which you\'d like to enable a static banner.'),
    '#default_value' => isset($values['bht_static_banner_ct_types']) ? $values['bht_static_banner_ct_types'] : array('page' => 'page'),
    '#options' => $content_types,
  );
  $form['static_banner_fieldset']['bht_static_banner_vocabs'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Vocabularies'),
    '#description' => t('Select the taxonomy vocabularies for which you\'d like to enable a static banner.'),
    '#default_value' => isset($values['bht_static_banner_vocabs']) ? $values['bht_static_banner_vocabs'] : array(),
    '#options' => $vocabs,
  );
  $form['static_banner_fieldset']['bht_static_banner_entities'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Entities'),
    '#description' => t('Select the special entities for which you\'d like to enable a static banner.'),
    '#default_value' => isset($values['bht_static_banner_entities']) ? $values['bht_static_banner_entities'] : array(),
    '#options' => $entities,
  );

  // create the adaptive image settings form
  $form['static_banner_image_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Static banner image settings')
  );
  
  $types = _get_enabled_banner_image_types();
  $settings = variable_get(BHT_STATIC_BANNER_ADAPTIVE_IMAGE_SETTINGS, array());
  $image_styles = _image_style_option_list();
  
  foreach ($types as $type) {
    $form['static_banner_image_settings'][$type] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => $type,
    );

    for ($i = 1; $i <= variable_get('cs_adaptive_image_breakpoint_count', 5); $i++) {
      $form['static_banner_image_settings'][$type][$i] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'inline-element-wrapper'
          ),
        ),
      );

      $form['static_banner_image_settings'][$type][$i]['breakpoint'] = array(
        '#type' => 'textfield',
        '#title' => t('Breakpoint'),
        '#default_value' => isset($settings[$type][$i]['breakpoint']) ? $settings[$type][$i]['breakpoint'] : NULL,
      );

      $form['static_banner_image_settings'][$type][$i]['style'] = array(
        '#type' => 'select',
        '#title' => t('Style'),
        '#options' => $image_styles,
        '#default_value' => isset($settings[$type][$i]['breakpoint']) ? $settings[$type][$i]['style'] : NULL,
      );
    }

    $form['static_banner_image_settings'][$type]['max_style'] = array(
      '#type' => 'select',
      '#title' => t('Default'),
      '#description' => t("Image style to use when no \":after\" pseudo-element has been defined on the BODY tag, or when the browser can't read the pseudo-element (everything below IE9, for example)."),
      '#options' => $image_styles,
      '#default_value' => isset($settings[$type]['max_style']) ? $settings[$type]['max_style'] : NULL,
    );

    $form['static_banner_image_settings'][$type]['fallback_style'] = array(
      '#type' => 'select',
      '#title' => t('Fallback'),
      '#description' => t("Image style to use when the client does not support JavaScript."),
      '#options' => $image_styles,
      '#default_value' => isset($settings[$type]['fallback_style']) ? $settings[$type]['fallback_style'] : NULL,
    );
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Submit function for our form.
 */
function bht_static_banner_form_submit($form, &$form_state) {  
  $values = _cleanup_form_submission($form_state['values']);
  
  $init_values = variable_get(BHT_STATIC_BANNER_SETTINGS, array('page' => 'page'));
  
  $static_banner_settings = array();
  foreach($values['settings_fieldset'] as $key => $value) {
    $static_banner_settings[$key] = $value;
  }
  foreach($values['static_banner_fieldset'] as $key => $value) {
    $static_banner_settings[$key] = $value;
  }
  variable_set(BHT_STATIC_BANNER_SETTINGS, $static_banner_settings);

  $field_names = array('static_banner_image', 'static_banner_body', 'static_banner_link');
  
  // Loop over the content types that don't need a static banner instance anymore.
  $diff_values = array_diff_assoc($values['static_banner_fieldset']['bht_static_banner_ct_types'], $init_values['bht_static_banner_ct_types']);
  foreach ($diff_values as $bundle => $val) {
    if (!$val) {
      foreach($field_names as $field_name) {
        $instance = field_info_instance('node', $field_name, $bundle);
        if (!is_null($instance)) {
          field_delete_instance($instance, FALSE);
        }
      }
    }
  }

  // Loop over the vocabs that don't need a static banner instance anymore.
  $diff_values = array_diff_assoc($values['static_banner_fieldset']['bht_static_banner_vocabs'], $init_values['bht_static_banner_vocabs']);
  foreach ($diff_values as $bundle => $val) {
    if (!$val) {
      foreach($field_names as $field_name) {
        $instance = field_info_instance('taxonomy_term', $field_name, $bundle);
        if (!is_null($instance)) {
          field_delete_instance($instance, FALSE);
        }
      }
    }
  }

  // Loop over the entities that don't need a static banner instance anymore.
  $diff_values = array_diff_assoc($values['static_banner_fieldset']['bht_static_banner_entities'], $init_values['bht_static_banner_entities']);
  $entities = entity_get_info();
  foreach ($diff_values as $entity_type => $val) {
    if (!$val) {
      // Get all entities
      foreach ($entities as $type => $info) {
        if ($type == $entity_type) {
          foreach ($info['bundles'] as $bundle => $bundle_info) {
            foreach($field_names as $field_name) {
              $instance = field_info_instance($entity_type, $field_name, $bundle);
              if (!is_null($instance)) {
                field_delete_instance($instance, FALSE);
              }
            }
          }
        }
      }
    }
  }

  // Check if the body banner field instances needs to be removed.
  if (($values['settings_fieldset']['bht_static_banner_body'] == FALSE) && ($init_values['bht_static_banner_body'] == TRUE)) {

    // Loop over the content types that don't need a body banner instance anymore.
    foreach ($values['static_banner_fieldset']['bht_static_banner_ct_types'] as $ct => $val) {
      if ($val) {
        $instance = field_info_instance('node', 'static_banner_body', $ct);
        if (!is_null($instance)) {
          field_delete_instance($instance, FALSE);
        }
      }
    }

    // Loop over the vocabs that don't need a body banner instance anymore.
    foreach ($values['static_banner_fieldset']['bht_static_banner_vocabs'] as $vocab => $val) {
      if ($val) {
        $instance = field_info_instance('taxonomy_term', 'static_banner_body', $vocab);
        if (!is_null($instance)) {
          field_delete_instance($instance, FALSE);
        }
      }
    }

    // Loop over the entities that don't need a body banner instance anymore.
    $entities = entity_get_info();
    foreach ($values['static_banner_fieldset']['bht_static_banner_entities'] as $entity_type => $val) {
      if ($val) {
        // Get all entities
        foreach ($entities as $type => $info) {
          if ($type == $entity_type) {
            foreach ($info['bundles'] as $bundle => $bundle_info) {
              $instance = field_info_instance($entity_type, 'static_banner_body', $bundle);
              if (!is_null($instance)) {
                field_delete_instance($instance, FALSE);
              }
            }
          }
        }
      }
    }
  }

  // Create the field instances on the defined content types
  $settings = array(
    'bht_static_banner_ct_types' => $values['static_banner_fieldset']['bht_static_banner_ct_types'],
    'bht_static_banner_vocabs' => $values['static_banner_fieldset']['bht_static_banner_vocabs'],
    'bht_static_banner_entities' => $values['static_banner_fieldset']['bht_static_banner_entities'],
    'bht_static_banner_body' => $values['settings_fieldset']['bht_static_banner_body']
  );
  _create_banner_instance($settings);
  
  $style_settings = array();
  $types = _get_enabled_banner_image_types();

  foreach ($types as $type) {
    if (isset($values['static_banner_image_settings'][$type])) {
      $style_settings[$type] = $values['static_banner_image_settings'][$type];
    }
  }

  variable_set(BHT_STATIC_BANNER_ADAPTIVE_IMAGE_SETTINGS, $style_settings);
  drupal_set_message(t("The settings where saved."));
  
  // Clear the cache to reflect the new settings on the administer display page
  drupal_flush_all_caches();
}
