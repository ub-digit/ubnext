<?php
/**
 * @file
 * ubn_library_feeds.feeds_source_default.inc
 */

/**
 * Implements hook_feeds_source_default().
 */
function ubn_library_feeds_feeds_source_default() {
  $export = array();

  $feeds_source = new stdClass();
  $feeds_source->disabled = FALSE; /* Edit this to true to make a default feeds_source disabled initially */
  $feeds_source->api_version = 1;
  $feeds_source->id = 'libraries_opening_hours';
  $feeds_source->feed_nid = 0;
  $feeds_source->config = array(
    'UBNOpeningHoursFeedsFetcher' => array(
      'source' => 'http://openhours.ub.gu.se/locations',
    ),
  );
  $feeds_source->source = 'http://openhours.ub.gu.se/locations';
  $export['libraries_opening_hours'] = $feeds_source;

  $feeds_source = new stdClass();
  $feeds_source->disabled = FALSE; /* Edit this to true to make a default feeds_source disabled initially */
  $feeds_source->api_version = 1;
  $feeds_source->id = 'libraries_opening_hours_field_collection';
  $feeds_source->feed_nid = 0;
  $feeds_source->config = array(
    'UBNOpeningHoursFeedsFetcher' => array(
      'source' => 'http://openhours.ub.gu.se/locations',
    ),
  );
  $feeds_source->source = 'http://openhours.ub.gu.se/locations';
  $export['libraries_opening_hours_field_collection'] = $feeds_source;

  return $export;
}
