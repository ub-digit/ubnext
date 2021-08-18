<?php
/**
 * @file
 * Enable actions to be exported by features.
 */

/**
 * Implements hook_features_export_options().
 */
function features_actions_triggers_actions_features_export_options() {
  $options = array();
  $query = 'SELECT * FROM {actions} ORDER BY label ASC';
  $fields = db_query($query);
  while ($row = $fields->fetchObject()) {
    $options[$row->aid.':'.$row->callback] = $row->label;
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function features_actions_triggers_actions_features_export($data, &$export, $module_name = '') {
  // Get all modules that implement action_info hook.
  $modules = module_implements('action_info');
  foreach ($data as $machine_name) {
    // Split out aid from machine name.
    $parts = explode(':', $machine_name);
    // Get callback function for action.
    $function = db_query('SELECT callback FROM {actions} WHERE aid = :aid', array(':aid' => $parts[0]))->fetchField();
    // Get info for each module that invokes the action_info hook.
    foreach ($modules as $m) {
      $info = module_invoke($m, 'action_info');
      // Check if module implementa action callback.
      if (array_key_exists($function, $info)) {
        // Add the module dependancy
        $export['dependencies'][$m] = $m;
        break;
      }
    }
    $export['features']['features_actions_triggers_actions'][$machine_name] = $machine_name;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function features_actions_triggers_actions_features_export_render($module_name, $data) {
  $items = array();
  foreach ($data as $key) {
    // Split out aid from key.
    $parts = explode(':', $key);
    $field = db_query('SELECT * FROM {actions} WHERE aid = :aid', array(':aid' => $parts[0]))->fetchObject();
    $items[$key] = $field;
  }
  $code = "  \$items = " . features_var_export($items, '  ') . ";\n";
  $code .= '  return $items;';
  return array('features_actions_triggers_export_actions_default' => $code);
}

/**
 * Implements hook_features_revert().
 */
function features_actions_triggers_actions_features_revert($module) {
  $defaults = features_get_default('features_actions_triggers_actions', $module);
  // Revert.
  foreach ($defaults as $object) {
    _features_actions_triggers_actions_save_field($object);
  }
}

/**
 * Saves a action field to the database.
 *
 * @param array $field_data
 *   The field data to save.
 */
function _features_actions_triggers_actions_save_field($field_data) {
  // Ensure the parameters field is set.
  if (!isset($field_data['parameters'])) {
    $field_data['parameters'] = '';
  }
  // Force field data to be an object.
  $field_data = (object) $field_data;
  // Check if record already exists.
  if (!db_query('SELECT * FROM {actions} WHERE aid = :aid', array(':aid' => $field_data->aid))->fetchObject()) {
    drupal_write_record('actions', $field_data);
  }
  else {
    drupal_write_record('actions', $field_data, array('aid'));
  }
}
