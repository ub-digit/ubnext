<?php
/**
 * @file
 */

// override theme pager
function ubnext_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => '<i class="fa fa-chevron-left"></i>', 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => '<i class="fa fa-chevron-right"></i>', 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }

    
    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ));
  }
}

function ubnext_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array('query' => $query));
  return '<a' . drupal_attributes($attributes) . '>' . $text . '</a>';
}


function ubnext_links__locale_block($variables) {
  global $language;
  unset($variables['links'][$language->language]);
  return theme('links', $variables);
}

function ubnext_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item', 'form-group');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  if ($element['#type'] == 'checkbox') {
    $attributes['class'][] = 'checkbox';
  }


    // Check for errors and set correct error class.
  if (isset($element['#parents']) && form_get_error($element)) {
    $attributes['class'][] = 'has-error';
    $element['#field_prefix'] = '<div class="error-msg">' . form_get_error($element) . '</div>';
  }


  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  if ($element['#type'] == 'checkbox') {
    $variables['rendered_element'] = ' ' . /*$prefix .*/ $element['#children'] . "\n";
    $output .= theme('form_element_label', $variables) /*. $suffix */;
  }
  else {

    switch ($element['#title_display']) {
      case 'before':
      case 'invisible':

        $output .= ' ' . theme('form_element_label', $variables);
        if (!empty($element['#description'])) {
          $output .= '<div class="help-block">' . $element['#description'] . "</div>\n";
        }
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;

      case 'after':
        $output .= ' ' . $prefix . $element['#children'] . $suffix;
        $output .= ' ' . theme('form_element_label', $variables) . "\n";
        break;

      case 'none':
      case 'attribute':
        // Output no label and no required marker, only the children.
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }



  $output .= "</div>\n";

  return $output;
}


function ubnext_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  $attributes['class'][] = 'control-label';
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }
  // Bootstrap wants us to add a class to the label as well.
  if ($element['#type'] == 'checkbox') {
    $attributes['class'] = 'checkbox';
  }

  // The leading whitespace helps visually separate fields from inline labels.
  if (!empty($variables['rendered_element'])) {
    return ' <label' . drupal_attributes($attributes) . '>' . $variables['rendered_element'] . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
  }
  else {
    return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
  }
}

function ubnext_checkboxes($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'][] = 'form-checkboxes form-control';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

function ubnext_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea form-control'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
  }

  if (!empty($element['#description'])) {

  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

function ubnext_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $element['#attributes']['class'][] = 'form-control';

  if (!empty($element['#description'])) {

  }

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = "<div class='input-wrapper'>";
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';
  $output .= "</div>";
  return $output . $extra;
}


function ubnext_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  $element['#attributes']['class'][] = 'btn btn-primary';
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  $value = $element['#attributes']["value"];
  if( isset($element['#attributes']["button-type"]) && $element['#attributes']["button-type"] == "search" ) {
    $value = $element['#attributes']["icon"];
    unset($element['#attributes']["icon"]);
  }
  return '<button' . drupal_attributes($element['#attributes']) . '>' . $value . '</button>';
}


function ubnext_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select', 'form-control'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}


/**
 *
 */
function ubnext_preprocess_html(&$vars) {
  global $is_https;
  drupal_add_css(($is_https ? 'https' : 'http') . '://fonts.googleapis.com/css?family=Open+Sans:400,400i,700', array('type' => 'external'));
  drupal_add_js(($is_https ? 'https' : 'http') . '://f1-eu.readspeaker.com/script/9467/ReadSpeaker.js?pids=embhl', array(
  'type' => 'external',
  'scope' => 'footer',
  'weight' => 100,));
  // If the Guide feature is enabled, add chapter-1 class to body if the first
  // chapter on a guide is active.
  if (module_exists('ubn_guide')) {
    $page = page_manager_get_current_page();

    if (!empty($page['task']['name']) && $page['task']['name'] === 'node_view') {
      $node = entity_metadata_wrapper('node', reset($page['contexts'])->data);

      if ($node->getBundle() === 'guide') {
        $vars['classes_array'][] = 'chapter-1';
      }
      elseif ($node->getBundle() === 'guide_chapter') {
        $root = ubn_guide_get_root($node);
        $children = array_keys(ubn_guide_get_children($root->getIdentifier(), 1));

        $index = array_search($node->getIdentifier(), $children);

        if ($index === 0) {
          $vars['classes_array'][] = 'chapter-1';
        }
      }
    }
  }

  $vars['classes_array'][] = 'new-class';
}

