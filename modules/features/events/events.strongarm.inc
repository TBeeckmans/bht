<?php
/**
 * @file
 * events.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function events_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__events';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'promoted' => array(
        'custom_settings' => TRUE,
      ),
      'teaser_promoted' => array(
        'custom_settings' => TRUE,
      ),
      'logo' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'marker' => array(
        'custom_settings' => FALSE,
      ),
      'taxonomy_content' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '10',
        ),
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '11',
        ),
        'xmlsitemap' => array(
          'weight' => '12',
        ),
      ),
      'display' => array(
        'title' => array(
          'teaser' => array(
            'weight' => '2',
            'visible' => TRUE,
          ),
          'promoted' => array(
            'weight' => '7',
            'visible' => FALSE,
          ),
          'teaser_promoted' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '9',
            'visible' => FALSE,
          ),
          'logo' => array(
            'weight' => '1',
            'visible' => FALSE,
          ),
          'program' => array(
            'weight' => '1',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_events';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_events';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_enable_node__events';
  $strongarm->value = TRUE;
  $export['metatag_enable_node__events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_events';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_events';
  $strongarm->value = '1';
  $export['node_preview_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_events';
  $strongarm->value = 0;
  $export['node_submitted_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_events_pattern';
  $strongarm->value = '';
  $export['pathauto_node_events_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_news_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_news_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_events';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '1.0',
  );
  $export['xmlsitemap_settings_node_events'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_news';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.7',
  );
  $export['xmlsitemap_settings_taxonomy_term_news'] = $strongarm;

  return $export;
}
