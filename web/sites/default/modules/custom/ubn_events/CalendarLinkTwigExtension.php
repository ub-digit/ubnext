<?php

namespace Drupal\ubn_events\Twig;

use Spatie\CalendarLinks\Exceptions\InvalidLink;
use Spatie\CalendarLinks\Link;

/**
 * Class CalendarLinkTwigExtension.
 *
 * @package Drupal\calendar_link\Twig
 */
class CalendarLinkTwigExtension extends \Twig_Extension {

  /**
   * Available link types (generators).
   *
   * @var array
   *
   * @see \Spatie\CalendarLinks\Link
   */
  protected static $types = [
    'google' => 'Google',
    'ics' => 'iCal',
    'yahoo' => 'Yahoo!',
    'webOutlook' => 'Outlook.com',
  ];

  /**
   * {@inheritdoc}
   */
  public function getFunctions() {
    return [
      new \Twig_SimpleFunction('calendar_link', [$this, 'calendarLink']),
      new \Twig_SimpleFunction('calendar_links', [$this, 'calendarLinks']),
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return 'calendar_link';
  }

  /**
   * Create a calendar link.
   *
   * @param string $type
   *   Generator key to use for link building.
   * @param string $title
   *   Calendar entry title.
  * @param EntityWrapperStructure $field
   *   Calendar date field structure.
   * @param string $description
   *   Calendar entry description.
   * @param string $address
   *   Calendar entry address.
   *
   * @return string
   *   URL for the specific calendar type.
   */
  public function calendarLink($type, $title, $field, $description = '', $address = '') {
    if (!isset(self::$types[$type])) {
      throw new Exception('Invalid calendar link type.');
    }

    $raw = $field->raw();
    $from = new \DateObject($raw['value'], $raw['timezone_db']);
    $to = new \DateObject($raw['value'], $raw['timezone_db']);

    try {
      $link = Link::create($title, $from, $to, ubn_events_is_all_day($from, $to));
    }
    catch (InvalidLink $e) {
      throw new CalendarLinkException($this->t('Invalid calendar link data.'));
    }

    if ($description) {
      $link->description($description);
    }

    if ($address) {
      $link->address($address);
    }

    return $link->{$type}();
  }

  /**
   * Create links for all calendar types.
   *
   * @param string $title
   *   Calendar entry title.
   * @param EntityWrapperStructure $field
   *   Calendar date field structure.
   * @param string $description
   *   Calendar entry description.
   * @param string $address
   *   Calendar entry address.
   *
   * @return array
   *   - type_key: Machine key for the calendar type.
   *   - type_name: Human-readable name for the calendar type.
   *   - url: URL for the specific calendar type.
   */
  public function calendarLinks($title, $field, $description = '', $address = '') {
    $links = [];

    foreach (self::$types as $type => $name) {
      $links[$type] = [
        'type_key' => $type,
        'type_name' => $name,
        'url' => $this->calendarLink($type, $title, $field, $description, $address),
      ];
    }

    return $links;
  }

}
