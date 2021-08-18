<?php
/**
 * @file
 * Contains SearchApiSolrAutocompleteServerSuggester.
 */

/**
 * Provides a suggester plugin that retrieves suggestions from the Solr
 * SuggesterComponent.
 *
 * The server needs to be a Solr 5.0+ server for this to work properly.
 */
class SearchApiSolrAutocompleteServerSuggester extends SearchApiAutocompleteServerSuggester {

  /**
   * {@inheritdoc}
   */
  public static function supportsIndex(SearchApiIndex $index) {
    static $supports_index = array();
    if(!isset($supports_index[$index->id])) {
      try {
        $server = $index->server();
        $service_info = search_api_get_service_info($server->class);
        $solr = $server->getSolrConnection();
        //TODO: check if suggesters have been enabled? where?
        //getSolrVersion() potentially rather expensive, advice user to set version manually?
        $supports_index[$index->id] =
          (
            $service_info['class'] === 'SearchApiSolrService' ||
            is_subclass_of($service_info['class'], 'SearchApiSolrService')
          ) &&
          $server->getSolrConnection()->getSolrVersion() >= 5;
      }
      catch (SearchApiException $e) {
        return FALSE;
      }
    }
    return $supports_index[$index->id];
  }

  /**
   * {@inheritdoc}
   */
  public function defaultConfiguration() {
    $index = $this->getSearch()->index();
    return parent::defaultConfiguration() + array(
      'solr_server' => array(
        'suggester_dictionaries' => '',
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function buildConfigurationForm(array $form, array &$form_state) {
    $form = parent::buildConfigurationForm($form, $form_state);
    $form['solr_server'] = array(
      '#type' => 'fieldset',
      '#title' => t('Solr server'),
      '#desciption' => t('Solr server suggester settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
    );
    $form['solr_server']['suggester_dictionaries'] = array(
      '#title' => t('Suggester dictionaries'),
      '#type' => 'textarea',
      '#description' => t('One dictionary per line, in order of precedence.'),
      '#default_value' => implode("\n", $this->configuration['solr_server']['suggester_dictionaries']),
    );
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  /*
  public function validateConfigurationForm(array $form, array &$form_state) {
    parent::validateConfigurationForm($form, $form_state);
  }
  */

  private function solrAutocompletParseDictionaries($value) {
    return array_map(
      'trim',
      explode(
        "\n",
        $value
      )
    );
  }

  /**
   * {@inheritdoc}
   */
  public function submitConfigurationForm(array $form, array &$form_state) {

    $form_state['values']['solr_server']['suggester_dictionaries'] =
      $this->solrAutocompletParseDictionaries($form_state['values']['solr_server']['suggester_dictionaries']);

    $server = $this->search->server();
    $service_class_info = search_api_get_service_info($server->class);
    $autocomplete_servlet = constant($service_class_info['class'] . '::AUTOCOMPLETE_SERVLET');
    $solr = $server->getSolrConnection();

    // First check if autocomplete servlet is enabled/configured
    // and warn if problems are detected
    try {
      $solr->makeServletRequest($autocomplete_servlet, array());
      // If autocomplete servlet is set up and seems to be
      // working probe each dictionary in turn
      foreach($form_state['values']['solr_server']['suggester_dictionaries'] as $dictionary) {
        try {
          $solr->makeServletRequest($autocomplete_servlet, array('suggest.dictionary' => $dictionary));
        }
        catch (Exception $e) {
          $message = t(
            'A problem occured requesting autocomplete suggester dictionary "@dictionary": @message.',
            array(
              '@dictionary' => $dictionary,
              '@message' => $e->getMessage(),
            )
          );
          drupal_set_message($message, 'warning');
        }
      }
    }
    catch (Exception $e) {
      $message = t(
        'A problem occured requesting autocomplete suggester servlet: @message',
        array(
          '@message' => $e->getMessage(),
        )
      );
      drupal_set_message($message, 'warning');
    }

    parent::submitConfigurationForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function getAutocompleteSuggestions(SearchApiQueryInterface $query, $incomplete_key, $user_input) {
    return $query
      ->getIndex()
      ->server()
      ->getSolrSuggestionCompomentAutocompleteSuggestions(
          $user_input,
          $this->configuration['solr_server']
        );
  }
}
