<?php
/**
 * @file
 * events.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function events_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_symposium|node|events|form';
  $field_group->group_name = 'group_symposium';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'events';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Symposium',
    'weight' => '7',
    'children' => array(
      0 => 'field_venue',
      1 => 'field_program',
      2 => 'field_register',
      3 => 'field_sponsor',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Symposium',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-symposium field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups[''] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Symposium');

  return $field_groups;
}
