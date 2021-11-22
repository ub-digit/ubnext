<?php

/**
 * @file
 * ubn_startpage.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function ubn_startpage_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'front_page_blurbs';
  $queue->label = 'Front page blurbs';
  $queue->language = 'sv';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'blurb' => 'blurb',
      'event' => 'event',
      'story' => 'story',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 1,
  );
  $export['front_page_blurbs'] = $queue;

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'front_page_blurbs_navigation';
  $queue->label = 'Front page navigation blurbs';
  $queue->language = 'sv';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'navigation_landing' => 'navigation_landing',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['front_page_blurbs_navigation'] = $queue;

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'front_page_blurbs_secondary';
  $queue->label = 'Front page blurbs secondary';
  $queue->language = 'sv';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'blurb' => 'blurb',
      'event' => 'event',
      'story' => 'story',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['front_page_blurbs_secondary'] = $queue;

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'panels_links_primary_on_frontpage';
  $queue->label = 'Panels links primary on frontpage';
  $queue->language = 'sv';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'link_list' => 'link_list',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['panels_links_primary_on_frontpage'] = $queue;

  return $export;
}
