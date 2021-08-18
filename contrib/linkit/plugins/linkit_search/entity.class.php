<?php
/**
 * @file
 * Define Linkit entity search plugin class.
 */

/**
 * Represents a Linkit entity search plugin.
 */
class LinkitSearchPluginEntity extends LinkitSearchPlugin {

  /**
   * Entity field query instance.
   *
   * @var EntityFieldQuery Resource
   */
  var $query;

  /**
   * The entity info array of an entity type.
   *
   * @var array
   */
  var $entity_info = array();

  /**
   * The name of the property that contains the entity label.
   *
   * @var string
   */
  var $entity_field_label;

  /**
   * The name of the property of the bundle object that contains the name of
   * the bundle object.
   *
   * @var string
   */
  var $entity_key_bundle;

  /**
   * Plugin specific settings.
   *
   * @var array
   */
  var $conf = array();

  /**
   * Overrides LinkitSearchPlugin::__construct().
   *
   * Initialize this plugin with the plugin, profile, and entity specific
   * variables.
   *
   * @param array $plugin
   *   The plugin array.
   *
   * @param LinkitProfile object $profile
   *   The Linkit profile to use.
   */
  function __construct($plugin, LinkitProfile $profile) {
    parent::__construct($plugin, $profile);

    // Load the corresponding entity info.
    $this->entity_info = entity_get_info($this->plugin['entity_type']);

    // Set bundle key name.
    if (isset($this->entity_info['entity keys']['bundle']) &&
      !isset($this->entity_key_bundle)) {
      $this->entity_key_bundle = $this->entity_info['entity keys']['bundle'];
    }

    // Set the label field name.
    if (!isset($this->entity_field_label)) {
      // Check that the entity has a label in entity keys.
      // If not, Linkit don't know what to search for.
      if (!isset($this->entity_info['entity keys']['label'])) {
        // This is only used when building the plugin list.
        $this->unusable = TRUE;
      }
      else {
        $this->entity_field_label = $this->entity_info['entity keys']['label'];
      }
    }

    // Make a shortcut for the profile data settings for this plugin.
    $this->conf = isset($this->profile->data[$this->plugin['name']]) ?
            $this->profile->data[$this->plugin['name']] : array();
  }

  /**
   * Create a label of an entity.
   *
   * @param $entity
   *   The entity to get the label from.
   *
   * @return
   *   The entity label, or FALSE if not found.
   */
  function createLabel($entity) {
    return filter_xss(entity_label($this->plugin['entity_type'], $entity));
  }

   /**
   * Create a search row description.
   *
   * If there is a "result_description", run it through token_replace.
   *
   * @param object $data
   *   An entity object that will be used in the token_place function.
   *
   * @return
   *   A string containing the row description.
   *
   * @see token_replace()
   */
  function createDescription($data) {
    $description = token_replace(check_plain($this->conf['result_description']), array(
      $this->plugin['entity_type'] => $data,
    ), array('clear' => TRUE));
    return $description;
  }

  /**
   * Create an uri for an entity.
   *
   * @param $entity
   *   The entity to get the path from.
   *
   * @return
   *   A string containing the path of the entity, NULL if the entity has no
   *   uri of its own.
   */
  function createPath($entity) {
    // Create the URI for the entity.
    $uri = entity_uri($this->plugin['entity_type'], $entity);

    $options = array();
    // Handle multilingual sites.
    if (isset($entity->language) && $entity->language != LANGUAGE_NONE && drupal_multilingual() && language_negotiation_get_any(LOCALE_LANGUAGE_NEGOTIATION_URL)) {
      $languages = language_list('enabled');
      // Only use enabled languages.
      $languages = $languages[1];

      if ($languages && isset($languages[$entity->language])) {
        $options['language'] = $languages[$entity->language];
      }
    }
    // Process the uri with the insert plugin.
    $path = linkit_get_insert_plugin_processed_path($this->profile, $uri['path'], $options);
    return $path;
  }