function ubnext_language_switch_links_alter(array &$links, $type, $path) {
  global $language;
  $links['en']['title'] = t('In ') . $links['en']['title'];
  $links['sv']['title'] = t('På ') . strtolower($links['sv']['title']);

}

/**
 * make the langswitcher availible in template
 * and remove stuff not wanted
 */

function block_render($module, $block_id) {
  $block = block_load($module, $block_id);
  $block_content = _block_render_blocks(array($block));
  $build = _block_get_renderable_array($block_content);
  $build['locale_language']['#block']->subject = null;
  $build['locale_language']['#contextual_links'] = null;
  $block_rendered = drupal_render($build);
  return $block_rendered;
}

/**
 * Change the CSS @import rules to <link> tags.
 */
function ubnext_pre_render_styles($elements) {
  if (isset($elements['#group_callback'])) {
    $elements['#groups'] = $elements['#group_callback']($elements['#items']);
    unset($elements['#group_callback']);
  }
  if (isset($elements['#aggregate_callback'])) {
    $elements['#aggregate_callback']($elements['#groups']);
    unset($elements['#aggregate_callback']);
  }

  foreach ($elements['#groups'] as &$group) {
    if ($group['type'] == 'file' && isset($group['preprocess'])) {
      foreach ($group['items'] as $index => $item) {
        if (!file_exists($item['data'])) {
          unset($group['items'][$index]);
        }
      }

      $group['preprocess'] = FALSE;
    }
  }

  return $elements;
}




/**
 * Implements hook_html_head_alter().
 */
function ubnext_html_head_alter(&$head_elements) {
}


function ubnext_theme() {
  $items = array();
  $items['bootstrap_search_api_page_search_form'] = array(
    'render element' => 'element',
  );
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'ubnext') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'ubnext_preprocess_user_login'
    ),
  );
  $items['user_register_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'ubnext') . '/templates',
    'template' => 'user-register-form',
    'preprocess functions' => array(
      'ubnext_preprocess_user_register_form'
    ),
  );
  $items['user_pass'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'ubnext') . '/templates',
    'template' => 'user-pass',
    'preprocess functions' => array(
      'ubnext_preprocess_user_pass'
    ),
  );
  return $items;
}

function ubnext_user_login_block($form) {

  $output = drupal_render($form);

  return $output;

}

function ubnext_preprocess_user_login(&$vars) {

  $vars['form']['name']['#attributes']['class'][] = 'form-control';
  $vars['form']['pass']['#attributes']['class'][] = 'form-control';
  $vars['form']['actions']['submit']['#attributes']['class'][] = 'btn btn-primary';
  $vars['intro_text'] = t('Please login.');

}

function ubnext_preprocess_user_register_form(&$vars) {
  $vars['intro_text'] = t('This is my super awesome reg form');
}

function ubnext_preprocess_user_pass(&$vars) {

  $vars['form']['name']['#attributes']['class'][] = 'form-control';
  $vars['form']['actions']['submit']['#attributes']['class'][] = 'btn btn-primary';
  $vars['intro_text'] = t('Please login.');
}

/**
 * Implements hook_css_alter().
 */
