<?php
/**
 * @file
 * ubn_events_content.features.uuid_entity_node.inc
 */

/**
 * Implements hook_uuid_entity_default_node().
 */
function ubn_events_content_uuid_entity_default_node() {
  $items = array();
  $items['ce579a0e-ea38-4398-a639-daf95923e105'] = entity_create('node', array(
    'uid' => 1,
    'title' => 'Bibliotekets kalender',
    'comment' => 0,
    'promote' => 0,
    'sticky' => 0,
    'vuuid' => 'd50ada96-8649-4962-9c71-356227744fe4',
    'type' => 'page',
    'language' => 'sv',
    'tnid' => 0,
    'translate' => 0,
    'uuid' => 'ce579a0e-ea38-4398-a639-daf95923e105',
    'revision_uid' => 1,
    'title_field' => array(
      'en' => array(
        0 => array(
          'value' => 'Library calendar',
          'format' => NULL,
          'safe_value' => 'Library calendar',
        ),
      ),
      'sv' => array(
        0 => array(
          'value' => 'Bibliotekets kalender',
          'format' => NULL,
          'safe_value' => 'Bibliotekets kalender',
        ),
      ),
    ),
    'field_lead' => array(),
    'field_content_sections' => array(),
    'translations' => array(
      'original' => 'sv',
      'data' => array(
        'en' => array(
          'language' => 'en',
          'source' => 'sv',
          'status' => 1,
          'translate' => 0,
        ),
        'sv' => array(
          'language' => 'sv',
          'source' => '',
          'status' => 1,
          'translate' => 0,
        ),
      ),
    ),
    'name' => 'admin',
    'picture' => 0,
    'data' => 'b:0;',
    'published_at' => 1584714129,
  ));
  return $items;
}
