<?php
/**
 * @file
 * Adds custom blocks to the site.
 */

/**
 * Implements hook_block_info().
 */
function bht_custom_block_info() {
  $block = array();

  $block['news_latest'] = array(
    'info' => t('Latest news'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  $block['event_promoted'] = array(
    'info' => t('Symposium'),
    'cache' => DRUPAL_CACHE_GLOBAL,
    'visibility' => BLOCK_VISIBILITY_LISTED,
    'pages' => '<front>',
    'region' => '-1',
    'status' => 1,
  );

  $block['event_promoted_cta'] = array(
    'info' => t('CTA Symposium'),
    'cache' => DRUPAL_CACHE_GLOBAL,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  $block['event_program'] = array(
    'info' => t('Event program'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  $block['event_location'] = array(
    'info' => t('Location and venue'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  $block['event_sponsors'] = array(
    'info' => t('Event sponsors'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  $block['sponsor_banner'] = array(
    'info' => t('Rel'),
    'cache' => DRUPAL_CACHE_GLOBAL,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'region' => '-1',
    'status' => 1,
  );

  return $block;
}

/**
 * Implements hook_block_view().
 */
function bht_custom_block_view($delta='') {
  $block = array();

  switch ($delta) {

    case 'news':
      $block['subject'] = t('News');
      $block['content'] = _content_news_overview();
      break;

    case 'news_latest':
      $block['subject'] = t('Latest news');
      $block['content'] = _content_news_latest();
      break;

    case 'event_promoted':
      $block['subject'] = NULL;
      $block['content'] = _content_event_promoted();
      break;

    case 'event_promoted_cta':
      $block['subject'] = NULL;
      $block['content'] = _content_event_promoted_cta();
      break;

    case 'event_program':
      $block['subject'] = t('Scientific program');
      $block['content'] = _content_event_program();
      break;

    case 'event_location':
      $block['subject'] = t('Location and venue');
      $block['content'] = _content_event_venue();
      break;

    case 'event_sponsors':
      $block['subject'] = t('Thank you conference sponsors');
      $block['content'] = _content_event_sponsors();
      break;

    case 'sponsor_banner':
      $block['subject'] = t('Location and venue');
      $block['content'] = _content_event_venue();
      break;

    default:
      break;

  }

  return $block;
}

/**
 * Implements hook_block_view_alter().
 */
/*function bht_custom_block_view_alter(&$data, &$block) { }*/
