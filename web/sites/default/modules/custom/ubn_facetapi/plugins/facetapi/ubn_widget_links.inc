<?php

/**
 * @file
 * The ubn_facetapi_links widget plugin class.
 */

class UBNFacetapiWidgetLinks extends FacetapiWidgetLinks {

  public function UBNFacetapiActiveBuildItems($build) {
    //TODO: cache?
    $active_items = array();
    foreach($build as $item) {
      if($item['#active']) {
        $active_items[] = $item;
      }
      if(isset($item['#item_children'])) {
        $active_items = array_merge($active_items, $this->UBNFacetapiActiveBuildItems($item['#item_children']));
      }
    }
    return $active_items;
  }

  /**
   * Implements FacetapiWidget::execute().
   *
   * Transforms the render array into something that can be themed by
   * theme_item_list().
   *
   * @see FacetapiWidgetLinks::setThemeHooks()
   * @see FacetapiWidgetLinks::buildListItems()
   */
  public function execute() {
    $element = &$this->build[$this->facet['field alias']];
    // Sets each item's theme hook, builds item list.
    $global_settings = $this->facet->getSettings()->settings;

    $settings = $this->settings->settings;
    //$active_items = $this->facet->getAdapter()->getActiveItems($this->facet->getFacet());

    $facet_title = '';
    $facet_items = array();
    $active_items = $this->UBNFacetapiActiveBuildItems($element);
    if(
      isset($settings['hide_inactive_items']) &&
      $settings['hide_inactive_items'] &&
      $active_items
    ) {
      $active_item = current($active_items);
      //Query?
      $variables = array(
        'path' => $active_item['#path'],
        //'container_attributes' => array('class' => 'ubn-facetapi-active-header-item'),
        //Link options? rename?
        'options' => array(
          'attributes' => array('class' => 'ubn-facetapi-active-header-item-link', 'rel' => 'nofollow', 'title' => t('Close filter')), //id?
          'html' => $active_item['#html'],
          'query' => $active_item['#query'],
        ),
      );
      $facet_title = $active_item['#markup'];
      $facet_handle = theme('ubn_facetapi_active_header_item_handle', $variables);
    }
    else {
      if(
        $global_settings['operator'] === FACETAPI_OPERATOR_OR &&
        $active_items
      ) {
        $active_items_titles = array();
        foreach($active_items as $i => $item) {
          //TODO: preg_split instead of explode
          //TODO: could probably do this in one preg_replace as well?
          //Capitalize backreference?
          /*
          if($i) {
            // For non-first items, chech if first word is all caps,
            // if not make it lower-case
            $words = explode(' ', $item['#markup']);
            if($words[0] !== drupal_strtoupper($words[0])) {
              $item['#markup'] = drupal_strtolower($item['#markup']);
            }
          }
          */
          /*
          if(strpos($item['#markup'], ',') !== FALSE) {
            $item['#markup'] = '"' . $item['#markup'] . '"';
          }
          */
          $active_items_titles[] = $item['#markup'];
        }
        $facet_title = htmlspecialchars(implode(' + ', $active_items_titles));
      }
      else {
        $facet_title = $this->build['#title'];
      }
      //TODO: theme function
      $facet_handle = theme('ubn_facetapi_widget_links_handle');
      $this->setThemeHooks($element);
      $facet_items = $this->buildListItems($element);
    }
    if ($active_items) {
      $this->build['#attributes']['class'][] = 'ubn-facet-active-items';
    }
    $this->build['#attributes']['class'][] = 'ubn-facet';
    $this->build['#attributes']['class'][] = 'ubn-facet-' . $global_settings['operator'];
    $this->build['#attributes']['class'][] = 'ubn-facet-links';
    $element = array(
      '#theme' => 'ubn_facetapi_facet', //UBN widget links item list
      '#items' => $facet_items,
      '#attributes' => $this->build['#attributes'],
      //TODO: class with field/facet name/key/alias?
      '#title' => $facet_title,
      '#handle' => $facet_handle,
    );
  }

