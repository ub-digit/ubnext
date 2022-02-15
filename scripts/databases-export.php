<?php

// Databases
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'database')
  ->propertyCondition('status', NODE_PUBLISHED);

$result = $query->execute();

$databases = array();
if (isset($result['node'])) {
  $database_nodes = entity_load('node', array_keys($result['node']));

  $value_fields = array(
    'field_hide_direct_link_in_search',
    'field_public_access',
    'field_tou_article_chapt_desc',
    'field_scholarly_sharing_desc',
    'field_scholarly_sharin',
    'field_print_article_chapter',
    'field_interlibrary_loan_desc',
    'field_interlibrary_loan',
    'field_gul_course_pack_electronic',
    'field_download_article_chapter',
    'field_download_article_chap_desc',
    'field_description',
    'field_course_pack_print_desc',
    'field_course_pack_print',
    'field_malfunction_message_active',
    'field_malfunction_message',
    'field_promote_to_shortcut',
  );

  $value_fields_multiple = array(
    'field_alternate_titles'
  );

  $taxonomy_fields_multiple = array(
    'field_recommended_in_subjects', // subjects = topics :/
    'field_access_information',
    'field_topics',
    'field_publishers',
    'field_media_types',
  );

  $taxonomy_fields = array(
    'field_access_information',
  );

  foreach ($database_nodes as $database_node) {

    $database_wrapper = entity_metadata_wrapper('node', $database_node);
    $database['database_urls'] = array();
    foreach($database_wrapper->field_database_urls as $url) {
      $value = $url->field_url->value();
      $database['database_urls'][] = array(
        'url' => $value['url'],
        'title' => $value['title']
      );
    }

    foreach ($value_fields as $field_name) {
      $database[substr($field_name, 6)] = array();
      if (!empty($database_node->{$field_name})) {
        $database[substr($field_name, 6)] = $database_node->{$field_name}['und'][0]['value'];
      }
    }

    foreach ($value_fields_multiple as $field_name) {
      $database[substr($field_name, 6)] = array();
      if (!empty($database_node->{$field_name})) {
        foreach($database_node->{$field_name}['und'] as $item) {
          $database[substr($field_name, 6)][] = $item['value'];
        }
      }
    }

    foreach ($taxonomy_fields as $field_name) {
      $database[substr($field_name, 6)] = array();
      if (!empty($database_node->{$field_name})) {
        $database[substr($field_name, 6)] = intval($database_node->{$field_name}['und'][0]['tid']);
      }
    }

    foreach ($taxonomy_fields_multiple as $field_name) {
      $database[substr($field_name, 6)] = array();
      if (!empty($database_node->{$field_name})) {
        foreach($database_node->{$field_name}['und'] as $item) {
          $database[substr($field_name, 6)][] = intval($item['tid']);
        }
      }
    }

    $database['title'] =  $database_node->title;
    $database['nid'] = $database_node->nid;

    $databases[] = $database;
  }
  //print json_encode($databases, JSON_PRETTY_PRINT);
}

// Taxonomies
$vocabularies = array(
  'database_availability', // used by field_access_information (?)
  'topics',
  'publishers',
  'media_types'
);

$vocab_terms_data = array();
foreach($vocabularies as $vocabulary_name) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
        ->entityCondition('bundle', $vocabulary_name);
  $result = $query->execute();
  $terms_data = array();
  if (isset($result['taxonomy_term'])) {
    $terms = entity_load('taxonomy_term', array_keys($result['taxonomy_term']));
    foreach($terms as $term) {
      unset($term->{rdf_mapping});
      unset($term->{entity_translation_handler_id});
      unset($term->{translations});
      unset($term->{path});
      $terms_data[] = $term;
    }
  }
  $vocab_terms_data[$vocabulary_name] = $terms_data;
}

//print json_encode($vocab_terms_data, JSON_PRETTY_PRINT);
