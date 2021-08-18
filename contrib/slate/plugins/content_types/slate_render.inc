<?php
/**
 * @file
 */


$plugin = array(
  'title' => 'Slate Render',
);


/**
 *
 */
function slate_slate_render_content_type_content_type($subtype) {
  $types = slate_slate_render_content_type_content_types();
  if (isset($types[$subtype])) {
    return $types[$subtype];
  }
}

/**
 *
 */
function slate_slate_render_content_type_content_types() {
  $types = array();

  foreach (slate_get_slates() as $slate => $slate_info) {
    $plugin = array(
      'title' => $slate_info['name'],
      'category' => 'Slate',
      'edit form' => 'slate_slate_render_content_type_content_type_settings',
    );

    if(isset($slate_info['conf'])) {
      $plugin['slate_conf'] = $slate_info['conf'];
    }

    foreach ($slate_info['models'] as $model => $model_info) {
      $model_plugin = slate_load_model($model_info);

      if (empty($model_plugin)) {
        // @todo this is bad!

        continue(2);
      }

      $required_contexts = $model_plugin->requiredContexts();

      if (!empty($required_contexts)) {
        $plugin['required context'] = $required_contexts;
      }
    }

    $types['slate_render:' . $slate] = $plugin;
  }

  return $types;
}

/**
 *
 */
function slate_slate_render_content_type_content_type_settings($form, &$form_state) {
  $subtype = $form_state['subtype'];
  //TODO: flesh this out more, support more types etc
  // but keep simple
  if(isset($subtype['slate_conf'])) {
    $conf = $form_state['conf'];
    foreach($subtype['slate_conf'] as $key => $info) {
      //Namespaced in own fieldset?
      //bool/boolean normalization?
      //t or not?
      $element = array(
        '#title' => isset($info['label']) ? $info['label'] : 'missing label',
        '#descripiton' => isset($info['description']) ? $info['description'] : NULL,
      );
      $type = isset($info['type']) ? $info['type'] : 'bool';
      switch($type) {
        case 'bool':
          $element['#type'] = 'checkbox';
          break;
        default:
      }
      $element['#default_value'] = isset($conf[$key]) ? $conf[$key] : NULL;
      if(isset($element['#type'])) {
        $form[$key] = $element;
      }
    }
  }
  //Form save
  return $form;
}

function slate_slate_render_content_type_content_type_settings_submit($form, &$form_state) {
  $subtype = $form_state['subtype'];
  if(isset($subtype['slate_conf'])) {
    foreach (array_keys($subtype['slate_conf']) as $key) {
      if(isset($form_state['values'][$key])) {
        $form_state['conf'][$key] = $form_state['values'][$key];
      }
    }
  }
}

/**
 *
 */
function slate_slate_render_content_type_render($subtype, $conf, $panel_args, $context) {
  // We want to be able to create slates withouts models for page elements
  // footer etc
  /*
  if (empty($context)) {
    return FALSE;
  }
  */

  list(, $slate) = explode(':', $subtype);

  $slate_info = slate_get_slate($slate);

  $models = array();
  if (isset($slate_info['models']['conf'])) {
    $models['conf'] = $conf;
    unset($slate_info['models']['conf']);
  }
  else if (isset($slate_info['conf'])) {
    $models['conf'] = array_intersect_key($conf, $slate_info['conf']);
    unset($slate_info['models']['conf']);
  }

  foreach ($slate_info['models'] as $model => $model_type) {
    $models[$model] = array_shift($context)->data;
  }

  $block = new stdClass();
  $block->module = 'slate';
  $block->title = $slate_info['name'];
  $block->content = slate_render($slate, $models);

  return $block;
}

/**
 *
 */
function slate_slate_render_content_type_admin_title($subtype, $conf, $context) {
  list(, $slate) = explode(':', $subtype);

  $slate_info = slate_get_slate($slate);

  return t('Rendered using slate "@name"', array('@name' => $slate_info['name']));
}