  /**
   * Create a group text.
   *
   * @param $entity
   *   The entity object.
   *
   * @return
   *   When "group_by_bundle" is active, we need to add the bundle name to the
   *   group, else just return the entity label.
   */
  function createGroup($entity) {
    // Get the entity label.
    $group = $this->entity_info['label'];

    // If the entities by this entity should be grouped by bundle, get the
    // name and append it to the group.
    if (isset($this->conf['group_by_bundle']) && $this->conf['group_by_bundle']) {
      $bundles = $this->entity_info['bundles'];
      $bundle_name = $bundles[$entity->{$this->entity_key_bundle}]['label'];
      $group .= ' - ' . check_plain($bundle_name);
    }
    return $group;
  }

  /**
   * Create a row class to append to the search result row.
   *
   * @param $entity
   *   The entity object.
   *
   * @return
   *   A string to with classes.
   */
  function createRowClass($entity) {
    return '';
  }

  /**
   * Start a new EntityFieldQuery instance.
   */
  function getQueryInstance() {
    $this->query = new EntityFieldQuery();
    $this->query->entityCondition('entity_type', $this->plugin['entity_type']);

    // Add the default sort on the entity label.
    $this->query->propertyOrderBy($this->entity_field_label, 'ASC');
  }

  /**
   * Implements LinkitSearchPluginInterface::fetchResults().
   */
  public function fetchResults($search_string) {
    // Support for the Title module: check for the search string in the entity
    // property (no translation enabled via the Title module) OR in the
    // (translatable) field that replaces the label property.
    //
    // EFQ does not support OR conditions, so we just run 2 queries. We could
    // have done this with a query_alter hook as well, but then we would depend
    // on running on a SQL database, while we now restrict ourselves to pure
    // EFQ.
    return array_merge(
      $this->fetchResultsByPropertyOrLabel($search_string, FALSE),
      $this->fetchResultsByPropertyOrLabel($search_string, TRUE)
    );
  }

  /**
   * Returns a list of entities that either match by label or by its field
   * replacement.
   *
   * @param string $search_string
   *   The string to search for.
   * @param bool $checkByField
   *   TRUE if to check by the field that replaces the label property,
   *   FALSE if to check by the entity property for the label.
   *
   * @return array
   *   An array of matching entities.
   */
  protected function fetchResultsByPropertyOrLabel($search_string, $checkByField) {
    $matches = array();

    // Return no matches if we should check for the field but no field
    // replacement is done.
    if ($checkByField && empty($this->entity_info['field replacement'][$this->entity_field_label])) {
      return $matches;
    }

    // Bundle handling:
    // If the entity type does not support bundles we have another quick return
    // if:
    //   we should check for the field and no field replacement is done
    //   OR we should check for the property and field replacement is done.
    if (!isset($this->entity_key_bundle)) {
      if ($checkByField === !empty($this->entity_info['field replacement'][$this->entity_field_label])) {
        return $matches;
      }
    }
    else {
      // The entity type does support bundles:
      // Get the bundles to check: those indicated in the config or all.
      $bundleRestrictions = !empty($this->conf['bundles']) ? array_filter($this->conf['bundles']) : array();
      $bundleRestrictions = !empty($bundleRestrictions) ? $bundleRestrictions : $this->entity_info['bundles'];
      // if the function title_field_replacement_enabled() does not exist, the
      // title module is not enabled and np replacements are done at all.
      $title_module_enabled = function_exists('title_field_replacement_enabled');
      // Filter these bundles further based on $checkByField and whether labels
      // for this bundle are replaced or not.
      $bundles = array();
      foreach ($bundleRestrictions as $bundle) {
        $is_replaced = $title_module_enabled && title_field_replacement_enabled($this->plugin['entity_type'], $bundle, $this->entity_field_label);
        if ($is_replaced === $checkByField) {
          $bundles[] = $bundle;
        }
      }
      // Return if the set of bundles to restrict the results to is empty.
      if (empty($bundles)) {
        return $matches;
      }
    }

    $this->getQueryInstance();

    // Filter on bundle if bundles are enabled for this entity type and there
    // are bundles to exclude.
    if (!empty($bundles) && count($bundles) < count($this->entity_info['bundles'])) {
      $this->query->propertyCondition($this->entity_key_bundle, $bundles, 'IN');
    }

    // Add the search condition.
    $search_value = '%' . db_like($search_string) . '%';
    if ($checkByField) {
      // Search in the field that replaces the label.
      $field_name = $this->entity_info['field replacement'][$this->entity_field_label]['field']['field_name'];
      $this->query->fieldCondition($field_name, 'value', $search_value, 'LIKE');
    }
    else {
      // Look in the label property.
      $this->query->propertyCondition($this->entity_field_label, $search_value, 'LIKE');
    }

    // Add tags to denote that this is a query from Linkit.
    $this->query->addTag('linkit_entity_autocomplete')
      ->addTag('linkit_' . $this->plugin['entity_type'] . '_autocomplete');

    // Add access tag for the query.
    // There is also a runtime access check that uses entity_access().
    $this->query->addTag($this->plugin['entity_type'] . '_access');

    // Execute the query.
    $result = $this->query->execute();

    if (!isset($result[$this->plugin['entity_type']])) {
      return array();
    }

    $ids = array_keys($result[$this->plugin['entity_type']]);

    // Load all the entities with all the ids we got.
    $entities = entity_load($this->plugin['entity_type'], $ids);

    foreach ($entities AS $entity) {
      // Check the access against the defined entity access callback.
      if (entity_access('view', $this->plugin['entity_type'], $entity) === FALSE) {
        continue;
      }

      $matches[] = array(
        'title' => $this->createLabel($entity),
        'description' => $this->createDescription($entity),
        'path' => $this->createPath($entity),
        'group' => $this->createGroup($entity),
        'addClass' => $this->createRowClass($entity),
      );

    }
    return $matches;
  }

