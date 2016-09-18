<?php
/**
 * @file
 * Add and/or alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function bht_custom_form_alter(&$form, &$form_state, $form_id) {
  // Add BEM styling to user forms
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
      $form['field_member_type'][LANGUAGE_NONE]['#default_value'] = $parameters['member'];
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
  if ($standard_member XOR $dedicated_member) {
    return FALSE;
  }

  // Set a form error if the above validation fails.
  form_set_error('field_standard_member', t('You need to chose between one of the two membership types'));

  return FALSE;

}