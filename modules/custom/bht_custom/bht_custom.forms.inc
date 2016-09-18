<?php
/**
 * @file
 * Add and/or alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function bht_custom_form_alter(&$form, &$form_state, $form_id) {
  // Add BEM styling to user forms.
  switch ($form_id) {
    case 'user_login':
      $form['#attributes'] = array(
        'class' => array(
          'user__form',
          'user__form--login',
        ),
      );
      break;

    case 'user_pass':
      $form['#attributes'] = array(
        'class' => array(
          'user__form',
          'user__form--password',
        ),
      );
      break;

    case 'user_register_form':
      $form['#attributes'] = array(
        'class' => array(
          'user__form',
          'user__form--register',
        ),
      );
      unset($form['account']['#type']);
      break;

    case 'user_profile_form':
      $form['#attributes'] = array(
        'class' => array(
          'user__form',
          'user__form--profile',
        ),
      );
      unset($form['account']['#type']);
      break;

    default:
      break;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function bht_custom_form_membership_entityform_edit_form_alter(&$form, &$form_state, $form_id) {
  // Add our custom validation to require a membership type.
  $form['#validate'][] = 'bht_custom_entityform_require_membership';

  // Add context to the membership types.
  $form['field_standard_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__membership';
  $form['field_standard_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('member'));
  $form['field_standard_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '4000';
  $form['field_dedicated_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__membership';
  $form['field_dedicated_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('member'));
  $form['field_dedicated_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '11500';

  // Handle the query parameters and set defaults.
  $parameters = drupal_get_query_parameters();
  if (!empty($parameters)) {
    if (array_key_exists('member', $parameters)) {
      switch ($parameters['member']) {
        case 'standard':
          $form['field_standard_member'][LANGUAGE_NONE]['#default_value'] = 1;
          break;

        case 'dedicated':
        case 'full':
          $form['field_dedicated_member'][LANGUAGE_NONE]['#default_value'] = 1;
          break;

        default:
          break;
      }
    }
  }
}

function bht_custom_entityform_require_membership(&$form, &$form_state) {
  $standard_member = FALSE;
  $dedicated_member = FALSE;

  // Get the values of field_standard & dedicated member.
  if (isset($form_state['values']['field_standard_member'][LANGUAGE_NONE][0]['value'])) {
    $standard_member = (bool) $form_state['values']['field_standard_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_dedicated_member'][LANGUAGE_NONE][0]['value'])) {
    $dedicated_member = (bool) $form_state['values']['field_dedicated_member'][LANGUAGE_NONE][0]['value'];
  }

  // Check for a single checked membership type.
  if ($standard_member xor $dedicated_member) {
    return TRUE;
  }

  // Set a form error if the above validation fails.
  form_set_error('field_standard_member', t('You need to chose between one of the two membership types'));

  return FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function bht_custom_form_symposium_registration_entityform_edit_form_alter(&$form, &$form_state, $form_id) {
  // Add our custom validation to require a membership type.
  $form['#validate'][] = 'bht_custom_entityform_require_attendee_type';

  // Add context to the membership types.
  $form['field_early_bird_bht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_bht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_bht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() < '1477958399') unset($form['field_early_bird_bht_member']);
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() < '1477958399') unset($form['field_early_bird_bhg_member']);
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() < '1477958399') unset($form['field_early_bird_efsht_member']);
  $form['field_early_bird_student'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_student'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_student'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '2500';
  if (time() < '1477958399') unset($form['field_early_bird_student']);
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '10000';
  if (time() < '1477958399') unset($form['field_early_bird_standard']);
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() >= '1477958399') unset($form['field_regular_bht_member']);
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() >= '1477958399') unset($form['field_regular_bhg_member']);
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() >= '1477958399') unset($form['field_regular_efsht_member']);
  $form['field_regular_student'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_student'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_student'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '3500';
  if (time() >= '1477958399') unset($form['field_regular_student']);
  $form['field_regular_standard'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_standard'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_standard'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '10000';
  if (time() >= '1477958399') unset($form['field_regular_standard']);

}

function bht_custom_entityform_require_attendee_type(&$form, &$form_state) {

  $early_bird_bht_member = FALSE;
  $early_bird_bhg_member = FALSE;
  $early_bird_efsht_member = FALSE;
  $early_bird_student = FALSE;
  $early_bird_standard = FALSE;
  $regular_bht_member = FALSE;
  $regular_bhg_member = FALSE;
  $regular_efsht_member = FALSE;
  $regular_student = FALSE;
  $regular_standard = FALSE;

  // Get the values of the ticket options.
  if (isset($form_state['values']['field_early_bird_bht_member'][LANGUAGE_NONE][0]['value'])) {
    $early_bird_bht_member = (bool) $form_state['values']['field_early_bird_bht_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_early_bird_bhg_member'][LANGUAGE_NONE][0]['value'])) {
    $early_bird_bhg_member = (bool) $form_state['values']['field_early_bird_bhg_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_early_bird_efsht_member'][LANGUAGE_NONE][0]['value'])) {
    $early_bird_efsht_member = (bool) $form_state['values']['field_early_bird_efsht_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_early_bird_student'][LANGUAGE_NONE][0]['value'])) {
    $early_bird_student = (bool) $form_state['values']['field_early_bird_student'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_early_bird_standard'][LANGUAGE_NONE][0]['value'])) {
    $early_bird_standard = (bool) $form_state['values']['field_early_bird_standard'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_regular_bht_member'][LANGUAGE_NONE][0]['value'])) {
    $regular_bht_member = (bool) $form_state['values']['field_regular_bht_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_regular_bhg_member'][LANGUAGE_NONE][0]['value'])) {
    $regular_bhg_member = (bool) $form_state['values']['field_regular_bhg_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_regular_efsht_member'][LANGUAGE_NONE][0]['value'])) {
    $regular_efsht_member = (bool) $form_state['values']['field_regular_efsht_member'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_regular_student'][LANGUAGE_NONE][0]['value'])) {
    $regular_student = (bool) $form_state['values']['field_regular_student'][LANGUAGE_NONE][0]['value'];
  }
  if (isset($form_state['values']['field_regular_standard'][LANGUAGE_NONE][0]['value'])) {
    $regular_standard = (bool) $form_state['values']['field_regular_standard'][LANGUAGE_NONE][0]['value'];
  }

  $checked_total = 0;
  if ($early_bird_bht_member) $checked_total++;
  if ($early_bird_bhg_member) $checked_total++;
  if ($early_bird_efsht_member) $checked_total++;
  if ($early_bird_student) $checked_total++;
  if ($early_bird_standard) $checked_total++;
  if ($regular_bht_member) $checked_total++;
  if ($regular_bhg_member) $checked_total++;
  if ($regular_efsht_member) $checked_total++;
  if ($regular_student) $checked_total++;
  if ($regular_standard) $checked_total++;

  // Check for a single ticket option.
  if ($checked_total === 1) {
    return TRUE;
  }

  // Set a form error if the above validation fails.
  form_set_error('field_profession', t('You need to chose between one of the ticket options'));

  return FALSE;

}