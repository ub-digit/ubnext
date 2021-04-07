<?php

/**
 * Fetches data via HTTP.
 */
class UBNOpeningHoursFeedsFetcher extends FeedsFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);

    //This could be a setting, or use sites timezone?
    $tz = new DateTimeZone('Europe/Stockholm');
    $now = new DateTime('now', $tz);

    $source_language = 'en';

    $query = array(
      'start_date' => $now->format('Y-m-d'),
      'days' => 7, //setting for this?
      'lang' => $source_language,
    );

    //TODO: use drupal_http_build_query instead to get rid of potential url
    // rewriting etc?
    $url = url($source_config['source'], array('query' => $query, 'external' => TRUE));

    $options = array();
    if(!empty($this->config['request_timeout'])) {
      $options['timeout'] = $this->config['request_timeout'];
    }

    $result = drupal_http_request($url, $options);

    //TODO: proper error handling?
    if(isset($result->error)) {
      throw new Exception($result->error);
    }
    else if($result->code != 200) {
      throw new Exception('Expected HTTP response code 200, got ' . $result->code);
    }

    // This is a kludge, but until fixed in api we need to generate unique id
    // for each opening hour item here
    $result_json = drupal_json_decode($result->data);
    if(!$result_json) {
      throw new Exception('Invalid json');
    }
    foreach($result_json['locations'] as &$location) {
      $location['lang'] = $source_language;
      foreach(array('swedish_name', 'english_name', 'name') as $key) {
        // Also fix encoding
        $location[$key] = html_entity_decode($location[$key], ENT_COMPAT | ENT_HTML401, 'UTF-8');
      }
      foreach($location['openhours'] as &$openhour) {
        $openhour['id'] = md5($location['id'] . $openhour['date']);
        $openhour['location_id'] = $location['id'];
      }
    }
    $raw = drupal_json_encode($result_json);
    $fetcher_result = new FeedsFetcherResult($raw);

    return $fetcher_result;
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'request_timeout' => NULL,
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    // Per importer override of global http request timeout setting.
    $form['request_timeout'] = array(
      '#type' => 'textfield',
      '#title' => t('Request timeout'),
      '#description' => t('Timeout in seconds to wait for an HTTP get request to finish. Default value is 30.'),
      '#default_value' => $this->config['request_timeout'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#maxlength' => 3,
      '#size'=> 30,
    );
    return $form;
  }

  /**
   * Expose source form.
   */
  public function sourceForm($source_config) {
    $form = parent::sourceForm($source_config);
    $form['source'] = array(
      '#type' => 'textfield',
      '#title' => t('Endpoint url'),
      '#default_value' => !empty($source_config['source']) ? $source_config['source'] : 'http://openhours.ub.gu.se/locations',
      '#maxlength' => NULL,
      '#required' => TRUE,
    );
    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {
    $values['source'] = trim($values['source']);

    // Keep a copy for error messages.
    $original_url = $values['source'];

    if (!feeds_valid_url($values['source'], TRUE)) {
      $form_key = 'feeds][' . get_class($this) . '][source';
      form_set_error($form_key, t('The URL %source is invalid.', array('%source' => $original_url)));
    }
  }

  /**
   * Implement FeedsFetcher::importPeriod().
   */
  /*
  public function importPeriod(FeedsSource $source) {
  }
  */

}
