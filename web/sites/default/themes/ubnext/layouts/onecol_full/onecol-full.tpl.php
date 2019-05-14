<div class="main">

  <?php if (!empty ($content['messages'])) : ?>
    <div class="container">
      <div class="row">
        <div class="col-xs-12">
          <?php print render($content['messages']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>


  <?php if (!empty ($content['header'])) : ?>
    <div class="container">
      <div class="row">
        <div class="col-sm-10 col-md-8 col-lg-6  col-lg-offset-3 col-sm-offset-2 col-md-offset-2">
          <?php print render($content['header']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['banner'])) : ?>
    <div class="container">
      <?php print render($content['banner']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['promoted_top'])) : ?>
    <div class="container fullwidth-on-xs">
      <?php print render($content['promoted_top']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['main_top'])) : ?>
    <div class="container">
      <?php print render($content['main_top']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['promoted'])) : ?>
    <div class="container fullwidth-on-xs">
      <?php print render($content['promoted']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['main'])) : ?>
    <div class="container">
      <?php print render($content['main']); ?>
    </div>
  <?php endif; ?>
</div>
