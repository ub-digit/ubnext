<?php

/**
 * @file
 * ubn_content_types.linkit_profiles.inc
 */

/**
 * Implements hook_default_linkit_profiles().
 */
function ubn_content_types_default_linkit_profiles() {
  $export = array();

  $linkit_profile = new LinkitProfile();
  $linkit_profile->disabled = FALSE; /* Edit this to true to make a default linkit_profile disabled initially */
  $linkit_profile->api_version = 1;
  $linkit_profile->name = 'ubnext';
  $linkit_profile->admin_title = 'ubnext';
  $linkit_profile->admin_description = '';
  $linkit_profile->profile_type = '2';
  $linkit_profile->data = array(
    'search_plugins' => array(
      'entity:search_api_autocomplete_search' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:taxonomy_term' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:user' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:comment' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:search_api_sort' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:scald_atom' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:node' => array(
        'enabled' => 1,
        'weight' => '-10',
      ),
      'entity:menu_position_rule' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:search_api_page' => array(
        'enabled' => 1,
        'weight' => '-10',
      ),
      'entity:search_api_server' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:file' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:search_api_index' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:menu_link' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
    ),
    'entity:node' => array(
      'result_description' => '',
      'bundles' => array(
        'page' => 'page',
        'library' => 'library',
        'navigation_landing' => 'navigation_landing',
        'app' => 0,
        'article' => 0,
        'database' => 0,
        'opening_hours' => 0,
      ),
      'group_by_bundle' => 0,
      'include_unpublished' => 0,
    ),
    'entity:taxonomy_term' => array(
      'result_description' => '',
      'bundles' => array(
        'tags' => 0,
        'library_properties' => 0,
        'wlan' => 0,
        'media_types' => 0,
        'publishers' => 0,
        'topics' => 0,
        'scald_authors' => 0,
        'scald_tags' => 0,
        'special_collection' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'entity:comment' => array(
      'result_description' => '',
      'bundles' => array(
        'comment_node_app' => 0,
        'comment_node_article' => 0,
        'comment_node_page' => 0,
        'comment_node_database' => 0,
        'comment_node_library' => 0,
        'comment_node_navigation_landing' => 0,
        'comment_node_opening_hours' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'entity:scald_atom' => array(
      'result_description' => '',
      'bundles' => array(
        'file' => 0,
        'image' => 0,
        'video' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'entity:menu_position_rule' => array(
      'result_description' => '',
    ),
    'entity:search_api_server' => array(
      'result_description' => '',
    ),
    'entity:search_api_index' => array(
      'result_description' => '',
    ),
    'entity:search_api_autocomplete_search' => array(
      'result_description' => '',
    ),
    'entity:search_api_page' => array(
      'result_description' => '',
    ),
    'entity:search_api_sort' => array(
      'result_description' => '',
    ),
    'entity:file' => array(
      'result_description' => '',
      'show_scheme' => 0,
      'group_by_scheme' => 0,
      'url_type' => 'direct',
      'image_extra_info' => array(
        'thumbnail' => 'thumbnail',
        'dimensions' => 'dimensions',
      ),
    ),
    'entity:user' => array(
      'result_description' => '',
    ),
    'entity:menu_link' => array(
      'result_description' => '',
      'bundles' => array(
        'devel' => 0,
        'features' => 0,
        'main-menu' => 0,
        'management' => 0,
        'navigation' => 0,
        'user-menu' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'insert_plugin' => array(
      'plugin' => 'raw_url',
      'url_method' => '1',
    ),
    'attribute_plugins' => array(
      'accesskey' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'target' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'class' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'rel' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'id' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'title' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
    ),
    'autocomplete' => array(
      'charLimit' => '3',
      'wait' => '350',
      'remoteTimeout' => '10000',
    ),
  );
  $export['ubnext'] = $linkit_profile;

  return $export;
}
