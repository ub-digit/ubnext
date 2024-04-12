<?php
$conf['ubn_environment'] = getenv('UBN_ENVIRONMENT');
$conf['file_temporary_path'] = '/tmp/drupal7_ubn_' . $conf['ubn_environment'];
$conf['ubn_settings_solr_host'] = 'solr';
$conf['slate_cache_enabled'] = getenv('UBN_SLATE_CACHE_ENABLED');
$conf['ubn_terms_cache'] = getenv('UBN_TERMS_CACHE_ENABLED');

