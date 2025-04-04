<?php

/**
 * @file
 * ubn_general.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function ubn_general_filter_default_formats() {
  $formats = array();

  // Exported format: Markdown.
  $formats['markdown'] = array(
    'format' => 'markdown',
    'name' => 'Markdown',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'ubn_entityform' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(),
      ),
      'ubn_scald_wrap_sas_atoms' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(),
      ),
      'ubn_markdown' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_markdown' => array(
        'weight' => -47,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -46,
        'status' => 1,
        'settings' => array(),
      ),
      'pathologic' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(
          'settings_source' => 'global',
          'local_paths' => '',
          'protocol_style' => 'full',
          'local_settings' => array(
            'protocol_style' => 'path',
            'local_paths' => '',
          ),
        ),
      ),
      'ubn_scald_render_sas_atoms' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
