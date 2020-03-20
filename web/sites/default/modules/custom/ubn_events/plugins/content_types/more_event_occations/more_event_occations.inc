<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Events: More event occations'),
  'description' => t('More event occations'),
  'required context' => new ctools_context_required(t('Event occation'), 'entity:node'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_more_event_occations_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_more_event_occations_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_events_more_event_occations_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  $block->title = t('More event occations');
  $block->content = '';

  if (!empty($context->data)) {
    $event_occation_wrapper = entity_metadata_wrapper('node', $context->data);

    // "All day" events are scheduled at midnight in local timezone
    $site_tz_midnight_in_utc = ubn_events_site_tz_midnight_in_utc();
    $query = new EntityFieldQuery();
    $results = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'event_occation')
      ->entityCondition('entity_id', $event_occation_wrapper->getIdentifier(), '!=')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_event', 'target_id', $event_occation_wrapper->field_event->getIdentifier())
      ->fieldCondition('field_scheduled_time', 'value', $site_tz_midnight_in_utc->format('Y-m-d H:i'), '>=')
      ->fieldOrderBy('field_scheduled_time', 'value', 'ASC')
      ->execute();
    if (!empty($results['node'])) {
      $event_occations = entity_load('node', array_keys($results['node']));
      $renderable = entity_view('node', $event_occations, 'ubn_teaser_small');
      $event_occations_rendered = drupal_render($renderable);
      $block->content = slate_render('more-event-occations', array('event_occations' => $event_occations_rendered));
    }
  }
  return $block;
}
