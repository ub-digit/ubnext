<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Events: More event occasions'),
  'description' => t('More event occasions'),
  'required context' => new ctools_context_required(t('Event occasion'), 'entity:node'),
  'category' => 'UBNext events',
  'edit form' => 'ubn_events_more_event_occasions_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_events_more_event_occasions_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_events_more_event_occasions_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language_content;

  $block = new stdClass();
  $block->title = t('More event occasions');
  $block->content = '';

  if (!empty($context->data)) {
    $event_occasion_wrapper = entity_metadata_wrapper('node', $context->data);
    $query = ubn_events_maybe_current_event_occasions_efq();
    if ($query) {
      $results = $query
        ->entityCondition('entity_id', $event_occasion_wrapper->getIdentifier(), '!=')
        ->fieldCondition('field_event', 'target_id', $event_occasion_wrapper->field_event->getIdentifier())
        ->execute();
      if (!empty($results['node'])) {
        $event_occasions = entity_load('node', array_keys($results['node']));
        $renderable = entity_view('node', $event_occasions, 'ubn_teaser_small');
        $event_occasions_rendered = drupal_render($renderable);
        $block->content = slate_render('more-event-occasions', array('event_occasions' => $event_occasions_rendered));
      }
    }
  }
  return $block;
}
