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
  'description' => t('All event occations'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_event_occations_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_event_occations_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_events_event_occations_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  $block->title = t('Event occations');
  $block->content = '';

  $results = ubn_events_current_event_occations_efq()
    ->execute();

  if (!empty($results['node'])) {
    $event_occations = entity_load('node', array_keys($results['node']));
    $event_occations_by_year_month = ubn_events_event_occations_by_year_month_rendered($event_occations);
    $block->content = slate_render('event-occations', array('event_occations_by_year_month' => $event_occations_by_year_month));
  }

  return $block;
}
