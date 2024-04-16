<?php
$databases = array (
  'default' =>
   array (
     'default' =>
      array (
       'database' => 'drupal7_ubnext',
       'username' => 'drupal7_ubnext',
       'password' => 'drupal7_ubnext',
       'host' => 'database',
       'port' => '',
       'driver' => 'mysql',
       'prefix' => '',
     ),
   ),
);

$drupal_hash_salt = getenv('UBN_DRUPAL_HASH_SALT');
$conf['ubn_summon_access_id'] = getenv('UBN_SUMMON_ACCESS_ID');
$conf['ubn_summon_secret_key'] = getenv('UBN_SUMMON_SECRET_KEY');
$conf['ubn_google_key'] = getenv('UBN_GOOGLE_KEY');
