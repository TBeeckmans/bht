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

    default:
      break;
  }
}
