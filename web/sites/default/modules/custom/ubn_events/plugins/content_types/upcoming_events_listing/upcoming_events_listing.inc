<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Events: Upcoming events listing'),
  'description' => t('Upcoming events listing'),
  'required context' => new ctools_context_required(t('Calendar'), 'entity:node'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_upcoming_events_listing_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_upcoming_events_listing_content_type_settings($form, &$form_state) {
  return $form;
}


/*variable_get('default_event_occasions_main')*
 * Render callback.
 */
function ubn_events_upcoming_events_listing_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  //$block->title = t('More event occasions');
  $block->title = '';
  $block->content = '';


  $calendar_wrapper = entity_metadata_wrapper('node', $context->data);
  $query = ubn_events_current_event_occasions_efq();
  $query->range(0, variable_get('default_event_occasions_main'));
  $results = $query->execute();
  $event_occasions = entity_load('node', array_keys($results['node']));
  $renderable = entity_view('node', $event_occasions, 'listing');
  $event_occasions_rendered = drupal_render($renderable);
  $block->content = slate_render('event-occasions-listing', array('event_occasions' => $event_occasions_rendered, 'calendar_page' => $calendar_wrapper));
  return $block;
}
