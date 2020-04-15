<?php
/**
 * @file
 * ubn_events_content.features.uuid_entity_menu_link.inc
 */

/**
 * Implements hook_uuid_entity_default_menu_link().
 */
function ubn_events_content_uuid_entity_default_menu_link() {
  $items = array();
  $items['5bcf4a48-75f8-4e41-82c7-6c65b0cc7d90'] = entity_create('menu_link', array(
    'menu_name' => 'menu-shortcut-menu',
    'plid' => 0,
    'link_path' => 'node/ce579a0e-ea38-4398-a639-daf95923e105',
    'router_path' => 'node/%',
    'link_title' => 'Calendar',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Calendar',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'depth' => 1,
    'customized' => 1,
    'p1' => '5bcf4a48-75f8-4e41-82c7-6c65b0cc7d90',
    'p2' => 0,
    'p3' => 0,
    'p4' => 0,
    'p5' => 0,
    'p6' => 0,
    'p7' => 0,
    'p8' => 0,
    'p9' => 0,
    'updated' => 0,
    'language' => 'und',
    'vuuid' => '24c5a230-979d-4995-871e-e5378559f077',
    'uuid' => '5bcf4a48-75f8-4e41-82c7-6c65b0cc7d90',
    'default_revision' => 1,
    'access' => TRUE,
    'i18n_menu' => TRUE,
  ));
  return $items;
}
