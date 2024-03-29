<?php
/**
 * @file
 */


/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Guide: Table of Contents'),
  'description' => t('Table of contents for a Guide.'),
  'category' => 'UBNext',
  'required context' => new ctools_context_required(t('Guide'), 'entity:node'),
  'edit form' => 'ubn_guide_guide_toc_content_type_settings',
);


/**
 * Settings callback.
 */
function ubn_guide_guide_toc_content_type_settings($form, &$form_state) {
  return $form;
}

/**
 * Render callback.
 */
function ubn_guide_guide_toc_content_type_render($subtype, $conf, $panel_args, $context) {
  if (empty($context->data)) {
    return;
  }

  $node = entity_metadata_wrapper('node', $context->data);

  $block = new stdClass();
  $block->title = t('Table of Contents');

  $root = ubn_guide_get_root($node);
  $tree = ubn_guide_get_children($root->getIdentifier());
  $flat = ubn_guide_flatten($tree);

  if (count($flat) < 2) {
    return $block;
  }

  $tree = _ubn_guide_generate_tree($node);

  $root = ubn_guide_get_root($node);
  $root_path = "node/{$root->getIdentifier()}";

  $block->content = slate_render('guide-toc', array(
    'tree' => drupal_render($tree),
    'root' => array(
      'label' => $root->label(),
      'url' => url($root_path),
      'active' => ($root_path == $_GET['q']),
    ),
  ));

  return $block;
}

/**
 * Generate ToC tree to be used with item_list.
 */
function _ubn_guide_generate_tree($node, $tree = NULL, $parents = NULL, $nodes = NULL) {
  if ($tree === NULL) {
    $root = ubn_guide_get_root($node);
    $tree = ubn_guide_get_children($root->getIdentifier());
    $flat = ubn_guide_flatten($tree);
    $nodes = array_map(function($entity) { return entity_metadata_wrapper('node', $entity); }, entity_load('node', $flat));
    $parents = ubn_guide_get_parents($node);
  }

  $build = array(
    '#sorted' => TRUE,
    '#theme_wrappers' => array('menu_tree'),
  );

  foreach ($tree as $id => $children) {
    $uri = entity_uri('node', $nodes[$id]->value());

    $link = array(
      '#theme' => 'menu_link',
      '#title' => $nodes[$id]->label(),
      '#href' => $uri['path'],
      '#localized_options' => array(),
      '#attributes' => array(),
      '#below' => array(),
    );

    // We don't need active-trail right now.
    // if ($id == $node->getIdentifier()) {
    //   $link['#attributes']['class'][] = 'active-trail';
    // }

    if (empty($children)) {
      $link['#attributes']['class'][] = 'leaf';
    }
    else {
      if (in_array($id, $parents) || $id == $node->getIdentifier()) {
        $link['#attributes']['class'][] = 'expanded';

        // We don't need active-trail right now.
        // $link['#attributes']['class'][] = 'active-trail';
      }
      else {
        $link['#attributes']['class'][] = 'collapsed';
      }

      $link['#below'] = _ubn_guide_generate_tree($node, $children, $parents, $nodes);
    }

    $build[] = $link;
  }

  return $build;
}
