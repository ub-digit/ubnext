<?php
/**
 * @file
 */


/**
 * Class SlateModelPluginEntity.
 */
class SlateModelPluginEntity extends SlateModelPlugin {

  public function requiredContexts() {
    return array(new ctools_context_required($this->model['label'], 'entity:' . $this->plugin['entity_type']));
  }

  public function wrapper($data) {
    $entity = entity_metadata_wrapper($this->plugin['entity_type'], $data);

    return new SlateModelPluginEntityWrapper($entity);
  }

}

/**
 * Class SlateModelPluginEntityWrapper.
 */
class SlateModelPluginEntityWrapper extends EntityDrupalWrapper {

  /**
   *
   */
  public function __construct($data) {
    global $language_content;

    parent::__construct($data->type, $data->data, $data->info);

    $this->language($language_content->language);
  }

  /**
   *
   */
  public function _label() {
    $info = $this->info;

    $key = array('field', $info['name'], $info['parent']->getBundle(), 'label');
    return entity_i18n_string(implode($key, ':') , $info['label']);
  }

  /**
   *
   */
  public function _view($view_mode) {
    $build = entity_view($this->type(), array($this->value()), $view_mode);

    return render($build);
  }

  /**
   *
   */
  public function get($name) {
    $value = parent::get($name);

    if ($value instanceof EntityDrupalWrapper) {
      $value = new SlateModelPluginEntityWrapper($value);
    }
    else if ($value instanceof EntityStructureWrapper) {
      $value = new SlateModelPluginEntityWrapperStructure($value);
    }
    else if ($value instanceof EntityListWrapper) {
      $value = new SlateModelPluginEntityWrapperList($value);
    }
    else if ($value instanceof EntityValueWrapper) {
      $value = new SlateModelPluginEntityWrapperValue($value);
    }

    return $value;
  }

  /**
   *
   */
  public function __isset($name) {
    if (parent::__isset($name)) {
      $info = $this->get($name)->info();

      if (!empty($info['computed'])) {
        return TRUE;
      }

      $value = $this->get($name)->value();

      return isset($value);
    }

    return FALSE;
  }

}

/**
 * Class SlateModelPluginEntityWrapperStructure.
 */
class SlateModelPluginEntityWrapperStructure extends EntityStructureWrapper {

  /**
   *
   */
  public function __construct($data) {
    parent::__construct($data->type, $data->data, $data->info);
  }

  /**
   *
   */
  public function _label() {
    $info = $this->info;

    $key = array('field', $info['name'], $info['parent']->getBundle(), 'label');
    return entity_i18n_string(implode($key, ':') , $info['label']);
  }

  /**
   *
   */
  public function get($name) {
    $value = parent::get($name);

    if ($value instanceof EntityDrupalWrapper) {
      $value = new SlateModelPluginEntityWrapper($value);
    }
    else if ($value instanceof EntityStructureWrapper) {
      $value = new SlateModelPluginEntityWrapperStructure($value);
    }
    else if ($value instanceof EntityListWrapper) {
      $value = new SlateModelPluginEntityWrapperList($value);
    }
    else if ($value instanceof EntityValueWrapper) {
      $value = new SlateModelPluginEntityWrapperValue($value);
    }

    return $value;
  }

  /**
   *
   */
  public function __toString() {
    try {
      $value = $this->value();

      return is_string($value) ? $value : '';
    }
    catch (EntityMetadataWrapperException $e) {
      return '';
    }
  }


}

/**
 * Class SlateModelPluginEntityWrapperList.
 */
class SlateModelPluginEntityWrapperList extends EntityListWrapper {

  /**
   *
   */
  public function __construct($data) {
    parent::__construct($data->type, $data->data, $data->info);
  }

  /**
   *
   */
  public function _label() {
    $info = $this->info;

    $key = array('field', $info['name'], $info['parent']->getBundle(), 'label');
    return entity_i18n_string(implode($key, ':') , $info['label']);
  }

  /**
   *
   */
  public function get($name) {
    $value = parent::get($name);

    if ($value instanceof EntityDrupalWrapper) {
      $value = new SlateModelPluginEntityWrapper($value);
    }
    else if ($value instanceof EntityStructureWrapper) {
      $value = new SlateModelPluginEntityWrapperStructure($value);
    }
    else if ($value instanceof EntityListWrapper) {
      $value = new SlateModelPluginEntityWrapperList($value);
    }
    else if ($value instanceof EntityValueWrapper) {
      $value = new SlateModelPluginEntityWrapperValue($value);
    }

    return $value;
  }

}

/**
 * Class SlateModelPluginEntityWrapperValue.
 */
class SlateModelPluginEntityWrapperValue extends EntityValueWrapper {

  /**
   *
   */
  public function __construct($data) {
    parent::__construct($data->type, $data->data, $data->info);
  }

  /**
   *
   */
  public function _label() {
    $info = $this->info;

    $key = array('field', $info['name'], $info['parent']->getBundle(), 'label');
    return entity_i18n_string(implode($key, ':') , $info['label']);
  }

  /**
   *
   */
  public function __toString() {
    try {
      $value = $this->value();

      return is_string($value) ? $value : '';
    }
    catch (EntityMetadataWrapperException $e) {
      return '';
    }
  }

}
