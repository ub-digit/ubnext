<?php

$sql = array();
$tables = array(
  'databases',
  'topics',
  'sub_topics',
  'publishers',
  'media_types',
  'terms_of_use',
  'database_terms_of_use',
  'database_alternative_titles',
  'database_urls',
  'database_topics',
  'database_sub_topics',
);

foreach($tables as $table) {
  $sql[] = "TRUNCATE `$table`;";
}

// Taxonomies
$vocabularies = array(
  'database_availability', // used by field_access_information (?)
  'publishers',
  'media_types',
  'topics'
);

function escape($string) {
  return str_replace("'", "''", $string);
}

$vocab_term_entities = array();
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
      $terms_data[$term->tid] = $term;
    }
  }
  $vocab_term_entities[$vocabulary_name] = $terms_data;
}

// topics table
$topics_vocab = taxonomy_vocabulary_machine_name_load('topics');
$topics_terms = taxonomy_get_tree($topics_vocab->vid);
foreach($topics_terms as $term) {
  $entity = $vocab_term_entities['topics'][$term->tid];
  if (!$term->parents[0]) {
    $name_en = escape($entity->name_field['en'][0]['value']);
    $name_sv = escape($entity->name_field['sv'][0]['value']);
    $sql[] = "INSERT INTO `topics`(`id`, `name_en`, `name_sv`) VALUES({$term->tid}, '$name_en', '$name_sv');";
  }
}

// sub_topics table
foreach($topics_terms as $term) {
  $entity = $vocab_term_entities['topics'][$term->tid];
  if ($term->parents[0]) {
    $name_en = escape($entity->name_field['en'][0]['value']);
    $name_sv = escape($entity->name_field['sv'][0]['value']);
    $sql[] = "INSERT INTO `sub_topics`(`id`, `name_en`, `name_sv`, `topic_id`) VALUES({$term->tid}, '$name_en', '$name_sv', '{$term->parents[0]}');";
  }
}

// publishers table
foreach($vocab_term_entities['publishers'] as $tid => $entity) {
  $name = escape($entity->name);
  $sql[] = "INSERT INTO `publishers`(`id`, `name`) VALUES($tid, '$name')";
}


// media_types table
foreach($vocab_term_entities['media_types'] as $tid => $entity) {
  $name_en = escape($entity->name_field['en'][0]['value']);
  $name_sv = escape($entity->name_field['sv'][0]['value']);
  $sql[] = "INSERT INTO `media_types`(`id`, `name_en`, `name_sv`) VALUES($tid, $name_en', '$name_sv')";
}

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
    'field_scholarly_sharing',
    'field_print_article_chapter',
    'field_interlibrary_loan_desc',
    'field_interlibrary_loan',
    'field_gul_course_pack_electronic',
    'field_gul_course_pack_elect_desc',
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
    'field_topics_depth_0',
    'field_topics_depth_1',
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
      $database[substr($field_name, 6)] = NULL;
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
          $tid = intval($item['tid']);
          $database[substr($field_name, 6)][$tid] = $tid;
        }
      }
    }

    $database['title'] =  $database_node->title;
    $database['nid'] = $database_node->nid;

    $databases[$database_node->nid] = $database;
  }
}

$tou_mappings = array(
  1 => array(
    'name_en' => 'Print article/chapter',
    'name_sv' => 'Skriva ut artikel eller kapitel',
    'fields' => array(
      'print_article_chapter',
      'tou_article_chapt_desc'
    )
  ),
  2 => array(
    'name_en' => 'Download article/chapter',
    'name_sv' => 'Ladda ner artikel eller kapitel',
    'fields' => array(
      'download_article_chapter',
      'download_article_chap_desc'
    )
  ),
  3 => array(
    'name_en' => 'Course pack print',
    'name_sv' => 'Trycka kurskompendium',
    'fields' => array(
      'course_pack_print',
      'course_pack_print_desc'
    )
  ),
  4 => array(
    'name_en' => 'GUL / Course pack electronic',
    'name_sv' => 'Ladda upp kurskompendium på lärplattform',
    'fields' => array(
      'gul_course_pack_electronic',
      'gul_course_pack_elect_desc'
    )
  ),
  5 => array(
    'name_en' => 'Scholarly sharing',
    'name_sv' => 'Scholarly sharing', //Oversattning saknas???
    'fields' => array(
      'scholarly_sharing',
      'scholarly_sharing_desc'
    )
  ),
  6 => array(
    'name_en' => 'Interlibrary loan',
    'name_sv' => 'Fjärrlån',
    'fields' => array(
      'interlibrary_loan',
      'interlibrary_loan_desc'
    )
  ),
);

// terms_of_use table
foreach($tou_mappings as $id => $info) {
  // name/name/label??
  $sql[] = "INSERT INTO `terms_of_use`(`id`, `name_en`, `name_sv`) VALUES($id, '{$info['name_en']}', '{$info['name_sv']}');";
}

// database_terms_of_use table
foreach($databases as $id => $database) {
  foreach($tou_mappings as $tou_id => $info) {
    list($permitted_field_name, $description_field_name) = $info['fields'];
    if ($database[$permitted_field_name]) {
      $desc = escape($database[$description_field_name]);
      $permitted = $database[$permitted_field_name] == 'Yes' ? 'TRUE' : 'FALSE';
      $sql[] = "INSERT INTO `database_terms_of_use`(`database_id`, `terms_of_use_id`, `description_en`, `descripition_sv`, `permitted`) VALUES($id, $tou_id, '$desc', '', $permitted);";
    }
  }
}

// database_alternative_titles table
foreach($databases as $id => $database) {
  foreach($database['alternate_titles'] as $title) {
    $title = escape($title);
    $sql[] = "INSERT INTO `database_alternative_titles`(`database_id`, `title`) VALUES($id, '$title');";
  }
}

// database_urls table
foreach($databases as $id => $database) {
  foreach($database['database_urls'] as $url) {
    $title = escape($url['title']);
    $url = escape($url['url']);
    $sql[] = "INSERT INTO `database_urls`(`database_id`, `title`, `url`) VALUES($id, '$title', '$url');";
  }
}

// database_topics
foreach($databases as $database_id => $database) {
  foreach($database['topics_depth_0'] as $topic_id) {
    $is_recommended = isset($database['recommended_in_subjects'][$topic_id]) ? 'TRUE' : 'FALSE';
    $sql[] = "INSERT INTO `database_topics`(`database_id`, `topic_id`, `is_recommended`) VALUES($database_id, $topic_id, $is_recommended);";
  }
}

// database_sub_topics
foreach($databases as $database_id => $database) {
  foreach($database['topics_depth_1'] as $topic_id) {
    $is_recommended = isset($database['recommended_in_subjects'][$topic_id]) ? 'TRUE' : 'FALSE';
    $sql[] = "INSERT INTO `database_sub_topics`(`database_id`, `sub_topic_id`, `is_recommended`) VALUES($database_id, $topic_id, $is_recommended);";
  }
}

print implode("\n", $sql) . "\n";