function ubnext_css_alter(&$css) {
  // Remove some stylesheets.
  unset(
    $css['misc/vertical-tabs.css'],
    //$css['misc/ui/jquery.ui.theme.css'],
    $css['modules/block/block.css'],
    $css['modules/locale/locale.css'],
    $css['modules/book/book.css'],
    $css['modules/comment/comment.css'],
    $css['modules/dblog/dblog.css'],
    $css['modules/field/theme/field.css'],
    $css['modules/file/file.css'],
    $css['modules/filter/filter.css'],
    $css['modules/forum/forum.css'],
    $css['modules/help/help.css'],
    $css['modules/menu/menu.css'],
    $css['modules/node/node.css'],
    $css['modules/openid/openid.css'],
    $css['modules/poll/poll.css'],
    $css['modules/profile/profile.css'],
    $css['modules/search/search.css'],
    $css['modules/statistics/statistics.css'],
    $css['modules/syslog/syslog.css'],
    $css['modules/system/admin.css'],
    $css['modules/system/maintenance.css'],
    $css['modules/system/system.css'],
    $css['modules/system/system.admin.css'],
    $css['modules/system/system.base.css'],
    $css['modules/system/system.maintenance.css'],
    $css['modules/system/system.menus.css'],
    $css['modules/system/system.messages.css'],
    $css['modules/system/system.theme.css'],
    $css['modules/taxonomy/taxonomy.css'],
    $css['modules/tracker/tracker.css'],
    $css['modules/update/update.css'],
    $css['modules/user/user.css'],
    $css[drupal_get_path('module', 'admin_menu') . '/admin_menu.uid1.css'],
    $css[drupal_get_path('module', 'ctools') . '/css/ctools.css'],
    $css[drupal_get_path('module', 'diff') . '/css/diff.default.css'],
    $css[drupal_get_path('module', 'panels') . '/css/panels.css'],
    $css[drupal_get_path('module', 'views') . '/css/views.css']
  );

  // Load the Contextual CSS last, whether overridden or not.
  if (isset($css['modules/contextual/contextual.css'])) {
    $css['modules/contextual/contextual.css']['group'] = CSS_THEME;
    $css['modules/contextual/contextual.css']['weight'] = 100;
  }
}

function ubnext_bootstrap_search_api_page_search_form($variables) {
  $element = $variables['element'];
  $suffix = '_' . $element['id']['#value'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }

  $search_submit = drupal_render($element['submit' . $suffix]);
  $search_input = drupal_render($element['keys' . $suffix]);
  foreach(element_children($element, TRUE) as $key) {
    $element['#children'] .= drupal_render($element[$key]);
  }
  // Anonymous DIV to satisfy XHTML compliance.

  // Get path to empty search
  $searches = search_api_current_search();
  $search = reset($searches);
  $searchQuery = $search[0];
  $pages = search_api_page_load_multiple(false, array('index_id' => $searchQuery->getIndex()->machine_name));
  $page = reset($pages);
  $path = $page->path;

  // figure out later..
  //print t("Showing !count of !max databases:", array('!count' => 10, '!max' => $variables['total-items-in-index']));

  $id = $element['id']['#value'];
  $database_url = url($element['base_' . $id]['#value']);

  global $base_url;
  return '<form' . drupal_attributes($element['#attributes']) . '><div>'
    . $element['#children'] .
    '<div class="input-group">' . $search_input . "<a href='" . $database_url . "'class='clear-search-btn' title='" . t("Clear search and reset filters") ."'><i class='fa  fa-times-circle'></i></a>" .
      '<span class="input-group-btn"><div>' . $search_submit . '</div></span>' .
    '</div></form>';
}

function ubnext_bootstrap_form_element_pre_render($elements) {
  //TODO: instead we should search for 'form_element' and remove that
  //array_search
  unset($elements['#theme_wrappers']);
  return $elements;
}

function ubnext_form_search_api_page_search_form_site_alter(&$form, &$form_state, $form_id) {
  _ubnext_search_form_alter($form, $form_state, $form_id);
}

function ubnext_form_search_api_page_search_form_databases_alter(&$form, &$form_state, $form_id) {
  _ubnext_search_form_alter($form, $form_state, $form_id);
}


