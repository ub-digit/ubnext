<?php
error_reporting(E_ALL & ~E_NOTICE & ~E_DEPRECATED & ~E_WARNING);

include dirname(__FILE__) . DIRECTORY_SEPARATOR . 'secret.settings.php';
include dirname(__FILE__) . DIRECTORY_SEPARATOR . 'site.settings.php';


$conf['page_cache_invoke_hooks'] = TRUE;

/**
 * Multilingual settings
 *
 * This is a collection of variables that can be set up for each language when
 * internationalization (i18n) is enabled. These are the basic ones for Drupal
 * core, but you can add your own here.
 */
$conf['i18n_variables'] = array(
  'site_name',
  'site_slogan',
  'site_mission',
  'site_footer',
  'anonymous',
  'menu_primary_menu',
  'menu_secondary_menu',
  'footer_col1',
  'footer_col2',
  'footer_col3',
  'slogan',
  'placeholder',
  'aria_label',
  'link_logotype',
  'aria_label_logotype',
);

// Prevent drupal from scanning certain folders when looking for theme and template files.
$conf['file_scan_ignore_directories'] = array( 'node_modules',  'bower_components');

if (
  isset($_SERVER['HTTP_X_FORWARDED_PROTO']) &&
  strtolower($_SERVER['HTTP_X_FORWARDED_PROTO']) == 'https'
  ) {
  $_SERVER['HTTPS'] = 'on';
}

if (isset($_SERVER['HTTP_X_FORWARDED_PORT'])) {
  $_SERVER['SERVER_PORT'] = intval($_SERVER['HTTP_X_FORWARDED_PORT']);
}

