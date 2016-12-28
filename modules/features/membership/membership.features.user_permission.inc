<?php
/**
 * @file
 * membership.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function membership_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer entityform types'.
  $permissions['administer entityform types'] = array(
    'name' => 'administer entityform types',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'delete any entityform'.
  $permissions['delete any entityform'] = array(
    'name' => 'delete any entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'delete own entityform'.
  $permissions['delete own entityform'] = array(
    'name' => 'delete own entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'edit any entityform'.
  $permissions['edit any entityform'] = array(
    'name' => 'edit any entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'edit own entityform'.
  $permissions['edit own entityform'] = array(
    'name' => 'edit own entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'view any entityform'.
  $permissions['view any entityform'] = array(
    'name' => 'view any entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'view own entityform'.
  $permissions['view own entityform'] = array(
    'name' => 'view own entityform',
    'roles' => array(
      'administrator' => 'administrator',
      'bht board' => 'bht board',
    ),
    'module' => 'entityform',
  );

  return $permissions;
}
