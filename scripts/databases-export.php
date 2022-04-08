<?php

$sql = array();
$tables = array(
  'databases',
  'topics',
  'sub_topics',
  'publishers',
  'media_types',
  'database_terms_of_use',
  'database_alternative_titles',
  'database_urls',
  'database_topics',
  'database_sub_topics',
);

foreach($tables as $table) {
  $sql[] = "TRUNCATE $table;";
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
    $sql[] = "INSERT INTO topics(id, name_en, name_sv) VALUES({$term->tid}, '$name_en', '$name_sv');";
  }
}

// sub_topics table
foreach($topics_terms as $term) {
  $entity = $vocab_term_entities['topics'][$term->tid];
  if ($term->parents[0]) {
    $name_en = escape($entity->name_field['en'][0]['value']);
    $name_sv = escape($entity->name_field['sv'][0]['value']);
    $sql[] = "INSERT INTO sub_topics(id, name_en, name_sv, topic_id) VALUES({$term->tid}, '$name_en', '$name_sv', '{$term->parents[0]}');";
  }
}

// publishers table
foreach($vocab_term_entities['publishers'] as $tid => $entity) {
  $name = escape($entity->name);
  $sql[] = "INSERT INTO publishers(id, name) VALUES($tid, '$name');";
}


// media_types table
foreach($vocab_term_entities['media_types'] as $tid => $entity) {
  $name_en = escape($entity->name_field['en'][0]['value']);
  $name_sv = escape($entity->name_field['sv'][0]['value']);
  $sql[] = "INSERT INTO media_types(id, name_en, name_sv) VALUES($tid, '$name_en', '$name_sv');";
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
      print_r($value);
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

    #$name_sv = escape($entity->name_field['sv'][0]['value']);
    $databases[$database_node->nid] = $database;
    #print_r($databases);
    #exit;

    
  }
}

# database table
foreach ($databases as $db) {
  $id = $db['nid'];
  $title_sv = escape($db['title']) . ' (sv)';
  $title_en = escape($db['title']) . ' (en)';
  $description_sv = escape($db['description']) . ' (sv)';
  $description_en = escape($db['description']) . ' (en)';
  $is_popular = (boolval($db['promote_to_shortcut']) ? 'TRUE' : 'FALSE');
  $malfunction_message_active = (boolval($db['malfunction_message_active'] ?: 0) ? 'TRUE' : 'FALSE');
  $malfunction_message = $db['$malfunction_message'] ?: NULL;
  $public_access = (boolval($db['public_access']) ? 'TRUE' : 'FALSE');
  $access_information_code = $db['access_information'];

  switch (array_values($access_information_code)[0]) {
    case '745':
        $access_information_code = 'freely_available';
        break;
    case '748':
        $access_information_code = 'available_to_the_university_of_gothenburg';
        break;
    case '751':
        $access_information_code = 'available_to_the_university_of_gothenburg_on_campus_only_available_to_anyone';
        break;
    case '752':
        $access_information_code = 'available_to_the_university_of_gothenburg_available_to_anyone_using_the_libraries_computers';
        break;
    default:
    $access_information_code = '';
  }
  
  
  $sql[] = "INSERT INTO databases(id, title_en, title_sv, description_en, description_sv, is_popular, malfunction_message, malfunction_message_active, public_access, access_information_code) VALUES($id, '$title_sv', '$title_en', '$description_en', '$description_sv', $is_popular, '$malfunction_message', $malfunction_message_active, $public_access, '$access_information_code');";
  
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
//foreach($tou_mappings as $id => $info) {
  // name/name/label??
  //print_r($id);
  //print_r(" ");
  //print_r($info['name_sv']);
  //print_r($info['name_en']);
  //print_r("\n");
  //$sql[] = "INSERT INTO terms_of_use(id, name_en, name_sv) VALUES($id, '{$info['name_en']}', '{$info['name_sv']}');";
//}

// database_terms_of_use table

foreach($databases as $id => $database) {
  foreach($tou_mappings as $tou_id => $info) {
    list($permitted_field_name, $description_field_name) = $info['fields'];
    if ($database[$permitted_field_name]) {
     // print_r("\n\n");
    // print_r($tou_id);
      switch ($tou_id) {
        case '1':
            $tou_code = 'print_article_chapter';
            break;
        case '2':
            $tou_code = 'download_article_chapter';
            break;
        case '3':
          $tou_code = 'course_pack_print';
            break;
        case '4':
          $tou_code = 'gul_course_pack_electronic';
            break;
        case '5':
          $tou_code = 'cholarly_sharing';
            break;
        case '6':
          $tou_code = 'interlibrary_loan';
            break;    
        default:
        $access_information_code = '';
      }
      //print_r($tou_code . " \n");
      $desc = escape($database[$description_field_name]);
      $permitted = $database[$permitted_field_name] == 'Yes' ? 'TRUE' : 'FALSE';
      $sql[] = "INSERT INTO database_terms_of_use(database_id, code, description_en, description_sv, permitted) VALUES($id, '$permitted_field_name', '$desc', '', $permitted);";
    }
  }
}

// database_media_types table
foreach($databases as $database_id => $database) {
  foreach($database['media_types'] as $media_type_id) {
    $sql[] = "INSERT INTO database_media_types(database_id, media_type_id) VALUES($database_id, $media_type_id);";  
  }
}

// database_alternative_titles table
foreach($databases as $id => $database) {
  foreach($database['alternate_titles'] as $title) {
    $title = escape($title);
    $sql[] = "INSERT INTO database_alternative_titles(database_id, title) VALUES($id, '$title');";
  }
}

// database_urls table
foreach($databases as $id => $database) {
  foreach($database['database_urls'] as $url) {
    $title = escape($url['title']);
    $url = escape($url['url']);
    $sql[] = "INSERT INTO database_urls(database_id, title, url) VALUES($id, '$title', '$url');";
  }
}

// database_topics table
foreach($databases as $database_id => $database) {
  foreach($database['topics_depth_0'] as $topic_id) {
    $is_recommended = isset($database['recommended_in_subjects'][$topic_id]) ? 'TRUE' : 'FALSE';
    $sql[] = "INSERT INTO database_topics(database_id, topic_id, is_recommended) VALUES($database_id, $topic_id, $is_recommended);";
  }
}

// database_sub_topics table
foreach($databases as $database_id => $database) {
  foreach($database['topics_depth_1'] as $topic_id) {
    $is_recommended = isset($database['recommended_in_subjects'][$topic_id]) ? 'TRUE' : 'FALSE';
    $sql[] = "INSERT INTO database_sub_topics(database_id, sub_topic_id, is_recommended) VALUES($database_id, $topic_id, $is_recommended);";
  }
}

// database_publishers table
foreach($databases as $database_id => $database) {
  foreach($database['publishers'] as $publisher_id) {
    $sql[] = "INSERT INTO database_publishers(database_id, publisher_id) VALUES($database_id, $publisher_id);";
  }
}

//print implode("\n", $sql) . "\n";
