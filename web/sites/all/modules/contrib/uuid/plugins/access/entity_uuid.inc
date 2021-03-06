<?php
/**
 * @file
 * Plugin to provide access control based on entity UUID.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Entity UUID value"),
  'description' => t('Control access through entity uuid value.'),
  'callback' => 'uuid_entity_uuid_ctools_access_check',
  'default' => array('uuid' => ''),
  'settings form' => 'uuid_entity_uuid_ctools_access_settings',
  'summary' => 'uuid_entity_uuid_ctools_access_summary',
  'get child' => 'uuid_entity_uuid_ctools_access_get_child',
  'get children' => 'uuid_entity_uuid_ctools_access_get_children',
);

function uuid_entity_uuid_ctools_access_get_child($plugin, $parent, $child) {
  $plugins = &drupal_static(__FUNCTION__, array());
  if (empty($plugins[$parent . ':' . $child])) {
    $plugins[$parent . ':' . $child] = _uuid_entity_uuid_ctools_access_get_child($plugin, $parent, $child);
  }
  return $plugins[$parent . ':' . $child];
}

function uuid_entity_uuid_ctools_access_get_children($plugin, $parent) {
  $plugins = &drupal_static(__FUNCTION__, array());
  if (!empty($plugins)) {
    return $plugins;
  }
  $entities = entity_get_info();
  foreach ($entities as $entity_type => $entity_info) {
    if (isset($entity_info['uuid'])) {
      $plugin = _uuid_entity_uuid_ctools_access_get_child($plugin, $parent, $entity_type);
      $plugins[$parent . ':' . $entity_type] = $plugin;
    }
  }
  return $plugins;
}

function _uuid_entity_uuid_ctools_access_get_child($plugin, $parent, $entity_type) {
  $entity_info = entity_get_info($entity_type);
  $plugin['title'] = t('@entity: UUID', array('@entity' => $entity_info['label']));
  $plugin['keyword'] = $entity_type;
  $plugin['description'] = t('Control access by @entity UUID.', array('@entity' => $entity_type));
  $plugin['name'] = $parent . ':' . $entity_type;
  $plugin['required context'] = new ctools_context_required(t(ucfirst($entity_type)), "entity:$entity_type");
  return $plugin;
}

/**
 * Settings form for the 'entity uuid value' access plugin
 */
function uuid_entity_uuid_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['uuid'] = array(
    '#type' => 'textfield',
    '#title' => t('UUID'),
    '#default_value' => $conf['uuid'],
  );
  return $form;
}

/**
 * Check for access.
 */
function uuid_entity_uuid_ctools_access_check($conf, $context, $plugin) {
  if ((!is_object($context)) || (empty($context->data))) {
    return FALSE;
  }
  list(, $entity_type) = explode(':', $plugin['name']);
  $entity_info = entity_get_info($entity_type);
  $uuid_key = $entity_info['entity keys']['uuid'];
  return isset($context->data->{$uuid_key}) && $context->data->{$uuid_key} === $conf['uuid'];
}

/**
 * Provide a summary description
 */
function uuid_entity_uuid_ctools_access_summary($conf, $context, $plugin) {
  return t('The UUID of @entity is "@uuid"', array('@entity' => drupal_strtolower($context->identifier), '@uuid' => $conf['uuid']));
}
