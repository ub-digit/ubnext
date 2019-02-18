<?php if (!empty($content['search'])): ?>
  <div id="search">
      <?php print render($content['search']); ?>
  </div>
<?php endif ?>

<?php if (!empty($content['messages'])): ?>
    <div class="container panel-separator">
      <div class="row">
        <div class="col-xs-12">
          <?php print render($content['messages']); ?>
        </div>
      </div>
    </div>
<?php endif ?>

<?php if (!empty($content['services'])): ?>
  <div id="services" class="container panel-separator">
    <?php print render($content['services']); ?>
  </div>
<?php endif ?>

<div class="container">
  <?php if (!empty ($content['promoted'])) : ?>
    <?php print render($content['promoted']); ?>
  <?php endif; ?>
</div>

<?php if (!empty ($content['navigation'])) : ?>
  <div class="fullwidth bg-grey">
    <div class="container">
      <?php print render($content['navigation']); ?>
    </div>
  </div>
<?php endif; ?>

<?php if (!empty($content['news'])): ?>
  <div id="news" class="container panel-separator">
    <div class="row promoted-news">
        <?php print render($content['news']); ?>
    </div>
  </div>
<?php endif ?>


<?php if (!empty($content['main'])): ?>
  <div class="fullwidth bg-grey start-page-opening-hours-wrapper">
    <div id="main" class="container panel-separator">
      <div class="row">
        <div class="col-xs-12 col-sm-8 col-sm-offset-2">
          <?php print render($content['main']); ?>
        </div>
      </div>
    </div>
  </div>
<?php endif ?>
