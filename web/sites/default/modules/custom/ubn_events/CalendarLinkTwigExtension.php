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
   * @param DateTime $from
   *   Calendar entry start date and time.
   * @param DateTime $to
   *   Calendar entry end date and time.
   * @param bool $all_day
   *   Indicator for an "all day" calendar entry.
   * @param string $description
   *   Calendar entry description.
   * @param string $address
   *   Calendar entry address.
   *
   * @return string
   *   URL for the specific calendar type.
   */
  public function calendarLink($type, $title, $from, $to, $all_day = FALSE, $description = '', $address = '') {
    if (!isset(self::$types[$type])) {
      throw new Exception('Invalid calendar link type.');
    }

    // This should work, $from->value is unix timestamp
    $from = new \DateObject($from->value());
    $to = new \DateObject($to->value());

    try {
      $link = Link::create($title, $from, $to, $all_day);
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
   * @param DateTime $from
   *   Calendar entry start date and time.
   * @param DateTime $to
   *   Calendar entry end date and time.
   * @param bool $all_day
   *   Indicator for an "all day" calendar entry.
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
  public function calendarLinks($title, $from, $to, $all_day = FALSE, $description = '', $address = '') {
    $links = [];

    foreach (self::$types as $type => $name) {
      $links[$type] = [
        'type_key' => $type,
        'type_name' => $name,
        'url' => $this->calendarLink($type, $title, $from, $to, $all_day, $description, $address),
      ];
    }

    return $links;
  }

}