function _ubnext_search_form_alter(&$form, &$form_state, $form_id) {
  // Add bootstrap classes
  $suffix = '_' . $form['id']['#value'];
  $form['keys' . $suffix]['#attributes']['placeholder'] = t('Title, subject, supplier...');
  $form['keys' . $suffix]['#attributes']['class'][] = 'form-control';
  $form['keys' . $suffix]['#attributes']['class'][] = 'input-lg';

  if(!isset($form['submit' . $suffix]['#attributes'])) {
    $form['submit' . $suffix]['#attributes'] = array();
  }
  if(!isset($form['submit' . $suffix]['#attributes']['class'])) {
    $form['submit' . $suffix]['#attributes']['class'] = array();
  }
  if(!isset($form['submit' . $suffix]['#attributes']['style'])) {
    $form['submit' . $suffix]['#attributes']['style'] = array();
  }

  // http://drupal.stackexchange.com/questions/13796/generating-button-type-submit-with-the-form-api
  $form['submit' . $suffix]['#attributes']['class'][] = 'btn';
  $form['submit' . $suffix]['#attributes']['class'][] = 'btn-primary';
  //$form['submit' . $suffix]['#attributes']['class'][] = 'btn-lg';
  $form['submit' . $suffix]['#attributes']['class'][] = 'submit-btn';
  $form['submit' . $suffix]['#value'] = t('Search');  //decode_entities('&#xf002;');

//  $form['submit' . $suffix]["#prefix"] = '<button type="submit" title="' . t("Click here to search for database") . '" class="submit-btn btn btn-lg btn-primary" id="submit-' . $form['id']['#value'] . '"><i class="fa fa-search">';
  //$form['submit' . $suffix]["#suffix"] = '</i></button>';

  if(!isset($form['keys' . $suffix]['#pre_render'])) {
    $form['keys' . $suffix]['#pre_render'] = array();
  }

  // get query and put it as default_value if it exist
  $searches = search_api_current_search();
  $search = reset($searches);
  $query = $search[0]->getOriginalKeys();

  $form['keys' . $suffix]['#default_value'] = $query;

  $form['keys' . $suffix]['#pre_render'][] = 'ubnext_bootstrap_form_element_pre_render';

  $form['#theme_wrappers'] = array();
  $form['#theme'] = array('bootstrap_search_api_page_search_form');
}


/** Facet-API **/

/**
 * Theme functions for the Facet API module.
 */

/**
 * Returns HTML for an inactive facet item.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', 'options', and
 *   'count'. See the l() and theme_facetapi_count() functions for information
 *   about these variables.
 *
 * @ingroup themeable
 */
function ubnext_facetapi_link_inactive($variables) {
  // Builds accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => FALSE,
  );
  $accessible_markup = theme('facetapi_accessible_markup', $accessible_vars);

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);

  $variables['text'] = ($sanitize) ? check_plain($variables['text']) : $variables['text'];
  // Resets link text, sets to options to HTML since we already sanitized the
  // link text and are providing additional markup for accessibility.
  $variables['text'] .= $accessible_markup;
  $variables['options']['html'] = TRUE;

  if(!$variables['hide_inactive_items']) {
    $widget = $variables['operator'] === FACETAPI_OPERATOR_OR && !$variables['limit_active_items'] ?
      '<span class="fa fa-plus"></span>' :
      '';
    $variables['text'] = $widget . $variables['text'];
  }

  $output = theme_link($variables);

  // Adds count to link if one was passed.
  if (isset($variables['count'])) {
    $output .= theme('facetapi_count', $variables);
  }

  return $output;
}

/**
 * Returns HTML for the active facet item's count.
 *
 * @param $variables
 *   An associative array containing:
 *   - count: The item's facet count.
 *
 * @ingroup themeable
 */
function ubnext_facetapi_count($variables) {
  return '<span class="ubn-facet-items-item-count">(' . (int) $variables['count'] . ')</span>';
}

/**
 * Returns HTML for an active facet item.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', and 'options'. See
 *   the l() function for information about these variables.
 *
 * @see l()
 *
 * @ingroup themeable
 */
function ubnext_facetapi_link_active($variables) {

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );

  $widget = $variables['operator'] === FACETAPI_OPERATOR_OR && !$variables['limit_active_items'] ?
    '<span class="fa fa-minus"></span>' :
    '';

  $variables['text'] = $widget . theme('facetapi_accessible_markup', $accessible_vars) . $link_text;
  $variables['options']['html'] = TRUE;

  return theme_link($variables) ;
}

/**
 * Returns HTML for the deactivation widget.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', and 'options'. See
 *   the l() function for information about these variables.
 *
 * @see l()
 * @see theme_facetapi_link_active()
 *
 * @ingroup themable
 */
//NOT CURRENTLY USED
function ubnext_facetapi_deactivate_widget($variables) {
  return '<span class="fa fa-check-square-o"></span>';
}

