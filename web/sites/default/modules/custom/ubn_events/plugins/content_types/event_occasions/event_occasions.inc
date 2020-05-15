<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Events'),
  'description' => t('All event occasions'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_event_occasions_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_event_occasions_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_events_event_occasions_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  $block->title = t('Event occasions');
  $block->content = '';

  $results = ubn_events_current_event_occasions_efq()
    ->execute();

  if (!empty($results['node'])) {
    $event_occasions = entity_load('node', array_keys($results['node']));
    $event_occasions_by_year_month = ubn_events_event_occasions_by_year_month_rendered($event_occasions);
    $block->content = slate_render('event-occasions', array('event_occasions_by_year_month' => $event_occasions_by_year_month));
  }

  return $block;
}
