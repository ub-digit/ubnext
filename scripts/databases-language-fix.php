<?php
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'database');
$result = $query->execute();
$databases = entity_load('node', array_keys($result['node']));

// TODO: clear feed items

$translation_en = array(
  'language' => 'en',
  'source' => '',
  'status' => 1,
  'uid' => 1,
  'created' => time(),
);

$translation_sv = array(
  'language' => 'sv',
  'source' => 'en',
  'status' => 1,
  'uid' => 1,
  'created' => time(),
);

// Cache all translatable fields
$translatable_fields = array();
foreach(field_info_instances('node', 'database') as $instance) {
  $field_name = $instance['field_name'];
  $field = field_info_field($field_name);
  if ($field['translatable']) {
    $translatable_fields[$field_name] = $field_name;
  }
}

foreach($databases as $database) {

  //  TODO: Emulate entityFormSubmit
  //  setOutdated?
  //  setOriginalLanguage
  //  setFormLanguage

  foreach($translatable_fields as $field_name) {
    if(isset($database->{$field_name}['und'])) {
      $database->{$field_name}['en'] = $database->{$field_name}['und'];
      $database->{$field_name}['und'] = array();
    }
  }

  $database->language = 'en'; //????
  $handler = entity_translation_get_handler('node', $database);

  $translations = $handler->getTranslations();

  // Only change original language to english if language neutral
  if ($translations->original === 'und') {
    // entity_type, entity_id etc on translation??
    //$handler->setEntity($database); //??
    $handler->setFormLanguage('en');
    $handler->setOriginalLanguage('en');
    $handler->setTranslation($translation_en);
    $entity = $handler->getEntity();
    entity_save('node', $entity);
  }
}

// Load again without cache
$databases = entity_load('node', array_keys($result['node']), array(), TRUE);
foreach($databases as $database) {
  foreach($translatable_fields as $field_name) {
    if(isset($database->{$field_name}['en'])) {
      $database->{$field_name}['sv'] = $database->{$field_name}['en'];
    }
  }

  $entity_wrapper = entity_metadata_wrapper('node', $database);

  // Only add swedish translation if not already exists
  $handler = entity_translation_get_handler('node', $database);
  $handler->setFormLanguage('sv');
  $handler->setTranslation($translation_sv);
  $entity = $handler->getEntity();
  entity_save('node', $entity);
}
?>
