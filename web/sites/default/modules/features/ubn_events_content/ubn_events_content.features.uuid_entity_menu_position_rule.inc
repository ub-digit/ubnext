<?php
/**
 * @file
 * ubn_events_content.features.uuid_entity_menu_position_rule.inc
 */

/**
 * Implements hook_uuid_entity_default_menu_position_rule().
 */
function ubn_events_content_uuid_entity_default_menu_position_rule() {
  $items = array();
  $items['1c73c98b-0132-4313-a845-30a18ffc8ce5'] = entity_create('menu_position_rule', array(
    'admin_title' => 'Calendar',
    'enabled' => 1,
    'conditions' => array(
      'content_type' => array(
        'content_type' => array(
          'event_occation' => 'event_occation',
        ),
      ),
    ),
    'menu_name' => 'menu-shortcut-menu',
    'plid' => '5bcf4a48-75f8-4e41-82c7-6c65b0cc7d90',
    'weight' => 0,
    'uuid' => '1c73c98b-0132-4313-a845-30a18ffc8ce5',
  ));
  return $items;
}