  /**
   * Recursive function that sets each item's theme hook.
   *
   * The indivual items will be rendered by different theme hooks depending on
   * whether or not they are active.
   *
   * @param array &$build
   *   A render array containing the facet items.
   *
   * @return FacetapiWidget
   *   An instance of this class.
   *
   * @see theme_facetapi_link_active()
   * @see theme_facetapi_link_inactive()
   */
  protected function setThemeHooks(array &$build) {
    foreach ($build as $value => &$item) {
      $item['#theme'] = ($item['#active']) ? 'facetapi_link_active' : 'facetapi_link_inactive';
      if (!empty($item['#item_children'])) {
        $this->setThemeHooks($item['#item_children']);
      }
    }
    return $this;
  }

  /**
   * Transforms the render array for use with theme_item_list().
   *
   * The recursion allows this function to act on the various levels of a
   * hierarchical data set.
   *
   * @param array $build
   *   The items in the facet's render array being transformed.
   *
   * @return array
   *   The "items" parameter for theme_item_list().
   */
  function buildListItems($build) {
    //$items = parent::buildListItems($build);
    //return $this->UBNFacetapiWidgetProcessListItems($items);

    $settings = $this->settings->settings;
    $global_settings = $this->facet->getSettings()->settings;

    $active_items = $this->facet->getAdapter()->getActiveItems($this->facet->getFacet());
    $hide_inactive_items = !empty($active_items) && isset($settings['hide_inactive_items']) && $settings['hide_inactive_items'];

    // Initializes links attributes, adds rel="nofollow" if configured.
    $attributes = ($settings['nofollow']) ? array('rel' => 'nofollow') : array();
    $attributes += array('class' => $this->getItemClasses());

    // Builds rows.
    $items = array();
    foreach ($build as $value => $item) {
      // Hide inactive items if setting is set and an active item exists
      if($hide_inactive_items && !$item['#active']) {
        continue;
      }

      $row = array('class' => array());

      // Allow adding classes via altering.
      if (isset($item['#class'])) {
        $attributes['class'] = array_merge($attributes['class'], $item['#class']);
      }
      // Initializes variables passed to theme hook.
      $variables = array(
        'text' => $item['#markup'],
        'path' => $item['#path'],
        'count' => $item['#count'],
        'options' => array(
          'attributes' => $attributes,
          'html' => $item['#html'],
          'query' => $item['#query'],
        ),
        'operator' => $global_settings['operator'],
        'hide_inactive_items' => $settings['hide_inactive_items'],
        'limit_active_items' => $global_settings['limit_active_items'],
      );

      // Adds the facetapi-zero-results class to items that have no results.
      if (!$item['#count']) {
        $variables['options']['attributes']['class'][] = 'facetapi-zero-results';
      }

      // Add an ID to identify this link.
      $variables['options']['attributes']['id'] = drupal_html_id('facetapi-link');

      // If the item has no children, it is a leaf.
      if (empty($item['#item_children'])) {
        $row['class'][] = 'leaf';
      }
      else {
        // If the item is active or the "show_expanded" setting is selected,
        // show this item as expanded so we see its children.
        if ($item['#active'] || !empty($settings['show_expanded'])) {
          $row['class'][] = 'expanded';
          $row['children'] = $this->buildListItems($item['#item_children']);
        }
        else {
          $row['class'][] = 'collapsed';
        }
      }

      // Gets theme hook, adds last minute classes.
      $class = ($item['#active']) ? 'facetapi-active' : 'facetapi-inactive';
      $variables['options']['attributes']['class'][] = $class;

      // Themes the link, adds row to items.
      $row['data'] = theme($item['#theme'], $variables);
      $items[] = $row;
    }
    return $items;
  }

  protected function UBNFacetapiWidgetProcessListItems($items) {
    foreach($items as &$item) {
      $item['data'] = '<span class="fa fa-square-o"></span>' . $item['data'];
      if(isset($item['children'])) {
        $item['children'] = $this->UBNFacetapiWidgetProcessListItems($item['children']);
      }
    }
    return $items;
  }

  /**
   * Gets the base class array for a facet item.
   *
   * Classes that extend FacetapiWidgetLinks will often overide this method to
   * alter the link displays via CSS without having to touch the render array.
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
    parent::settingsForm($form, $form_state);
    $form['widget']['widget_settings']['ubn_facetapi_widget_links'][$this->id]['hide_inactive_items'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide inactive items'),
      '#default_value' => $this->settings->settings['hide_inactive_items'],
      '#description' => t('Hide all inactive items once one item is active.'),
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
    return parent::getDefaultSettings() + array(
      'hide_inactive_items' => FALSE,
    );
  }

}
