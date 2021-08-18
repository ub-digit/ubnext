<?php
/**
 * Controller class for menu position rules.
 *
 */

class MenuPositionRuleController extends EntityAPIController {

  protected function attachLoad(&$menu_links, $revision_id = FALSE) {
    foreach ($menu_links as $mlid => &$item) {
    }
    parent::attachLoad($menu_links, $revision_id);
  }

  /**
   * Overrides delete from EntityAPIController
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    foreach ($ids as $rid) {
      menu_position_delete_rule($rid);
    }
    cache_clear_all('menu_position_enabled_rules', 'cache');
  }

  /**
   * Overrides save from EntityAPIController
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();
    $rule = (object) $entity;
    //TODO: correct?
    // Possible to add required to schema?
    // Use own entity api property metadata?
    $required_properties = array(
      'admin_title',
      //'menu_name' //TODO: set menu name from plid if missing
      'plid',
    );
    foreach($required_properties as $property) {
      if(empty($rule->{$property})) {
        throw new Exception(t('Required property @property missing', array('@property' => $property)));
      }
    }
    cache_clear_all('menu_position_enabled_rules', 'cache');
    return parent::save($rule, $transaction);
  }
}
