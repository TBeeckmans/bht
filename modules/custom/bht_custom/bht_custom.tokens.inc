<?php
/**
 * @file bht_custom.tokens.inc
 *
 * @description
 * Create tokens used in pathauto
 */


/**
 * Implements hook_token_info_alter().
 */
function bht_custom_token_info_alter(&$data) {
//  $data['tokens']['variable']['machine'] = array(
//    'name' => t('Machine overview path'),
//    'description' => t('Sanitized path for use in the url alias'),
//  );
//  $data['tokens']['variable']['second-hand'] = array(
//    'name' => t('Second-hand overview path'),
//    'description' => t('Sanitized path for use in the url alias'),
//  );
//  $data['tokens']['variable']['sector'] = array(
//    'name' => t('Sector overview path'),
//    'description' => t('Sanitized path for use in the url alias'),
//  );
}


/**
 * Implements hook_tokens().
 */
function bht_custom_tokens($obj_type, $tokens, array $data = array(), array $options = array()) {
  // Define variables
  $language_code = NULL;
  $obj = NULL;

  // Set the language code if provided
  if (isset($options['language'])) {
    $language_code = $options['language']->language;
  }
  else {
    global $language;
    $language_code = $language->language;
  }

  // Define the token replacements
  $replacements = array();

//  // Attempt to get the object
//  if ($obj_type == 'variable' && !empty($data)) {
//    // Loop over each object
//    foreach ($data as $objType => $obj) {
//      if (is_object($obj)) {
//        // Override the language code if the object provides one
//        $current_language_code = $language_code;
//        if (isset($obj->language))
//          $current_language_code = $obj->language;
//
//        // Loop over each token
//        foreach ($tokens as $name => $original) {
//          // Reinitialize the alias each time
//          $alias = '';
//
//          // Add logic for the custom tokens
//          switch ($name) {
//            case 'machine':
//              // Get the translation of the machine overview
//              $machine_nid = _get_translated_id(variable_get('the_aim_machine_overview_nid', '79'), 'node', $current_language_code);
//
//              // Get the alias
//              $alias = drupal_get_path_alias('node/' . $machine_nid, $current_language_code);
//
//              // Check if the alias is equal to the source path
//              if ($alias === 'node/' . $machine_nid) {
//                // Load the target object
//                if ($target = node_load($machine_nid)) {
//                  // Include the pathauto module
//                  module_load_include('inc','pathauto','pathauto');
//                  // Create the alias for the target object
//                  $new_alias = pathauto_create_alias('node', 'update', 'node/' . $machine_nid, array('node' => $target), $target->type, $current_language_code);
//                  // Set the new alias
//                  if (isset($new_alias['alias']))
//                    $alias = $new_alias['alias'];
//                  else
//                    $alias = '';
//                }
//              }
//              break;
//
//            case 'second-hand':
//              // Get the translation of the second-hand overview
//              $second_hand_nid = _get_translated_id(variable_get('the_aim_second_hand_overview_nid', '90'), 'node', $current_language_code);
//
//              // Get the alias
//              $alias = drupal_get_path_alias('node/' . $second_hand_nid, $current_language_code);
//
//              // Check if the alias is equal to the source path
//              if ($alias === 'node/' . $second_hand_nid) {
//                // Load the target object
//                if ($target = node_load($second_hand_nid)) {
//                  // Include the pathauto module
//                  module_load_include('inc','pathauto','pathauto');
//                  // Create the alias for the target object
//                  $new_alias = pathauto_create_alias('node', 'update', 'node/' . $second_hand_nid, array('node' => $target), $target->type, $current_language_code);
//                  // Set the new alias
//                  if (isset($new_alias['alias']))
//                    $alias = $new_alias['alias'];
//                  else
//                    $alias = '';
//                }
//              }
//              break;
//
//            case 'sector':
//              // Get the translation of the sector overview
//              $sector_nid = _get_translated_id(variable_get('the_aim_sector_overview_nid', '93'), 'node', $current_language_code);
//
//              // Get the alias
//              $alias = drupal_get_path_alias('node/' . $sector_nid, $current_language_code);
//
//              // Check if the alias is equal to the source path
//              if ($alias === 'node/' . $sector_nid) {
//                // Load the target object
//                if ($target = node_load($sector_nid)) {
//                  // Include the pathauto module
//                  module_load_include('inc','pathauto','pathauto');
//                  // Create the alias for the target object
//                  $new_alias = pathauto_create_alias('node', 'update', 'node/' . $sector_nid, array('node' => $target), $target->type, $current_language_code);
//                  // Set the new alias
//                  if (isset($new_alias['alias']))
//                    $alias = $new_alias['alias'];
//                  else
//                    $alias = '';
//                }
//              }
//              break;
//
//            default:
//              break;
//          }
//
//          // Add the alias as a replacement for the original token
//          $replacements[$original] = $alias;
//
//        }
//      }
//    }
//  }

  // Return the token replacements
  return $replacements;
}


/**
 * Generate a page with token info
 */
function custom_token_content() {

  // $the_aim_machine_overview__nid = '79';
  // variable_set('the_aim_machine_overview_nid', $the_aim_machine_overview__nid);

//  module_load_include('inc','pathauto','pathauto');
//
//  $node = node_load(76);
//  $token1 = pathauto_cleanstring(token_replace('[variable:machine]/[node:field-machine-category:parents:join:/]/[node:field-machine-category:name]/[node:title]', array('node' => $node)));
//
//  $term = taxonomy_term_load(5);
//  $token2 = pathauto_cleanstring(token_replace('[variable:machine]/[term:parents:join:/]/[term:name]', array('taxonomy_term' => $term)));
//
//  return array(
//    array(
//      '#markup' => 'This is a page to test the custom tokens',
//      '#prefix' => '<p>',
//      '#suffix' => '</p>',
//    ),
//    array(
//      '#markup' => $token1,
//      '#prefix' => '<p>',
//      '#suffix' => '</p>',
//    ),
//    array(
//      '#markup' => $token2,
//      '#prefix' => '<p>',
//      '#suffix' => '</p>',
//    )
//  );
}
