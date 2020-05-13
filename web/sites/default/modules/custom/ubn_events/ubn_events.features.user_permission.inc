<?php
/**
 * @file
 * ubn_events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ubn_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view event occasions with unpublished event'.
  $permissions['view event occasions with unpublished event'] = array(
    'name' => 'view event occasions with unpublished event',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'ubn_events',
  );

  return $permissions;
}
