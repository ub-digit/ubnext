<?php
/**
 * @file
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('General: Search widget'),
  'description' => t('This is the search widget that will forward search to Summon'),
  'category' => 'UBNext',
  'required context' => new ctools_context_required(t('Link list'), 'entity:node'),
  'edit form' => 'ubn_general_search_widget_content_type_settings',
);


/**
 * Settings callback.
 */
function ubn_general_search_widget_content_type_settings($form, &$form_state) {
 /* $conf = $form_state['conf'];
  file_put_contents("/tmp/debug", "ubn_general_search_widget_content_type_settings"  . "\n", FILE_APPEND);
  $form['number_of_items'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of items'),
    '#description' => t('The number of items in Summon'),
    '#default_value' => !empty($conf['number_of_items']) ? $conf['number_of_items'] : '100000',
  );
  $form['slogan'] = array(
    '#type' => 'textarea',
    '#title' => t('Search slogan'),
    '#default_value' =>
      !empty($conf['slogan']) ?
        $conf['slogan'] :
        'Search among <strong class="hidden-xs"> @number </strong> books, articles, magazines and more...',
  );
  $form['placeholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
    '#description' => t('The number of items in Summon'),
    '#default_value' => !empty($conf['placeholder']) ? $conf['placeholder'] : 'Search for...',
  );
  $form['aria_label'] = array(
    '#type' => 'textfield',
    '#title' => t('ARIA label'),
    '#default_value' => !empty($conf['aria_label']) ? $conf['aria_label'] : 'Search terms',
  );

  $form['ubn_background_image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Background image'),
    '#description' => "Image should be as wide as possible and at least (best is exactly) 375px high. Use JPG format. Please optimize for web.",
    '#progress_indicator' => "bar",
    '#upload_location' => 'public://search-widget-2',
    '#default_value' => '', //variable_get('ubn_search_widget_fid', ''),
  );

  $form['dark_theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check to use light text (on a dark image)'),
    '#default_value' => !empty($conf['dark_theme']) ? $conf['dark_theme'] : TRUE,
  );*/
  return $form;
}

/**
 * Ctools edit form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function ubn_general_search_widget_content_type_settings_submit($form, &$form_state) {
  file_put_contents("/tmp/debug", "ubn_general_search_widget_content_type_settings_submit"  . "\n", FILE_APPEND);
  foreach (array('slogan', 'placeholder', 'aria_label', 'dark_theme') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
  $form_state['conf']['number_of_items'] = str_replace(' ', '', $form_state['values']['number_of_items']);
}

/**
 *
 *
 * Render callback.
 */
function ubn_general_search_widget_content_type_render($subtype, $conf, $panel_args, $context) {
  global $language;
  $number = '100000'; // default number
  if (!variable_get('number_of_items')) {
    $number = variable_get('number_of_items');
  }
  elseif ($record_count = variable_get('ubn_general_summon_record_count', FALSE)) {
    $number = $record_count;
  }

  $lang =  $language->language;
  if ($lang == 'en') {
    $url = "https://gothenburg.summon.serialssolutions.com/en/search/";
  }
  elseif ($lang == 'sv') {
    $url = "https://gothenburg.summon.serialssolutions.com/sv-SE/search/";
  }

  $link_list_rendered = '';
  if (!empty($context->data)) {
    $link_list = $context->data;
    $link_list_rendered = slate_render('search-widget-link-list', array('link_list' => $link_list));
  }


  $slogan = format_string(variable_get('slogan'), array('@number' => _ubn_slate_number_format($number)));
  $block = new stdClass();

  $file = NULL;
  if (variable_get('ubn_search_widget_fid')) {
    $file = file_load(variable_get('ubn_search_widget_fid'));
  }

  if ($file) {
    $file_uri = file_create_url($file->uri);
  }
  else {
    $file_uri = "";
  }

  $block->content = slate_render('search-widget',
    array(
      'url' => $url,
      'slogan' =>  $slogan,
      'placeholder' => variable_get('placeholder'),
      'aria_label' => variable_get('aria_label'),
      'file_url' => $file_uri,
      'link_list' => trim($link_list_rendered),
    )
  );
  drupal_add_js(drupal_get_path('module', 'ubn_general') . '/plugins/content_types/search_widget/search-widget.js');

  return $block;
}


