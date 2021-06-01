<?php

class UBNFacetapiWidgetCheckbox extends FacetapiWidget {

  /**
   * Overrides FacetapiWidget::__construct().
   *
   * For links, it is better to use the machine name of the facet as opposed to
   * the alias for the key. Alias are usually, but not necessarily, unique. It
   * doesn't make sense to group links in the same element as they are usually
   * rendered in blocks with are separate from one another.
   */
  public function __construct($id, array $realm, FacetapiFacet $facet, stdClass $settings) {
    $config_name = _ubn_facetapi_i18n_string_name($settings->name);
    $settings->settings['checkbox_label'] =
      i18n_string(
        'facetapi:facet_setting:' . $config_name . ':checkbox_label',
        $settings->settings['checkbox_label']
      );
    parent::__construct($id, $realm, $facet, $settings);
    $this->key = $facet['name'];
  }

  /**
   * Implements FacetapiWidget::execute().
   */
  public function execute() {
    $build = &$this->build[$this->facet['field alias']];
    $settings = $this->settings->settings;
    // Initializes links attributes, adds rel="nofollow" if configured.
    $attributes = ($settings['nofollow']) ? array('rel' => 'nofollow') : array();
    $attributes += array('class' => $this->getItemClasses());

    //TODO: Perhaps a little more robustness/configurability:
    // for now assuming "1"
    if(!empty($build) && isset($build[1])) {
      $checkbox_item = $build[1];
      $facet_title = !empty($settings['checkbox_label']) ? $settings['checkbox_label'] : $checkbox_item['#markup'];
      $variables = array(
        'active' => $checkbox_item['#active'],
        'path' => $checkbox_item['#path'],
        'options' => array(
          'attributes' => array('class' => 'ubn-facetapi-checkbox-item-link', 'rel' => 'nofollow', 'title' => t('Show freely accessible')), //id?
          'html' => $checkbox_item['#html'],
          'query' => $checkbox_item['#query'],
        ),
      );
      $this->build['#attributes']['class'][] = 'ubn-facet';
      $this->build['#attributes']['class'][] = 'ubn-facet-checkbox';
      if ($checkbox_item['#active']) {
        $this->build['#attributes']['class'][] = 'ubn-facet-checkbox-checked';
      }
      $build = array(
        '#theme' => 'ubn_facetapi_facet',
        '#items' => array(),
        '#attributes' => $this->build['#attributes'],
        '#title' => $facet_title,
        '#handle' => theme('ubn_facetapi_widget_checkbox_handle', $variables),
      );
    }
    else {
      $build = array();
    }
  }

  /**
   * Gets the base class array for a facet item.
   *
   * @return array
   *   An array of classes.
   */
  function getItemClasses() {
    return array();
  }

  /**
   * Overrides FacetapiWidget::settingsForm().
   */
  function settingsForm(&$form, &$form_state) {
    // @see http://drupal.org/node/1370342
    $form['widget']['widget_settings']['links'][$this->id]['nofollow'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prevent crawlers from following facet links'),
      '#default_value' => !empty($this->settings->settings['nofollow']),
      '#description' => t('Add the <code>rel="nofollow"</code> attribute to facet links to maximize SEO by preventing crawlers from indexing duplicate content and getting stuck in loops.'),
      '#states' => array(
        'visible' => array(
          'select[name="widget"]' => array('value' => $this->id),
        ),
      ),
    );
    //TODO: i18n, how?
    //Default to field label? how?
    $form['widget']['widget_settings']['links'][$this->id]['checkbox_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Checkbox label'),
      '#default_value' => !empty($this->settings->settings['checkbox_label']) ?
        $this->settings->settings['checkbox_label'] : '',
      '#description' => t('The checkbox label.'),
      '#states' => array(
        'visible' => array(
          'select[name="widget"]' => array('value' => $this->id),
        ),
      ),
    );
  }

  /**
   * Overrides FacetapiWidget::getDefaultSettings().
   */
  function getDefaultSettings() {
    return array(
      'nofollow' => 1,
      'checkbox_label' => '',
    );
  }
}
