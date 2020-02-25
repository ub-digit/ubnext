<?php

function create_dc_element($doc, $name, $value) {
  $element = $doc->createElementNS('http://purl.org/dc/elements/1.1/', "dc:$name", htmlspecialchars($value));
  //$element = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/oai_dc/', "oai_dc:$name", htmlspecialchars($value));
  return $element;
}

$query = new EntityFieldQuery();

$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'database')
  ->propertyCondition('status', NODE_PUBLISHED);

$result = $query->execute();

$doc = new DOMDocument('1.0', 'utf-8');
$doc->formatOutput = true;
#$root = $dom->createElementNS('http://purl.org/dc/elements/1.1/', 'dc');
$root = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'OAI-PMH');
$root->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
$root->setAttributeNS(
  'http://www.w3.org/2001/XMLSchema-instance',
  'xsi:schemaLocation',
  'http://www.openarchives.org/OAI/2.0/ http://www.openarchives.org/OAI/2.0/OAI-PMH.xsd'
);

$doc->appendChild($root);

$records = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'ListRecords'); //??
//$records = $doc->createElement('ListRecords'); //??
$root->appendChild($records);

if (isset($result['node'])) {
  $database_nodes = entity_load('node', array_keys($result['node']));

  foreach ($database_nodes as $database_node) {
    $database = entity_metadata_wrapper('node', $database_node);
    $nid = $database->getIdentifier();

    $record = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'record');
    $records->appendChild($record);

    $header = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'header');
    $record->appendChild($header);

    $identifier = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'identifier', "oai:ubnext/databases/$nid");
    $header->appendChild($identifier);

    $datestamp = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'datestamp', date('c'));
    $header->appendChild($datestamp);

    $metadata = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/', 'metadata');
    $record->appendChild($metadata);

    $dc = $doc->createElementNS('http://www.openarchives.org/OAI/2.0/oai_dc/', 'oai_dc:dc');
    $dc->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
    $dc->setAttributeNS(
      'http://www.w3.org/2001/XMLSchema-instance',
      'xsi:schemaLocation',
      'http://www.openarchives.org/OAI/2.0/oai_dc/ http://www.openarchives.org/OAI/2.0/oai_dc.xsd'
    );

    $dc->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:dc', 'http://purl.org/dc/elements/1.1/');

    $database_sv = $database->language('sv');

    $element = create_dc_element($doc, 'title', $database_sv->title->value());
    $dc->appendChild($element);

    if ($database_sv->field_description->value()) {
      $element = create_dc_element($doc, 'description', $database_sv->field_description->value->value());
      $dc->appendChild($element);
    }

    foreach ($database->field_publishers as $publisher) {
      $element = create_dc_element($doc, 'publisher', $publisher->name->value());
      $dc->appendChild($element);
    }

    $element = create_dc_element($doc, 'identifier', $nid);
    $dc->appendChild($element);

    foreach ($database_sv->field_media_types as $media_type) {
      $element = create_dc_element($doc, 'type', $media_type->name->value());
      $dc->appendChild($element);
    }

    foreach ($database_sv->field_topics as $topic) {
      $element = create_dc_element($doc, 'subject', $topic->name->value());
      $dc->appendChild($element);
    }

    $element = create_dc_element($doc, 'modified', date('c', $database_sv->changed->value()));
    $dc->appendChild($element);

    $metadata->appendChild($dc);
  }
}

$xml = $doc->saveXML();

$output_filename = '46GUB-' . date('Y-m-d-H-i-s') . '.xml';
$output_filepath = "/tmp/$output_filename";
file_put_contents($output_filepath, $xml);

try {
  $archive = new PharData("$output_filepath.tar");
  $archive->addFile($output_filepath, $output_filename);
  $filepath_compressed = $archive->compress(Phar::GZ)->getPath();
  //unlink("$output_filepath.tar"); //????
  unlink($output_filepath);
}
catch (Exception $e) {
  die("Something went wrong: " . $e);
}

$exit_code = null;
$output = array();
$user = variable_get('primo_databases_scp_user', 'primo');
//$host = variable_get('primo_databases_scp_host', 'koha-staging.ub.gu.se');
$host = variable_get('primo_databases_scp_host', 'koha.ub.gu.se');
$dir = rtrim(variable_get('primo_databases_scp_directory', '/var/lib/koha/primo/databases'), '/');

exec("scp $filepath_compressed $user@$host:$dir", $output, $exit_code);

if ($exit_code) {
  die(implode("\n", $output) . "\n");
}
