<?php
/**
 * @file
 * Add and/or alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function bht_custom_form_alter(&$form, &$form_state, $form_id) {
  kpr($form_id);
  // Add BEM styling to user forms
  switch ($form_id) {
    case 'user_login':
      $form['#attributes'] = array('class' => array('user__form', 'user__form--login'));
      break;

    case 'user_pass':
      $form['#attributes'] = array('class' => array('user__form', 'user__form--password'));
      break;

    case 'user_register_form':
      $form['#attributes'] = array('class' => array('user__form', 'user__form--register'));
      unset($form['account']['#type']);
      break;

    case 'user_profile_form':
      $form['#attributes'] = array('class' => array('user__form', 'user__form--profile'));
      unset($form['account']['#type']);
      break;

    case 'membership_entityform_edit_form':
      $form['field_standard_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__membership';
      $form['field_standard_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('member'));
      $form['field_standard_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '40.00';
      $form['field_dedicated_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__membership';
      $form['field_dedicated_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('member'));
      $form['field_dedicated_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '70.00';
      $parameters = drupal_get_query_parameters();
      if (!empty($parameters)) {
        if (array_key_exists('member', $parameters)) {
          $form['field_member_type'][LANGUAGE_NONE]['#default_value'] = $parameters['member'];
        }
      }

      break;

    default:
      break;
  }
}
