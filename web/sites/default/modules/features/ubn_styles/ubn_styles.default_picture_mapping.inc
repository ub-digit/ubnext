<?php
/**
 * @file
 * ubn_styles.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function ubn_styles_default_picture_mapping() {
  $export = array();

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Hero';
  $picture_mapping->machine_name = 'hero';
  $picture_mapping->breakpoint_group = 'hero';
  $picture_mapping->mapping = array(
    'breakpoints.theme.ubnext.small' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'hero_small',
      ),
    ),
    'breakpoints.theme.ubnext.extra_small' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'hero_small_extra_small',
      ),
    ),
  );
  $export['hero'] = $picture_mapping;

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Page content';
  $picture_mapping->machine_name = 'page_content';
  $picture_mapping->breakpoint_group = 'page_content';
  $picture_mapping->mapping = array(
    'breakpoints.theme.ubnext.small' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'page_content',
      ),
    ),
    'breakpoints.theme.ubnext.extra_small' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'page_content_extra_small',
      ),
    ),
  );
  $export['page_content'] = $picture_mapping;

  return $export;
}