/**
 * Prefix function with "_" to exclude from normal hook detection
 * We add this in ubnext_theme_registry_alter instead
 * (Because we need it to run before
 * template_preprocess_search_api_page_results)
 *
 * Attach "search result items" (with snippets etc) to search result entities
 */
//TODO: entity api entity metadata shit alter and add ubn_search_result_item
//property??
function _ubnext_preprocess_search_api_page_results(array &$variables) {
  $ubn_database_settings = array(
    'basePath' => url($variables['page']->path),
  );
  drupal_add_js(array('ubn_databases' => $ubn_database_settings), 'setting');
  drupal_add_js(drupal_get_path("theme", "ubnext") . "/js/database-search.js",
  array(
    'scope' => 'footer',
    'group' => JS_THEME,
    'weight' => 5,
  ));

  $variables['total-items-in-index'] = $variables['index']->datasource()->getIndexStatus($variables['index'])['indexed'];
  if(!empty($variables['results']['results'])) {
    $variables['items'] = $variables['index']->loadItems(array_keys($variables['results']['results']));
    // Overlay item entities with "result item" data (so we can access it in
    // slate view mode templates)
    foreach($variables['results']['results'] as $id => $item) {
      if(isset($variables['items'][$id])) {
        $variables['items'][$id]->ubn_search_result_item = $item;
      }
    }
  }
  if(
    $variables['page']->options['get_per_page'] &&
    !isset($_GET['per_page']) &&
    isset($variables['results']['result count']) &&
    $variables['results']['result count'] > $variables['page']->options['per_page']
  ) {
    $params = drupal_get_query_parameters($_GET, array('q', 'page'));
    $path = current_path();
    $params['per_page'] = 2000;
    $variables['show_all_link'] = theme(
      'link',
      array(
        'text' => t('Show all'),
        'path' => $path,
        'options' => array(
          'html' => TRUE,
          'query' => $params,
          'attributes' => array(
            'class'=> array(
              'ubn-search-results-show-all',
              'btn',
              'btn-primary',
              'btn-block',
            ),
          ),
        ),
      )
    );
  }
}

function ubnext_theme_registry_alter(&$theme_registry) {
  array_unshift(
    $theme_registry['search_api_page_results']['preprocess functions'],
    '_ubnext_preprocess_search_api_page_results'
  );
}

/**
 * Theme a list of sort options.
 *
 * @param array $variables
 *   An associative array containing:
 *   - items: The sort options
 *   - options: Various options to pass
 */
function ubnext_search_api_sorts_list(array $variables) {
  $items = array_map('render', $variables['items']);
  $options = $variables['options'];
  $options['attributes']['class'] = array('ubn-search-sorts', 'list-unstyled', 'list-inline');
  return !empty($items) ? theme('item_list', array('items' => $items) + $options) : '';
}

/**
 * Theme a single sort item.
 *
 * @param array $variables
 *   An associative array containing:
 *   - name: The name to display for the item.
 *   - path: The destination path when the sort link is clicked.
 *   - options: An array of options to pass to l().
 *   - active: A boolean telling whether this sort filter is active or not.
 *   - order_options: If active, a set of options to reverse the order
 * @return string
 */
function ubnext_search_api_sorts_sort($variables) {

  $name = $variables['name'];
  $path = $variables['path'];
  $options = $variables['options'] + array('attributes' => array());
  $options['attributes'] += array('class' => array());
  $options['html'] = (bool) $variables['active'];

  $order_options = $variables['order_options'] + array('query' => array(), 'attributes' => array(), 'html' => TRUE);
  $order_options['attributes'] += array('class' => array());
  if ($variables['active']) {
    //TODO: Should not use t for variable strings!
    // as modules original theme implementation does
    $fa_class = array(
      'asc' => 'fa-sort-desc',
      'desc' => 'fa-sort-asc',
    );
    $fa_icon = '<i class="fa ' . $fa_class[$order_options['query']['order']] . '" aria-hidden="true"></i>';
    $output = theme(
      'link',
      array(
        'text' => $name .' ' . $fa_icon,
        'path' => $path,
        'options' => $order_options,
      )
    );
  }
  else {
    $output = theme('link', array('text' => $name, 'path' => $path, 'options' => $options));
  }
  return $output;
}

