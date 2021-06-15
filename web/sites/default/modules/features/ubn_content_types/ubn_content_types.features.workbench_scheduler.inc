<?php

/**
 * @file
 * ubn_content_types.features.workbench_scheduler.inc
 */

/**
 * Implements hook_workbench_scheduler_export_schedules().
 */
function ubn_content_types_workbench_scheduler_export_schedules() {
  $items = array(
    'published_unpublished' => array(
      'name' => 'published_unpublished',
      'label' => 'Publish/Unpublish',
      'start_state' => 'published',
      'end_state' => 'unpublished',
      'types' => array(
        0 => 'alert_and_info_message',
        1 => 'blurb',
        2 => 'page',
        3 => 'story',
      ),
    ),
  );
  return $items;
}
