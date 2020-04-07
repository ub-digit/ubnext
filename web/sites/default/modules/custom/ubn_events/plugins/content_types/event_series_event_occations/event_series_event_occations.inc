<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Events: event series event occations'),
  'description' => t('Event occations related by event series'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_event_series_event_occations_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_event_series_event_occations_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_events_event_series_event_occations_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  $block->title = t('Event series event occations');
  $block->content = '';

  // "All day" events are scheduled at midnight in local timezone
  $site_tz_midnight_in_utc = ubn_events_site_tz_midnight_in_utc();
  $query = new EntityFieldQuery();
  $results = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'event_occation')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_scheduled_time', 'value', $site_tz_midnight_in_utc->format('Y-m-d H:i'), '>=')
    ->fieldOrderBy('field_scheduled_time', 'value', 'ASC')
    ->execute();

  $site_tz = new DateTimeZone(date_default_timezone(FALSE));
  if (!empty($results['node'])) {
    $event_occations = entity_load('node', array_keys($results['node']));
    $event_occations_by_month = array();
    foreach($event_occations as $event_occation) {
      // Not using entity_metadat_wrapper here since carries quite some overhead
      // and also what to deal with DateObject not formatted value
      $item = $event_occation->field_scheduled_time['und'][0];
      $scheduled_time = new DateObject($item['value'], $item['timezone_db']);
      $scheduled_time->setTimezone($site_tz);
      $month = drupal_ucfirst(
        t($scheduled_time->format('F'), array(), array('context' => 'Long month name'))
      );
      $event_occations_by_month[$month][] = $event_occation;
    }
    foreach($event_occations_by_month as $month => $event_occations) {
      $event_occations_by_month[$month] = entity_view('node', $event_occations, 'teaser');
      $event_occations_by_month[$month] = drupal_render($event_occations_by_month[$month]);
    }
    $block->content = slate_render('event-occations', array('event_occations_by_month' => $event_occations_by_month));
  }

  return $block;
}
