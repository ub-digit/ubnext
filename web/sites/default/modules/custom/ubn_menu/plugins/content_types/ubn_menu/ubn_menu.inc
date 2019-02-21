<?php
/**
 * @file
 */

//TODO: add info?
/**
 * Plugin definition.
 */
$plugin = array(
  'single' => FALSE,
  'title' => t('UBN Main menu'),
  'description' => t('The UBN Main menu'),
  'category' => 'UBN Menu',
);

function ubn_menu_ubn_menu_content_type_content_types() {
  $types = array();
  //TODO: Perhaps don't hard code
  $plugin = array(
    'category' => 'UBNext',
    //'edit form' => 'ubn_menu_slate_slate_gmap_content_type_settings',
  );
  $menu_name = 'main-menu';
  $menu_label = 'Main menu';

  //TODO: full instead of all
  foreach(array('all', 'top-level', 'menu-trail', 'bottom-level', 'bottom-level-dropdown') as $variant) {
    $types['ubn_menu:' . $menu_name . ':' . $variant ] = $plugin + array('title' => 'UBN Menu: ' .  $menu_label . ' (' . $variant . ')');
  }
  return $types;
}


/**
 * Settings callback.
 */
/*
function ubn_menu_ubn_menu_content_type_settings($form, &$form_state) {
  return $form;
}
function ubn_menu_ubn_menu_content_type_settings_submit($form, &$form_state) {
  foreach(array() as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
*/

/**
 * Render callback.
 */
function ubn_menu_ubn_menu_content_type_render($subtype, $conf, $panel_args, $context) {
  list(, $menu_name, $type) = explode(':', $subtype);
  $cache = &drupal_static(__FUNCTION__);
  $menu_names = array('main-menu', 'menu-shortcut-menu');

  if (!isset($cache['active_menu_name'])) {
    $preferred_item = menu_link_get_preferred();
    // Hmm, really set main-menu if no active??
    $cache['active_menu_name'] = is_array($preferred_item) && $preferred_item['menu_name'] ? $preferred_item['menu_name'] : 'main-menu';
  }
  $active_menu_name = $cache['active_menu_name'];

  foreach($menu_names as $menu_name) {
    if(!isset($cache[$menu_name . ':page_tree_by_level'])) {
      $page_tree = menu_tree_page_data($menu_name);
      _ubn_menu_prune($page_tree);
      $page_tree_by_level = _ubn_menu_menu_tree_by_level($page_tree);
      $cache[$menu_name . ':page_tree_by_level'] = $page_tree_by_level;
    }
  }
  $main_menu_page_tree_by_level = $cache['main-menu:page_tree_by_level'];
  $block = new stdClass();
  $block->title = t('UBN Menu'); //title?, none?

  switch($type) {
    case 'all':
      /*
      $menu_output_by_level = array();

      $menu_top_level = array_shift($menu_output_by_level);
      $menu_bottom_level = !empty($menu_output_by_level) ? array_pop($menu_output_by_level) : '';
      $menu_trail = !empty($menu_output_by_level) ? $menu_output_by_level : array();

      $block->content = slate_render('ubn-menu-main-menu',
        array(
          'menu_top_level' => $menu_top_level,
          'menu_trail' => $menu_trail,
          'menu_bottom_level' => $menu_bottom_level,
        )
      );
      break;
      */
    case 'top-level':
      $menu_top_level = array_shift($main_menu_page_tree_by_level);
      if (!empty($menu_top_level)) {
        $links = _ubn_menu_menu_tree_links($menu_top_level, FALSE);
        //TODO: implement menu-name wild card
        if (!empty($links)) {
          $block->content = slate_render('ubn-menu-top-level', array(
            'links' => $links
          ));
        }
      }
      break;
    case 'bottom-level':
      // First unshift top-level
      //array_shift($main_menu_page_tree_by_level);
      //$menu_bottom_level = array_pop($main_menu_page_tree_by_level);
      $menu_bottom_level = _ubn_menu_menu_tree_expanded_level($main_menu_page_tree_by_level);
      $block->content = '';
      if (!empty($menu_bottom_level)) {
        $links = _ubn_menu_menu_tree_links($menu_bottom_level, FALSE);
        //TODO: implement menu-name wild card
        if (!empty($links)) {
          $block->content = slate_render('ubn-menu-bottom-level', array(
            'links' => $links
          ));
        }
      }
      break;
    case 'bottom-level-dropdown':
      global $language; 
      $current_path = $GLOBALS['base_url'] . "/" . $language->language . "/" . current_path();
      $readspeaker_lang = 'sv_se';
      if ($language->language == 'en') {
        $readspeaker_lang = 'en_gb';
      }
      $menu_top_level = array_shift($main_menu_page_tree_by_level);
      $links = _ubn_menu_menu_tree_links($menu_top_level, FALSE);
      $block->content = slate_render('ubn-menu-top-level-dropdown', array(
        'links' => $links,
        'readspeaker_lang' => $readspeaker_lang,
        'current_path' => $current_path,
      ));
      break;
    case 'menu-trail':
      // We don't call drupal_get_breadcrumb() since
      // we don't whant menu_get_active_breadcrumb() called
      // if no breadcrumb is set. We have already handled that
      // case below.
      $breadcrumb_max_length = variable_get('ubn_menu_breadcrumb_max_length', 36);
      $trail = drupal_set_breadcrumb();

      if (empty($trail)) {
        foreach ($cache[$active_menu_name . ':page_tree_by_level'] as $level) {
          $links = _ubn_menu_menu_tree_links($level, TRUE);
          foreach ($links as $link) {
            if ($link['in_active_trail']) {
              // There is a slight inconsistency that we cannot easliy truncate
              // breakcrumb titles set by drupal_set_breadcrumb() (since already
              // rendered), but we can live with that.
              $link['title'] = truncate_utf8($link['title'], $breadcrumb_max_length, TRUE, TRUE);
              $trail[] = $link;
              break;
            }
          }
        }
        // trail is still empty, check if we may use node title for breadcrumb
        if (empty($trail)) {
          $node = menu_get_object();
          if (!empty($node)) {
            $link = array(
              'href' => url($node->title),
              'title' => $node->title,
            );
            $link['title'] = truncate_utf8($link['title'], $breadcrumb_max_length, TRUE, TRUE);
            $trail[] = $link;
          }
        }
        if (!empty($trail)) {
          array_unshift(
            $trail,
            array(
              'href' => url('<front>'),
              'title' => t('Home'),
            )
          );
        }
      }
      if (!empty($trail)) {
        $block->content = slate_render('ubn-menu-menu-trail', array(
          'links' => $trail,
        ));
      }
      else {
        $block->content = '';
      }
      break;
  }

  return $block;
}

