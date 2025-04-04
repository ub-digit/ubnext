<?php

/**
 * @file
 * ubn_general.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ubn_general_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: database editor.
  $roles['database editor'] = array(
    'name' => 'database editor',
    'weight' => 3,
  );

  // Exported role: editor.
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => 4,
  );

  // Exported role: user administrator.
  $roles['user administrator'] = array(
    'name' => 'user administrator',
    'weight' => 5,
  );

  return $roles;
}
