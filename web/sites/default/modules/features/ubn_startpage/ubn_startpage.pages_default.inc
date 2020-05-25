<?php
/**
 * @file
 * ubn_startpage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ubn_startpage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front';
  $page->task = 'page';
  $page->admin_title = 'front';
  $page->admin_description = '';
  $page->path = 'front';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'front';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Default',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Latest stories link list (UUID)',
        'keyword' => 'latest_stories_link_list',
        'name' => 'entity_uuid:node',
        'uuid' => '4292e4cb-a82f-4ba3-a468-41c7ac7b70f5',
        'id' => 1,
      ),
      1 => array(
        'identifier' => 'Search-widget links',
        'keyword' => 'node',
        'name' => 'entity_uuid:node',
        'uuid' => '56371bfa-65af-430d-8675-cc28b6d78c71',
        'id' => 2,
      ),
    ),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'front';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'services' => NULL,
      'search' => NULL,
      'news' => NULL,
      'promoted' => NULL,
      'promoted_top' => NULL,
      'navigation' => NULL,
      'messages' => NULL,
    ),
    'promoted_top' => array(
      'style' => 'naked',
    ),
    'news' => array(
      'style' => 'naked',
    ),
    'promoted' => array(
      'style' => 'naked',
    ),
    'search' => array(
      'style' => 'naked',
    ),
    'services' => array(
      'style' => 'naked',
    ),
    'main' => array(
      'style' => 'naked',
    ),
    'navigation' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = 'No Title';
  $display->uuid = 'b0bb68cb-13cf-4310-82a0-499fdb2f2d71';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ea3f5579-ce3d-4d53-a14a-726f1d81d213';
    $pane->panel = 'main';
    $pane->type = 'views_panes';
    $pane->subtype = 'library_list-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ea3f5579-ce3d-4d53-a14a-726f1d81d213';
    $display->content['new-ea3f5579-ce3d-4d53-a14a-726f1d81d213'] = $pane;
    $display->panels['main'][0] = 'new-ea3f5579-ce3d-4d53-a14a-726f1d81d213';
    $pane = new stdClass();
    $pane->pid = 'new-6f8ff259-1397-45f7-b4c6-a0d95f687f3a';
    $pane->panel = 'messages';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:beta-indicator';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '6f8ff259-1397-45f7-b4c6-a0d95f687f3a';
    $display->content['new-6f8ff259-1397-45f7-b4c6-a0d95f687f3a'] = $pane;
    $display->panels['messages'][0] = 'new-6f8ff259-1397-45f7-b4c6-a0d95f687f3a';
    $pane = new stdClass();
    $pane->pid = 'new-eeed91b1-56c6-43ab-b159-6098813eda7c';
    $pane->panel = 'navigation';
    $pane->type = 'front_page_blurbs_navigation';
    $pane->subtype = 'front_page_blurbs_navigation';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'eeed91b1-56c6-43ab-b159-6098813eda7c';
    $display->content['new-eeed91b1-56c6-43ab-b159-6098813eda7c'] = $pane;
    $display->panels['navigation'][0] = 'new-eeed91b1-56c6-43ab-b159-6098813eda7c';
    $pane = new stdClass();
    $pane->pid = 'new-e1fe5984-202d-4942-ab93-0b41cca68dd6';
    $pane->panel = 'news';
    $pane->type = 'latest_news_widget';
    $pane->subtype = 'latest_news_widget';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'context_entity_uuid:node_1',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e1fe5984-202d-4942-ab93-0b41cca68dd6';
    $display->content['new-e1fe5984-202d-4942-ab93-0b41cca68dd6'] = $pane;
    $display->panels['news'][0] = 'new-e1fe5984-202d-4942-ab93-0b41cca68dd6';
    $pane = new stdClass();
    $pane->pid = 'new-564b1454-9c7d-4497-8b20-3258f9912243';
    $pane->panel = 'promoted';
    $pane->type = 'front_page_blurbs';
    $pane->subtype = 'front_page_blurbs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '564b1454-9c7d-4497-8b20-3258f9912243';
    $display->content['new-564b1454-9c7d-4497-8b20-3258f9912243'] = $pane;
    $display->panels['promoted'][0] = 'new-564b1454-9c7d-4497-8b20-3258f9912243';
    $pane = new stdClass();
    $pane->pid = 'new-e1e92e85-a8e9-42aa-8d1a-3727c4ee87fa';
    $pane->panel = 'promoted_top';
    $pane->type = 'front_page_blurbs_primary';
    $pane->subtype = 'front_page_blurbs_primary';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e1e92e85-a8e9-42aa-8d1a-3727c4ee87fa';
    $display->content['new-e1e92e85-a8e9-42aa-8d1a-3727c4ee87fa'] = $pane;
    $display->panels['promoted_top'][0] = 'new-e1e92e85-a8e9-42aa-8d1a-3727c4ee87fa';
    $pane = new stdClass();
    $pane->pid = 'new-40c86ccc-6666-442a-a994-f89c035b8757';
    $pane->panel = 'search';
    $pane->type = 'search_widget';
    $pane->subtype = 'search_widget';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
      'slogan' => 'Search among <strong class="hidden-xs"> @number </strong> books, articles, magazines and more...',
      'placeholder' => 'Search for...',
      'aria_label' => 'Search in Supersök',
      'number_of_items' => '100000',
      'context' => 'context_entity_uuid:node_2',
      'dark_theme' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '40c86ccc-6666-442a-a994-f89c035b8757';
    $display->content['new-40c86ccc-6666-442a-a994-f89c035b8757'] = $pane;
    $display->panels['search'][0] = 'new-40c86ccc-6666-442a-a994-f89c035b8757';
    $pane = new stdClass();
    $pane->pid = 'new-2b2c36ca-fc2a-4599-9e20-4768481be88c';
    $pane->panel = 'services';
    $pane->type = 'views_panes';
    $pane->subtype = 'link_lists-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2b2c36ca-fc2a-4599-9e20-4768481be88c';
    $display->content['new-2b2c36ca-fc2a-4599-9e20-4768481be88c'] = $pane;
    $display->panels['services'][0] = 'new-2b2c36ca-fc2a-4599-9e20-4768481be88c';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front'] = $page;

  return $pages;

}
