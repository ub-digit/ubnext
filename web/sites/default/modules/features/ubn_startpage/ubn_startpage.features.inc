<?php

/**
 * @file
 * ubn_startpage.features.inc
 */

/**
 * Implements hook_entityqueue_api().
 */
function ubn_startpage_entityqueue_api($module = NULL, $api = NULL) {
  if ($module == "entityqueue" && $api == "entityqueue_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function ubn_startpage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ubn_startpage_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ubn_startpage_node_info() {
  $items = array(
    'link_list' => array(
      'name' => t('Link list panel'),
      'base' => 'node_content',
      'description' => t('This enables you to list x number of links under a heading. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
