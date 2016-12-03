<?php
/**
 * @file
 * events.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function events_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__symposium';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -27;
  $handler->conf = array(
    'title' => 'Symposium',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'symposium',
    'access' => array(
      'plugins' => array(
        1 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'events' => 'events',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        2 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Promoted',
            'php' => 'if (isset($contexts[\'argument_entity_id:node_1\'])) {
$node = $contexts[\'argument_entity_id:node_1\']->data;
if ($node->promote){
return TRUE;
} else {
return FALSE;
}
}',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left_above' => NULL,
      'right_above' => NULL,
      'middle' => NULL,
      'left_below' => NULL,
      'right_below' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '2ac2ac8c-e73d-4675-8582-33196ad857c6';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'node_view__symposium';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-7296a071-84e5-4e42-81ac-2fa4deda4697';
  $pane->panel = 'bottom';
  $pane->type = 'block';
  $pane->subtype = 'bean-contact-us';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'pane__contact-us',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '7296a071-84e5-4e42-81ac-2fa4deda4697';
  $display->content['new-7296a071-84e5-4e42-81ac-2fa4deda4697'] = $pane;
  $display->panels['bottom'][0] = 'new-7296a071-84e5-4e42-81ac-2fa4deda4697';
  $pane = new stdClass();
  $pane->pid = 'new-0e19a1b3-6cef-400b-841c-3b7954676776';
  $pane->panel = 'left_above';
  $pane->type = 'block';
  $pane->subtype = 'bean-member-advantages';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => '%title',
    'override_title_heading' => 'div',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'pane__member-advantages',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '0e19a1b3-6cef-400b-841c-3b7954676776';
  $display->content['new-0e19a1b3-6cef-400b-841c-3b7954676776'] = $pane;
  $display->panels['left_above'][0] = 'new-0e19a1b3-6cef-400b-841c-3b7954676776';
  $pane = new stdClass();
  $pane->pid = 'new-1f7cf704-6459-47dd-8099-df69fb5f5d51';
  $pane->panel = 'left_below';
  $pane->type = 'block';
  $pane->subtype = 'bht_custom-event_program';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => 'Scientific program',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'program',
    'css_class' => 'pane__program',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '1f7cf704-6459-47dd-8099-df69fb5f5d51';
  $display->content['new-1f7cf704-6459-47dd-8099-df69fb5f5d51'] = $pane;
  $display->panels['left_below'][0] = 'new-1f7cf704-6459-47dd-8099-df69fb5f5d51';
  $pane = new stdClass();
  $pane->pid = 'new-8a872580-ac9b-4a65-b896-9f84cba75371';
  $pane->panel = 'right_above';
  $pane->type = 'block';
  $pane->subtype = 'bht_custom-event_sponsors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => '%title',
    'override_title_heading' => 'div',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'pane__events-sponsors',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '8a872580-ac9b-4a65-b896-9f84cba75371';
  $display->content['new-8a872580-ac9b-4a65-b896-9f84cba75371'] = $pane;
  $display->panels['right_above'][0] = 'new-8a872580-ac9b-4a65-b896-9f84cba75371';
  $pane = new stdClass();
  $pane->pid = 'new-b60e96c3-dd4d-4c9f-b539-e6ca3b7ecaa4';
  $pane->panel = 'right_below';
  $pane->type = 'block';
  $pane->subtype = 'bht_custom-event_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => 'Location and venue',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'venue',
    'css_class' => 'pane__venue',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'b60e96c3-dd4d-4c9f-b539-e6ca3b7ecaa4';
  $display->content['new-b60e96c3-dd4d-4c9f-b539-e6ca3b7ecaa4'] = $pane;
  $display->panels['right_below'][0] = 'new-b60e96c3-dd4d-4c9f-b539-e6ca3b7ecaa4';
  $pane = new stdClass();
  $pane->pid = 'new-469e3b9a-f3ae-4033-a78b-a1bdb77203f6';
  $pane->panel = 'top';
  $pane->type = 'node_content';
  $pane->subtype = 'node_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'links' => 0,
    'no_extras' => 1,
    'override_title' => 1,
    'override_title_text' => '',
    'identifier' => '',
    'link' => 0,
    'leave_node_title' => 1,
    'build_mode' => 'full',
    'context' => 'argument_entity_id:node_1',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'pane__main',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '469e3b9a-f3ae-4033-a78b-a1bdb77203f6';
  $display->content['new-469e3b9a-f3ae-4033-a78b-a1bdb77203f6'] = $pane;
  $display->panels['top'][0] = 'new-469e3b9a-f3ae-4033-a78b-a1bdb77203f6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-469e3b9a-f3ae-4033-a78b-a1bdb77203f6';
  $handler->conf['display'] = $display;
  $export['node_view__symposium'] = $handler;

  return $export;
}
