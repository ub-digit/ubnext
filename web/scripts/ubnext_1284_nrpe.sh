#!/usr/bin/env php
<?php

// Define default settings.
define('DRUPAL_ROOT', getcwd());
$cmd = 'index.php';
$_SERVER['HTTP_HOST']       = 'default';
$_SERVER['REMOTE_ADDR']     = '127.0.0.1';
$_SERVER['SERVER_SOFTWARE'] = NULL;
$_SERVER['REQUEST_METHOD']  = 'GET';
$_SERVER['QUERY_STRING']    = '';
$_SERVER['PHP_SELF']        = $_SERVER['REQUEST_URI'] = '/';
$_SERVER['HTTP_USER_AGENT'] = 'console';

// Bootstrap Drupal.
include_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

/*
$result = db_query("SELECT fd.title_field_value, fd.entity_type, fd.entity_id, fd.language, et.language AS et_language, et.source AS et_source FROM field_data_title_field fd LEFT OUTER JOIN entity_translation et on fd.entity_type = et.entity_type AND fd.entity_id = et.entity_id AND fd.language = et.language WHERE et.entity_id IS NULL");
*/
$result = db_query("SELECT fd.entity_type, fd.entity_id AS et_source FROM field_data_title_field fd LEFT OUTER JOIN entity_translation et on fd.entity_type = et.entity_type AND fd.entity_id = et.entity_id AND fd.language = et.language WHERE et.entity_id IS NULL");

$rows = array();
foreach($result as $row) {
  $row = (array) $row;
  $rows[] = implode(':', $row);
}
// 1024 bytes is the nrpe limit
$message = "WARNING - Corrupted language data for: ";
$info = mb_strcut(implode(', ', $rows), 0, 1024 - mb_strlen($message));
if (!empty($info)) {
  // We have a problem
  print $message . $info;
  exit(1);
}
else {
  // Everything is ok
  print "OK";
  exit(0);
}
