<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('UBN Nav: Lists all sub-navigational items in menu'),
  'description' => t('Lists all sub-nav elements in menu.'),
  'required context' => new ctools_context_required(t('sub-nav'), 'entity:node'),
  'category' => 'UBNext',
  'edit form' => 'ubn_nav_sub_menu_items_content_type_settings',
);

/**
 * Settings callback.
 */
function ubn_nav_sub_menu_items_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_nav_sub_menu_items_content_type_render($subtype, $conf, $panel_args, $context) {
  // Set $path to the internal Drupal path of the parent or
// to NULL for the current path 
  $path = NULL;
  $parent = menu_link_get_preferred($path);
  $parameters = array(
      'active_trail' => array($parent['plid']),
      'only_active_trail' => FALSE,
      'min_depth' => $parent['depth']+1,
      'max_depth' => $parent['depth']+1,
      'conditions' => array('plid' => $parent['mlid']),
    );

  $use_one_col_layout = false;
  if (count($context->data->field_layout) > 0) {
    if ($context->data->field_layout['und'][0]['value'] == '1-column') {
      $use_one_col_layout = true;
    }
  }

  $children = menu_build_tree($parent['menu_name'], $parameters);
  $content = slate_render('navigation-landing-theme-links', array('page' => $context->data, 'children' => $children, 'onecol' => $use_one_col_layout));

  $block = new stdClass();
  $block->title = '';
  $block->content = $content;
  return $block;
}