  /**
   * Overrides LinkitSearchPlugin::buildSettingsForm().
   */
  function buildSettingsForm() {
    $form[$this->plugin['name']] = array(
      '#type' => 'fieldset',
      '#title' => t('!type plugin settings', array('!type' => $this->ui_title())),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
      '#states' => array(
        'invisible' => array(
          'input[name="data[search_plugins][' . $this->plugin['name'] . '][enabled]"]' => array('checked' => FALSE),
        ),
      ),
    );
    // Get supported tokens for the entity type.
    $tokens = linkit_extract_tokens($this->plugin['entity_type']);

    // A short description within the search result for each row.
    $form[$this->plugin['name']]['result_description'] = array(
      '#title' => t('Result description'),
      '#type' => 'textfield',
      '#default_value' => isset($this->conf['result_description']) ? $this->conf['result_description'] : '',
      '#size' => 120,
      '#maxlength' => 255,
      '#description' => t('Available tokens: %tokens.', array('%tokens' => implode(', ', $tokens))),
    );

    // If the token module is installed, lets do some fancy stuff with the
    // token chooser.
    if (module_exists('token')) {
      // Unset the regular description if token module is enabled.
      unset($form[$this->plugin['name']]['result_description']['#description']);

      // Display the user documentation of placeholders.
      $form[$this->plugin['name']]['token_help'] = array(
        '#title' => t('Replacement patterns'),
        '#type' => 'markup',
      );
      $form[$this->plugin['name']]['token_help']['help'] = array(
        '#theme' => 'token_tree_link',
        '#token_types' => array($this->plugin['entity_type']),
      );
    }

    // If there are bundles, add some default settings features.
    if (count($this->entity_info['bundles']) > 1) {
      $bundles = array();
      // Extract the bundle data.
      foreach ($this->entity_info['bundles'] as $bundle_name => $bundle) {
        $bundles[$bundle_name] = $bundle['label'];
      }

      // Filter the possible bundles to use if the entity has bundles.
      $form[$this->plugin['name']]['bundles'] = array(
        '#title' => t('Type filter'),
        '#type' => 'checkboxes',
        '#options' => $bundles,
        '#default_value' => isset($this->conf['bundles']) ? $this->conf['bundles'] : array(),
        '#description' => t('If left blank, all types will appear in autocomplete results.'),
      );

      // Group the results with this bundle.
      $form[$this->plugin['name']]['group_by_bundle'] = array(
        '#title' => t('Group by bundle'),
        '#type' => 'checkbox',
        '#default_value' => isset($this->conf['group_by_bundle']) ? $this->conf['group_by_bundle'] : 0,
      );
    }
    return $form;
  }
}
