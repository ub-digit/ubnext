<?php
/**
 * @file
 * ubn_page.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ubn_page_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__navigation-landing';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -22;
  $handler->conf = array(
    'title' => 'Navigation landing',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'navigation-landing',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'navigation_landing' => 'navigation_landing',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol_full';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'header' => NULL,
      'promoted_top' => NULL,
      'main_top' => NULL,
      'promoted' => NULL,
      'messages' => NULL,
    ),
    'main' => array(
      'style' => 'naked',
    ),
    'header' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'b6f36589-9536-420c-8d41-57a59f9d4348';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ce69a7ac-895b-4e74-96e3-1054f934577b';
    $pane->panel = 'header';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-head';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = 'ce69a7ac-895b-4e74-96e3-1054f934577b';
    $display->content['new-ce69a7ac-895b-4e74-96e3-1054f934577b'] = $pane;
    $display->panels['header'][0] = 'new-ce69a7ac-895b-4e74-96e3-1054f934577b';
    $pane = new stdClass();
    $pane->pid = 'new-42a20fe0-8b58-4b7d-bbd7-cfaa600af309';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:content-sections';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
      'override_title' => 0,
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
    $pane->uuid = '42a20fe0-8b58-4b7d-bbd7-cfaa600af309';
    $display->content['new-42a20fe0-8b58-4b7d-bbd7-cfaa600af309'] = $pane;
    $display->panels['main'][0] = 'new-42a20fe0-8b58-4b7d-bbd7-cfaa600af309';
    $pane = new stdClass();
    $pane->pid = 'new-a0a45809-6ee5-4758-b7fb-10a998c8fa73';
    $pane->panel = 'main';
    $pane->type = 'sub_menu_items';
    $pane->subtype = 'sub_menu_items';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a0a45809-6ee5-4758-b7fb-10a998c8fa73';
    $display->content['new-a0a45809-6ee5-4758-b7fb-10a998c8fa73'] = $pane;
    $display->panels['main'][1] = 'new-a0a45809-6ee5-4758-b7fb-10a998c8fa73';
    $pane = new stdClass();
    $pane->pid = 'new-c33077d5-1d92-47fd-840e-cdc7b28876f5';
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
    $pane->uuid = 'c33077d5-1d92-47fd-840e-cdc7b28876f5';
    $display->content['new-c33077d5-1d92-47fd-840e-cdc7b28876f5'] = $pane;
    $display->panels['messages'][0] = 'new-c33077d5-1d92-47fd-840e-cdc7b28876f5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__navigation-landing'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_2a4b8744-508b-4c0f-bd8f-86a4fa9d91f3';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -26;
  $handler->conf = array(
    'title' => 'Library',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'library' => 'library',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol_full';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'header' => NULL,
      'promoted_top' => NULL,
      'main_top' => NULL,
      'promoted' => NULL,
      'messages' => NULL,
      'banner' => NULL,
    ),
    'main' => array(
      'style' => 'naked',
    ),
    'header' => array(
      'style' => 'naked',
    ),
    'promoted_top' => array(
      'style' => 'naked',
    ),
    'main_top' => array(
      'style' => 'naked',
    ),
    'promoted' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '3c785124-14ea-40bb-b281-31a9329c0b23';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-7b603e3e-7c61-4ad5-9bd4-5ca568050b69';
    $pane->panel = 'banner';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library-opening-hours-banner';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = '7b603e3e-7c61-4ad5-9bd4-5ca568050b69';
    $display->content['new-7b603e3e-7c61-4ad5-9bd4-5ca568050b69'] = $pane;
    $display->panels['banner'][0] = 'new-7b603e3e-7c61-4ad5-9bd4-5ca568050b69';
    $pane = new stdClass();
    $pane->pid = 'new-e3df4bf2-4c92-4ef6-a375-a198cb2772c9';
    $pane->panel = 'header';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-head';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = 'e3df4bf2-4c92-4ef6-a375-a198cb2772c9';
    $display->content['new-e3df4bf2-4c92-4ef6-a375-a198cb2772c9'] = $pane;
    $display->panels['header'][0] = 'new-e3df4bf2-4c92-4ef6-a375-a198cb2772c9';
    $pane = new stdClass();
    $pane->pid = 'new-7c4c7fc8-306f-4cd3-9d92-608de6b5d877';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library-contact';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = '7c4c7fc8-306f-4cd3-9d92-608de6b5d877';
    $display->content['new-7c4c7fc8-306f-4cd3-9d92-608de6b5d877'] = $pane;
    $display->panels['main'][0] = 'new-7c4c7fc8-306f-4cd3-9d92-608de6b5d877';
    $pane = new stdClass();
    $pane->pid = 'new-0e88fcdc-10ed-4c8e-876d-0c853fdb074f';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library-contact-form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '0e88fcdc-10ed-4c8e-876d-0c853fdb074f';
    $display->content['new-0e88fcdc-10ed-4c8e-876d-0c853fdb074f'] = $pane;
    $display->panels['main'][1] = 'new-0e88fcdc-10ed-4c8e-876d-0c853fdb074f';
    $pane = new stdClass();
    $pane->pid = 'new-2b04e45a-7ba0-4d4d-98d6-f874e234fe61';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library-opening-hours';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '2b04e45a-7ba0-4d4d-98d6-f874e234fe61';
    $display->content['new-2b04e45a-7ba0-4d4d-98d6-f874e234fe61'] = $pane;
    $display->panels['main'][2] = 'new-2b04e45a-7ba0-4d4d-98d6-f874e234fe61';
    $pane = new stdClass();
    $pane->pid = 'new-153d8eb4-1a5e-4aa2-af3a-2ac7d4856e23';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library_opening_hours_info ';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '153d8eb4-1a5e-4aa2-af3a-2ac7d4856e23';
    $display->content['new-153d8eb4-1a5e-4aa2-af3a-2ac7d4856e23'] = $pane;
    $display->panels['main'][3] = 'new-153d8eb4-1a5e-4aa2-af3a-2ac7d4856e23';
    $pane = new stdClass();
    $pane->pid = 'new-f49d8c04-39d9-4b89-aca9-3d19c20fcc82';
    $pane->panel = 'main_top';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:library-properties';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = 'f49d8c04-39d9-4b89-aca9-3d19c20fcc82';
    $display->content['new-f49d8c04-39d9-4b89-aca9-3d19c20fcc82'] = $pane;
    $display->panels['main_top'][0] = 'new-f49d8c04-39d9-4b89-aca9-3d19c20fcc82';
    $pane = new stdClass();
    $pane->pid = 'new-fc378e18-63ad-4e8e-b4cd-bbc7a8f67fb8';
    $pane->panel = 'main_top';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:content-sections';
    $pane->shown = TRUE;
    $pane->access = array(
      'logic' => 'and',
      'plugins' => array(),
    );
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'fc378e18-63ad-4e8e-b4cd-bbc7a8f67fb8';
    $display->content['new-fc378e18-63ad-4e8e-b4cd-bbc7a8f67fb8'] = $pane;
    $display->panels['main_top'][1] = 'new-fc378e18-63ad-4e8e-b4cd-bbc7a8f67fb8';
    $pane = new stdClass();
    $pane->pid = 'new-bb0e1e51-4299-490d-a9b2-891d4fb16017';
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
    $pane->uuid = 'bb0e1e51-4299-490d-a9b2-891d4fb16017';
    $display->content['new-bb0e1e51-4299-490d-a9b2-891d4fb16017'] = $pane;
    $display->panels['messages'][0] = 'new-bb0e1e51-4299-490d-a9b2-891d4fb16017';
    $pane = new stdClass();
    $pane->pid = 'new-955d37a7-32c7-4b87-b14b-4273a1ea33a0';
    $pane->panel = 'promoted';
    $pane->type = 'slate_gmap';
    $pane->subtype = 'slate_gmap:node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'gmap_slate' => 'library-map',
      'gmap_item_content_slate' => 'library-map-item',
      'lat_lng_field' => 'field_location',
      'gmap_tools_settings' => array(
        'container_id' => 'slate-gmap-node',
        'gmap_tools_namespace' => 'slate_gmap_node',
        'gmap_tools_gmap_create_gmap' => 1,
        'gmap_tools_gmap_options' => array(
          'mapTypeId' => 'ROADMAP',
          'zoom' => '15',
          'min_zoom' => '',
          'max_zoom' => '',
          'center' => array(
            'lat' => '0',
            'lng' => '0',
          ),
        ),
        'gmap_tools_behaviors' => array(
          'clustered' => array(
            'enabled' => 0,
          ),
          'info_windows' => array(
            'enabled' => 1,
          ),
          'items_sidebar' => array(
            'enabled' => 0,
            'options' => array(
              'wrapper' => '',
              'limit' => '',
              'bounce' => 0,
              'items_filter' => array(
                'body' => '',
              ),
            ),
          ),
          'fit_items_bounds' => array(
            'enabled' => 0,
            'options' => array(
              'max_zoom' => '',
              'min_zoom' => '',
            ),
          ),
        ),
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
      'bundles' => array(
        'library' => 'library',
      ),
      'container_id' => 'slate-gmap-node',
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
    $pane->uuid = '955d37a7-32c7-4b87-b14b-4273a1ea33a0';
    $display->content['new-955d37a7-32c7-4b87-b14b-4273a1ea33a0'] = $pane;
    $display->panels['promoted'][0] = 'new-955d37a7-32c7-4b87-b14b-4273a1ea33a0';
    $pane = new stdClass();
    $pane->pid = 'new-8414a01c-f282-44b7-9f3b-afa34b91e33e';
    $pane->panel = 'promoted_top';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:hero-image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = '8414a01c-f282-44b7-9f3b-afa34b91e33e';
    $display->content['new-8414a01c-f282-44b7-9f3b-afa34b91e33e'] = $pane;
    $display->panels['promoted_top'][0] = 'new-8414a01c-f282-44b7-9f3b-afa34b91e33e';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_2a4b8744-508b-4c0f-bd8f-86a4fa9d91f3'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_75e1767f-61d5-443b-9456-0e86608b78ce';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -25;
  $handler->conf = array(
    'title' => 'Libraries',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        1 => array(
          'name' => 'entity_uuid:node',
          'settings' => array(
            'uuid' => 'f8bcf20f-d066-41fc-9e41-c1b3d97dccee',
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol_full';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'header' => NULL,
      'messages' => NULL,
      'promoted_top' => NULL,
      'main_top' => NULL,
      'promoted' => NULL,
    ),
    'main' => array(
      'style' => 'naked',
    ),
    'header' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '20a21b24-5ea9-4706-b757-2bb313975b11';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-58939798-2006-4e3e-9e32-e3840910a4bf';
    $pane->panel = 'header';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-head';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = '58939798-2006-4e3e-9e32-e3840910a4bf';
    $display->content['new-58939798-2006-4e3e-9e32-e3840910a4bf'] = $pane;
    $display->panels['header'][0] = 'new-58939798-2006-4e3e-9e32-e3840910a4bf';
    $pane = new stdClass();
    $pane->pid = 'new-376e1c75-6e4c-43c2-903d-0a3ce654c613';
    $pane->panel = 'main';
    $pane->type = 'views_panes';
    $pane->subtype = 'library_list-libraries';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ubn_i18n' => array(
        'opening_hours_title' => 'Opening hours',
      ),
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
    $pane->uuid = '376e1c75-6e4c-43c2-903d-0a3ce654c613';
    $display->content['new-376e1c75-6e4c-43c2-903d-0a3ce654c613'] = $pane;
    $display->panels['main'][0] = 'new-376e1c75-6e4c-43c2-903d-0a3ce654c613';
    $pane = new stdClass();
    $pane->pid = 'new-b3b3304e-4b2b-4310-b0d8-913b909b9ac8';
    $pane->panel = 'main';
    $pane->type = 'slate_gmap';
    $pane->subtype = 'slate_gmap:node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'gmap_tools_settings' => array(
        'container_id' => 'slate-gmap-node',
        'gmap_tools_namespace' => 'slate_gmap_node',
        'gmap_tools_gmap_create_gmap' => 1,
        'gmap_tools_gmap_options' => array(
          'mapTypeId' => 'ROADMAP',
          'zoom' => '14',
          'min_zoom' => '',
          'max_zoom' => '',
          'center' => array(
            'lat' => '0',
            'lng' => '0',
          ),
        ),
        'gmap_tools_behaviors' => array(
          'clustered' => array(
            'enabled' => 0,
          ),
          'info_windows' => array(
            'enabled' => 1,
          ),
          'items_sidebar' => array(
            'enabled' => 0,
            'options' => array(
              'wrapper' => '',
              'limit' => '',
              'bounce' => 0,
              'items_filter' => array(
                'body' => '',
              ),
            ),
          ),
          'fit_items_bounds' => array(
            'enabled' => 1,
            'options' => array(
              'max_zoom' => '',
              'min_zoom' => '',
            ),
          ),
        ),
      ),
      'bundles' => array(
        'library' => 'library',
      ),
      'gmap_slate' => 'libraries-map',
      'gmap_item_content_slate' => 'library-map-item',
      'lat_lng_field' => 'field_location',
      'context' => 'empty',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'b3b3304e-4b2b-4310-b0d8-913b909b9ac8';
    $display->content['new-b3b3304e-4b2b-4310-b0d8-913b909b9ac8'] = $pane;
    $display->panels['main'][1] = 'new-b3b3304e-4b2b-4310-b0d8-913b909b9ac8';
    $pane = new stdClass();
    $pane->pid = 'new-368d5bb4-9873-4b76-9466-b19ffa4d0325';
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
    $pane->uuid = '368d5bb4-9873-4b76-9466-b19ffa4d0325';
    $display->content['new-368d5bb4-9873-4b76-9466-b19ffa4d0325'] = $pane;
    $display->panels['messages'][0] = 'new-368d5bb4-9873-4b76-9466-b19ffa4d0325';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-376e1c75-6e4c-43c2-903d-0a3ce654c613';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_75e1767f-61d5-443b-9456-0e86608b78ce'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_86d5c846-6b6c-43f7-8ef9-0cbb4f513fe7';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -23;
  $handler->conf = array(
    'title' => 'Database',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'database' => 'database',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
    'main' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '35056379-c54c-4be5-a528-c4caf781a4c7';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1a87ea19-06b4-4ec5-b690-bcea2f4d8dd6';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-database';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = '1a87ea19-06b4-4ec5-b690-bcea2f4d8dd6';
    $display->content['new-1a87ea19-06b4-4ec5-b690-bcea2f4d8dd6'] = $pane;
    $display->panels['main'][0] = 'new-1a87ea19-06b4-4ec5-b690-bcea2f4d8dd6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_86d5c846-6b6c-43f7-8ef9-0cbb4f513fe7'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_f69415b1-e449-4cd0-859c-f2bea71148bb';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -24;
  $handler->conf = array(
    'title' => 'Page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'page' => 'page',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol_full';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'header' => NULL,
      'messages' => NULL,
      'promoted_top' => NULL,
      'main_top' => NULL,
      'promoted' => NULL,
    ),
    'main' => array(
      'style' => 'naked',
    ),
    'header' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'b6f36589-9536-420c-8d41-57a59f9d4348';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ce69a7ac-895b-4e74-96e3-1054f934577b';
    $pane->panel = 'header';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-head';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = 'ce69a7ac-895b-4e74-96e3-1054f934577b';
    $display->content['new-ce69a7ac-895b-4e74-96e3-1054f934577b'] = $pane;
    $display->panels['header'][0] = 'new-ce69a7ac-895b-4e74-96e3-1054f934577b';
    $pane = new stdClass();
    $pane->pid = 'new-f5c386c1-afc9-4a08-96c3-2cd3ee33e780';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:content-sections';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->uuid = 'f5c386c1-afc9-4a08-96c3-2cd3ee33e780';
    $display->content['new-f5c386c1-afc9-4a08-96c3-2cd3ee33e780'] = $pane;
    $display->panels['main'][0] = 'new-f5c386c1-afc9-4a08-96c3-2cd3ee33e780';
    $pane = new stdClass();
    $pane->pid = 'new-d28ce43c-79fd-4c00-be39-515358c58ce4';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:page-app';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd28ce43c-79fd-4c00-be39-515358c58ce4';
    $display->content['new-d28ce43c-79fd-4c00-be39-515358c58ce4'] = $pane;
    $display->panels['main'][1] = 'new-d28ce43c-79fd-4c00-be39-515358c58ce4';
    $pane = new stdClass();
    $pane->pid = 'new-f26a13d8-7831-4045-a93c-0df8ec4a64f0';
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
    $pane->uuid = 'f26a13d8-7831-4045-a93c-0df8ec4a64f0';
    $display->content['new-f26a13d8-7831-4045-a93c-0df8ec4a64f0'] = $pane;
    $display->panels['messages'][0] = 'new-f26a13d8-7831-4045-a93c-0df8ec4a64f0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-f5c386c1-afc9-4a08-96c3-2cd3ee33e780';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_f69415b1-e449-4cd0-859c-f2bea71148bb'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template_panel_context';
  $handler->task = 'site_template';
  $handler->subtask = '';
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
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'site_template';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'topbar' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'toplinks' => NULL,
      'pagetitle' => NULL,
      'tabs' => NULL,
      'messages' => NULL,
      'navigation_secondary' => NULL,
      'dropdown_navigation' => NULL,
      'breadcrumb' => NULL,
      'beta' => NULL,
      'warning_message' => NULL,
      'shortcuts' => NULL,
    ),
    'tabs' => array(
      'style' => 'default',
    ),
    'navigation' => array(
      'style' => 'naked',
    ),
    'pagetitle' => array(
      'style' => 'naked',
    ),
    'toplinks' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '9e33ff90-3988-470d-9ff9-57c03abb7a3d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-045db4f3-e91d-4623-b1f8-c7ef0477c576';
    $pane->panel = 'beta';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:beta-indicator';
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
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '045db4f3-e91d-4623-b1f8-c7ef0477c576';
    $display->content['new-045db4f3-e91d-4623-b1f8-c7ef0477c576'] = $pane;
    $display->panels['beta'][0] = 'new-045db4f3-e91d-4623-b1f8-c7ef0477c576';
    $pane = new stdClass();
    $pane->pid = 'new-d1d3ab18-a2e2-4332-a72d-727c5f241b8f';
    $pane->panel = 'breadcrumb';
    $pane->type = 'ubn_menu';
    $pane->subtype = 'ubn_menu:main-menu:menu-trail';
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
    $pane->uuid = 'd1d3ab18-a2e2-4332-a72d-727c5f241b8f';
    $display->content['new-d1d3ab18-a2e2-4332-a72d-727c5f241b8f'] = $pane;
    $display->panels['breadcrumb'][0] = 'new-d1d3ab18-a2e2-4332-a72d-727c5f241b8f';
    $pane = new stdClass();
    $pane->pid = 'new-011a4262-ca7b-42af-ab00-9d5ee0a36877';
    $pane->panel = 'content';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
      'override_title' => 0,
      'override_title_text' => '',
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
    $pane->uuid = '011a4262-ca7b-42af-ab00-9d5ee0a36877';
    $display->content['new-011a4262-ca7b-42af-ab00-9d5ee0a36877'] = $pane;
    $display->panels['content'][0] = 'new-011a4262-ca7b-42af-ab00-9d5ee0a36877';
    $pane = new stdClass();
    $pane->pid = 'new-92a668ff-293b-4e55-aeaa-1363a20464ff';
    $pane->panel = 'dropdown_navigation';
    $pane->type = 'ubn_menu';
    $pane->subtype = 'ubn_menu:main-menu:bottom-level-dropdown';
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
    $pane->uuid = '92a668ff-293b-4e55-aeaa-1363a20464ff';
    $display->content['new-92a668ff-293b-4e55-aeaa-1363a20464ff'] = $pane;
    $display->panels['dropdown_navigation'][0] = 'new-92a668ff-293b-4e55-aeaa-1363a20464ff';
    $pane = new stdClass();
    $pane->pid = 'new-7462df87-fdfa-4351-8ceb-255a745eecef';
    $pane->panel = 'footer';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:footer';
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
    $pane->uuid = '7462df87-fdfa-4351-8ceb-255a745eecef';
    $display->content['new-7462df87-fdfa-4351-8ceb-255a745eecef'] = $pane;
    $display->panels['footer'][0] = 'new-7462df87-fdfa-4351-8ceb-255a745eecef';
    $pane = new stdClass();
    $pane->pid = 'new-94db747d-dbbe-42bd-9909-a59b215d30bd';
    $pane->panel = 'messages';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
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
    $pane->uuid = '94db747d-dbbe-42bd-9909-a59b215d30bd';
    $display->content['new-94db747d-dbbe-42bd-9909-a59b215d30bd'] = $pane;
    $display->panels['messages'][0] = 'new-94db747d-dbbe-42bd-9909-a59b215d30bd';
    $pane = new stdClass();
    $pane->pid = 'new-af13358f-a03b-454e-a619-0bcf6d238af6';
    $pane->panel = 'navigation';
    $pane->type = 'ubn_menu';
    $pane->subtype = 'ubn_menu:main-menu:top-level';
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
    $pane->uuid = 'af13358f-a03b-454e-a619-0bcf6d238af6';
    $display->content['new-af13358f-a03b-454e-a619-0bcf6d238af6'] = $pane;
    $display->panels['navigation'][0] = 'new-af13358f-a03b-454e-a619-0bcf6d238af6';
    $pane = new stdClass();
    $pane->pid = 'new-acf77ff7-9aef-4d9d-9242-6da34549b765';
    $pane->panel = 'navigation_secondary';
    $pane->type = 'ubn_menu';
    $pane->subtype = 'ubn_menu:main-menu:bottom-level';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'library' => 'library',
              'navigation_landing' => 'navigation_landing',
            ),
          ),
          'context' => 'node',
          'not' => TRUE,
        ),
        1 => array(
          'name' => 'entity_uuid:node',
          'settings' => array(
            'uuid' => 'f8bcf20f-d066-41fc-9e41-c1b3d97dccee',
          ),
          'context' => 'node',
          'not' => TRUE,
        ),
      ),
    );
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
    $pane->uuid = 'acf77ff7-9aef-4d9d-9242-6da34549b765';
    $display->content['new-acf77ff7-9aef-4d9d-9242-6da34549b765'] = $pane;
    $display->panels['navigation_secondary'][0] = 'new-acf77ff7-9aef-4d9d-9242-6da34549b765';
    $pane = new stdClass();
    $pane->pid = 'new-ce326e53-b34a-4815-b93f-3210320a4edd';
    $pane->panel = 'pagetitle';
    $pane->type = 'page_title';
    $pane->subtype = 'page_title';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'markup' => 'h1',
      'class' => '',
      'id' => '',
      'override_title' => 0,
      'override_title_text' => '',
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
    $pane->uuid = 'ce326e53-b34a-4815-b93f-3210320a4edd';
    $display->content['new-ce326e53-b34a-4815-b93f-3210320a4edd'] = $pane;
    $display->panels['pagetitle'][0] = 'new-ce326e53-b34a-4815-b93f-3210320a4edd';
    $pane = new stdClass();
    $pane->pid = 'new-f92086e9-0d9c-4541-be57-6623ad98be72';
    $pane->panel = 'shortcuts';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-shortcut-menu';
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
    $pane->uuid = 'f92086e9-0d9c-4541-be57-6623ad98be72';
    $display->content['new-f92086e9-0d9c-4541-be57-6623ad98be72'] = $pane;
    $display->panels['shortcuts'][0] = 'new-f92086e9-0d9c-4541-be57-6623ad98be72';
    $pane = new stdClass();
    $pane->pid = 'new-3054dda2-3a4b-428b-b253-726c16c2f284';
    $pane->panel = 'tabs';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'both',
      'id' => 'tabs',
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
    $pane->uuid = '3054dda2-3a4b-428b-b253-726c16c2f284';
    $display->content['new-3054dda2-3a4b-428b-b253-726c16c2f284'] = $pane;
    $display->panels['tabs'][0] = 'new-3054dda2-3a4b-428b-b253-726c16c2f284';
    $pane = new stdClass();
    $pane->pid = 'new-0dce97f2-bac4-47f0-ac2d-c0eb728104ba';
    $pane->panel = 'toplinks';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:screenreader';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'node',
      ),
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
    $pane->uuid = '0dce97f2-bac4-47f0-ac2d-c0eb728104ba';
    $display->content['new-0dce97f2-bac4-47f0-ac2d-c0eb728104ba'] = $pane;
    $display->panels['toplinks'][0] = 'new-0dce97f2-bac4-47f0-ac2d-c0eb728104ba';
    $pane = new stdClass();
    $pane->pid = 'new-179c37da-32bb-42e2-900c-6dbcaec09453';
    $pane->panel = 'toplinks';
    $pane->type = 'block';
    $pane->subtype = 'locale-language';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '179c37da-32bb-42e2-900c-6dbcaec09453';
    $display->content['new-179c37da-32bb-42e2-900c-6dbcaec09453'] = $pane;
    $display->panels['toplinks'][1] = 'new-179c37da-32bb-42e2-900c-6dbcaec09453';
    $pane = new stdClass();
    $pane->pid = 'new-d7e006c7-cc3d-4685-8393-060d731a3efd';
    $pane->panel = 'warning_message';
    $pane->type = 'views_panes';
    $pane->subtype = 'alert_message-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd7e006c7-cc3d-4685-8393-060d731a3efd';
    $display->content['new-d7e006c7-cc3d-4685-8393-060d731a3efd'] = $pane;
    $display->panels['warning_message'][0] = 'new-d7e006c7-cc3d-4685-8393-060d731a3efd';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['site_template_panel_context'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ubn_page_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'error_404';
  $page->task = 'page';
  $page->admin_title = 'error';
  $page->admin_description = '';
  $page->path = 'error-404';
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
  $handler->name = 'page_404__panel';
  $handler->task = 'page';
  $handler->subtask = 'error_404';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
    'access' => array(
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol_full';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '33096873-9ea6-47d4-9f87-ff1fc7f0fb47';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3c66fbab-23e5-4c3b-a3c9-4e687cc0fef7';
    $pane->panel = 'main';
    $pane->type = 'slate_render';
    $pane->subtype = 'slate_render:error-404';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
      'ubn_i18n' => array(
        'title' => '404 - the page was not found',
        'message' => 'Sorry! Nothing exists here.',
        'front_page_link_text' => 'To go back to the start page click here',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3c66fbab-23e5-4c3b-a3c9-4e687cc0fef7';
    $display->content['new-3c66fbab-23e5-4c3b-a3c9-4e687cc0fef7'] = $pane;
    $display->panels['main'][0] = 'new-3c66fbab-23e5-4c3b-a3c9-4e687cc0fef7';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages[''] = $page;

  return $pages;

}