function _ubn_menu_menu_tree_links($tree, $is_menu_trail = FALSE) {
  $items = array();
  // Pull out just the menu links we are going to render so that we
  // get an accurate count for the first/last classes.
  //&& (!isset($data['link']['ubn_menu_hidden']) || !$data['link']['ubn_menu_hidden'] && !$is_menu_trail)
  foreach ($tree as $data) {
    if  ($data['link']['access'] && !$data['link']['hidden'] && !(isset($data['link']['ubn_menu_hidden']) && $data['link']['ubn_menu_hidden'] && !$is_menu_trail)) {
      $items[] = $data;
    }
  }
  $links = array();
  foreach($items as $item) {
    $link = array();
    //url options?
    $link['href'] = url($item['link']['href']);
    $link['title'] = $item['link']['title'];
    $link['in_active_trail'] = $item['link']['in_active_trail'];
    $link['has_children'] = $item['link']['has_children'];
    // Since $item['below'] may contain local
    // tasks, only set 'expanded' if the link also has children
    // within the current menu.
    $link['expanded'] = $item['link']['has_children'] && !empty($item['ubn_menu_item_has_below']);
    $links[] = $link;
  }
  return $links;
}

//TODO: naming etc, I'm confusing even myself
// this code smells
function _ubn_menu_menu_tree_expanded_level($menu_tree_by_level) {
  if(count($menu_tree_by_level) > 1) {
    $last_level = array_pop($menu_tree_by_level);
    foreach($last_level as $item) {
      if($item['link']['in_active_trail']) {
        return array();
      }
    }
    return $last_level;
  }
  return array();
}

function _ubn_menu_menu_tree_by_level($menu_tree) {
  $menu_tree_by_level = array();
  $level = 0;
  do {
    $next_level_menu_tree = array();
    foreach($menu_tree as &$item) {
      if(!empty($item['below'])) {
        $next_level_menu_tree += $item['below'];
        $item['below'] = array();
        //Leave marker that this item is expanded as 'below'
        //will not indicat this any more
        $item['ubn_menu_item_has_below'] = TRUE; //? in active-trail
        // enough?
      }
    }
    $menu_tree_by_level[$level++] = $menu_tree;
    $menu_tree = $next_level_menu_tree;
  } while(!empty($menu_tree));
  return $menu_tree_by_level;
}

function _ubn_menu_prune(&$tree) {
  $no_active_trails = TRUE;
  foreach($tree as $item) {
    if($item['link']['in_active_trail']) {
      $no_active_trails = FALSE;
    }
    if($item['link']['in_active_trail'] && empty($item['below'])) {
      return;
    }
  }

  if($no_active_trails) {
    return;
  }

  foreach($tree as $key => $item) {
    if(!$item['link']['in_active_trail'] && $item['link']['plid']) {
      unset($tree[$key]);
    }
    else if(!empty($item['below'])) {
      _ubn_menu_prune($tree[$key]['below']);
    }
  }
}




/*
function _ubn_menu_partition_by_level($tree, $level = 0) {
  $items = array(
    $level => array(),
  );
  foreach($tree as $key => $item) {
    if(!empty($items['below'])) {
      $items = array_merge($items, ubn_menu_partition_by_level($items['below'], $level++));
      unset($items['below']);
    }
    $items[$level][$key] = $item;
  }
  return $items;
}
*/
