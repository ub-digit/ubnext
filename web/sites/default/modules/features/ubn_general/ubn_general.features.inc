<?php

/**
 * @file
 * ubn_general.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ubn_general_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ubn_general_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_features_actions_triggers_export_actions_default().
 */
function ubn_general_features_actions_triggers_export_actions_default() {
  $items = array(
    '36:system_goto_action' => array(
      'aid' => 36,
      'type' => 'system',
      'callback' => 'system_goto_action',
      'parameters' => 'a:1:{s:3:"url";s:7:"<front>";}',
      'label' => 'Redirect to URL - node #FRONT#',
    ),
  );
  return $items;
}

/**
 * Implements hook_features_actions_triggers_export_triggers_default().
 */
function ubn_general_features_actions_triggers_export_triggers_default() {
  $items = array(
    'user_login:36:system_goto_action' => array(
      'hook' => 'user_login',
      'aid' => 36,
      'weight' => 1,
    ),
  );
  return $items;
}
