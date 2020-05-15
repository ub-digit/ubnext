<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<div class="row panel-separator">
  <div class="col-sm-10 col-md-8 col-lg-6 col-lg-offset-3 col-sm-offset-1 col-md-offset-2">
    <div class="divider"></div>
    <h2 class="story-header"><?php print $view->get_title(); ?></h2>
    <?php foreach ($rows as $id => $row): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    <?php
      $options = array();
      $options['attributes']['class'] =  'more-news-link';
    ?>

    <?php
      global $language ;
      $lang_name = $language->language; 
      if ($lang_name == "sv") {
        $url = '/nyheter';
      }
      else {
        $url = '/news';
      }
    ?>
    <div class="more-news-link pull-left"><?php print l(t("More news"), $url) ?> <i class="fa fa-arrow-right"></i></div>
  </div>
</div>
