<?php

/**
 * @file
 * ubn_general.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function ubn_general_locale_default_languages() {
  $languages = array();

  // Exported language: en.
  $languages['en'] = array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => 0,
  );
  // Exported language: sv.
  $languages['sv'] = array(
    'language' => 'sv',
    'name' => 'Swedish',
    'native' => 'Svenska',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n!=1)',
    'domain' => '',
    'prefix' => 'sv',
    'weight' => 0,
  );
  return $languages;
}
