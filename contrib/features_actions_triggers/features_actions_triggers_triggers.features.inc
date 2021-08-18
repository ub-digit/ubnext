<?php
/**
 * @file
 * Enable triggers to be exported by features.
 */

/**
 * Implements hook_features_export_options().
 */
function features_actions_triggers_triggers_features_export_options() {
  $options = array();
  $query = 'SELECT t.*, a.label, a.callback FROM {trigger_assignments} AS t JOIN {actions} AS a ON t.aid = a.aid ORDER BY t.hook ASC';
  $fields = db_query($query);
  while ($row = $fields->fetchObject()) {
    $options[$row->hook . ':' . $row->aid . ':' . $row->callback] = $row->hook . ' -> ' . $row->label;
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function features_actions_triggers_triggers_features_export($data, &$export, $module_name = '') {
  $pipe = array();
  $export['dependencies']['trigger'] = 'trigger';
  foreach ($data as $machine_name) {
    $parts = explode(':', $machine_name);
    // Initialise pip dependancies.
    if (empty($pipe['features_actions_triggers_actions'])) {
      $pipe['features_actions_triggers_actions'] = array();
    }
    // Check dependancy is not already assigned.
    if (!in_array($parts[1], $pipe['features_actions_triggers_actions'])) {
      $pipe['features_actions_triggers_actions'][] = $parts[1] . ':' . $parts[2];
    }
    $export['features']['features_actions_triggers_triggers'][$machine_name] = $machine_name;
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function features_actions_triggers_triggers_features_export_render($module_name, $data) {
  $items = array();
  foreach ($data as $key) {
    $parts = explode(':', $key);
    $field = db_query('SELECT * FROM {trigger_assignments} WHERE hook = :hook AND aid = :aid', array(':hook' => $parts[0], ':aid' => $parts[1]))->fetchObject();
    $items[$key] = $field;
  }
  $code = "  \$items = " . features_var_export($items, '  ') . ";\n";
  $code .= '  return $items;';
  return array('features_actions_triggers_export_triggers_default' => $code);
}

/**
 * Implements hook_features_revert().
 */
function features_actions_triggers_triggers_features_revert($module) {
  $defaults = features_get_default('features_actions_triggers_triggers', $module);
  // Revert.
  foreach ($defaults as $object) {
    _features_actions_triggers_triggers_save_field($object);
  }
}

/**
 * Saves a action field to the database.
 *
 * @param array $field_data
 *   The field data to save.
 */
function _features_actions_triggers_triggers_save_field($field_data) {
  // Force field data to be an object.
  $field_data = (object) $field_data;
  // Check if record already exists.
  if (!db_query('SELECT * FROM {trigger_assignments} WHERE hook = :hook AND aid = :aid', array(':hook' => $field_data->hook, ':aid' => $field_data->aid))->fetchObject()) {
    drupal_write_record('trigger_assignments', $field_data);
  }
  else {
    drupal_write_record('trigger_assignments', $field_data, array('hook', 'aid'));
  }
}