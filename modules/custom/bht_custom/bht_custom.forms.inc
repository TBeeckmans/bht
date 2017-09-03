<?php
/**
 * @file
 * Add and/or alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function bht_custom_form_alter(&$form, &$form_state, $form_id) {
  $form_id = $form_id;
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
function bht_custom_form_events_node_form_alter(&$form, &$form_state, $form_id) {
  // @TODO: Check how to add form states to fieldgroups and hide the symposium.
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
  $form['field_shipping_identical']['#states'] = array(
    'visible' => array(
      ':input[name="field_dedicated_member[und]"]' => array('checked' => TRUE),
    ),
    'invisible' => array(
      ':input[name="field_dedicated_member[und]"]' => array('unchecked' => TRUE),
    ),
  );
  $form['field_shipping_address']['#states']
    = $form['field_shipping_postal_code']['#states']
    = $form['field_shipping_city']['#states'] = array(
    'visible' => array(
      ':input[name="field_shipping_identical[und]"]' => array('unchecked' => TRUE),
    ),
    'invisible' => array(
      ':input[name="field_shipping_identical[und]"]' => array('checked' => TRUE),
    ),
    'required' => array(
      ':input[name="field_shipping_identical[und]"]' => array('unchecked' => TRUE),
    ),
    'optional' => array(
      ':input[name="field_shipping_identical[und]"]' => array('checked' => TRUE),
    ),
  );

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
  if (time() > '1507510800') {
    unset($form['field_early_bird_bht_member']);
  }
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_bhg_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() > '1507510800') {
    unset($form['field_early_bird_bhg_member']);
  }
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_efsht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() > '1507510800') {
    unset($form['field_early_bird_efsht_member']);
  }
  $form['field_early_bird_student'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_student'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_student'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '2500';
  if (time() > '1507510800') {
    unset($form['field_early_bird_student']);
  }
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_early_bird_standard'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() > '1507510800') {
    unset($form['field_early_bird_standard']);
  }
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_bht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() <= '1507510800') {
    unset($form['field_regular_bht_member']);
  }
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_bhg_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() <= '1507510800') {
    unset($form['field_regular_bhg_member']);
  }
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_efsht_member'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '7500';
  if (time() <= '1507510800') {
    unset($form['field_regular_efsht_member']);
  }
  $form['field_regular_student'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_student'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_student'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '5000';
  if (time() <= '1507510800') {
    unset($form['field_regular_student']);
  }
  $form['field_regular_standard'][LANGUAGE_NONE]['#theme_wrappers'][] = 'form_element__register';
  $form['field_regular_standard'][LANGUAGE_NONE]['#wrapper_attributes'] = array('class' => array('register'));
  $form['field_regular_standard'][LANGUAGE_NONE]['#attributes_array']['data-price'] = '10000';
  if (time() <= '1507510800') {
    unset($form['field_regular_standard']);
  }

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
  if ($early_bird_bht_member) {
    $checked_total++;
  }
  if ($early_bird_bhg_member) {
    $checked_total++;
  }
  if ($early_bird_efsht_member) {
    $checked_total++;
  }
  if ($early_bird_student) {
    $checked_total++;
  }
  if ($early_bird_standard) {
    $checked_total++;
  }
  if ($regular_bht_member) {
    $checked_total++;
  }
  if ($regular_bhg_member) {
    $checked_total++;
  }
  if ($regular_efsht_member) {
    $checked_total++;
  }
  if ($regular_student) {
    $checked_total++;
  }
  if ($regular_standard) {
    $checked_total++;
  }

  // Check for a single ticket option.
  if ($checked_total === 1) {
    return TRUE;
  }

  // Set a form error if the above validation fails.
  form_set_error('field_profession', t('You need to chose between one of the ticket options'));

  return FALSE;

}

/**
 * Callback function to build a basic payment form.
 *
 * @param array $form
 *   The form build array.
 * @param array $form_state
 *   The form state information.
 * @param int $reference
 *   The payment context.
 */
function MYMODULE_form(&$form, $form_state, $reference) {
  // Define a payment object.
  $payment = new Payment();
  $payment->context = 'form/payment/' . $reference;
  $payment->context_data = array(
    'reference' => $reference,
  );
  $payment->currency_code = 'EUR';
  $payment->description = 'Basic payment form';
  $payment->finish_callback = 'MYMODULE_finish_callback';

  // Define a payment line item.
  $line_item = new PaymentLineItem();
  $line_item->amount = 100.00 / 1.21;
  $line_item->name = t('EUR 100');
  $line_item->tax_rate = 0.21;
  $line_item->quantity = 1;

  // Add the payment line item to the payment object.
  $payment->setLineItem($line_item);

  // Add the payment object to the form.
  $form_state['payment'] = $payment;

  // Get available payment methods and limit this form to Mollie payment.
  $payment_methods = $payment->availablePaymentMethods();
  $payment_options = array();
  foreach ($payment_methods as $payment_method) {
    if ($payment_method->enabled && $payment_method->name == 'pay_with_mollie') {
      $payment_options[] = $payment_method->pmid;
    }
  }

  // Get the payment embed elements.
  $payment_embed_form = payment_form_embedded($form_state, $payment, $payment_options);

  // Add the embedded payment form element.
  $form['payment'] = $payment_embed_form['elements'];

  // Define the form submit callback.
  $form['#submit'] = $payment_embed_form['submit'];

  // Add form actions.
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Pay with Mollie'),
  );

  return $form;
}

/**
 * Handle successful payment from Mollie.
 *
 * @param \Payment $payment
 *   The returned payment object containing all relevant information.
 */
function MYMODULE_finish_callback(Payment $payment) {
  $payment_complete = FALSE;

  // Check if the payment status contains a successful state.
  foreach ($payment->statuses as $status) {
    if ($status->status == 'payment_status_success') {
      $payment_complete = FALSE;
    }
  }

  if ($payment_complete) {
    // @TODO: Implement custom callbacks.
  }
}


