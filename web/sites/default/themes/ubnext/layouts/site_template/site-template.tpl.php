<?php global $language; ?>
<?php parse_url($current_path = $GLOBALS['base_url'] . "/" . $language->language . "/" . current_path()); ?>

<?php 
  $readspeaker_lang = 'sv_se';
  if ($language->language == 'en') {
    $readspeaker_lang = 'en_gb';
  }
 ?>
<div id="spinner">
  <i class="fa fa-circle-o-notch fa-spin"></i>
</div>
<?php if (!empty($content['topbar'])): ?>
  <div class="topbar clearfix">
    <?php print render($content['topbar']); ?>
  </div>
<?php endif; ?>

<!-- ### HEADER ### -->
<div class="header-cms">
  <header>
    <div class="container">
      <div class="row">
        <div class="col-md-7 col-xs-12">
          <div class="siteNav-logo <?php echo $language->language; ?>">
            <div class="logo">
              <a href="<?php echo $GLOBALS['base_url']; ?>"><div class="logo-image"></div></a>
            </div>
          </div>
          <div class="site-headers">
            <div class="site-title">
              <a href="<?php echo $GLOBALS['base_url']; ?>"><?php print variable_get('site_name'); ?></a>
            </div>
          </div>
        </div>
        <div class="col-md-5">
          <nav class="toplinks">
            <div class="rs_skip rsbtn rs_preserve rs_portal"><a class="rsbtn_play" accesskey="L" rel="nofollow" title="<?php t('Listen to the page content') ?>" href="https://app-eu.readspeaker.com/cgi-bin/rsent?customerid=9467&amp;lang=<?php echo $readspeaker_lang ?>&amp;readclass=main-cms&amp;url=<?php echo $current_path ?>" data-rsevent-id="rs_599740" role="button"><?php print t('Listen') ?></a></div>
            <div class="lang-area">              
              <?php print render($content['toplinks']); ?>
            </div>
          </nav>
        </div>
      </div>
    </div>
  </header>
  </div>

<!-- ### END HEADER ### -->

<div class="nav-cms shortcut-nav-cms">
  <div class="container">
    <div class="row">
      <div class="col-xs-12">
        <?php print render($content['shortcuts']); ?>
      </div>
    </div>
  </div>
</div>


<!-- ### MAIN NAVIGATION ### -->
<div class="nav-cms primary-nav-cms">
  <div class="container">
    <div class="row border-mobile">
      <div class="col-xs-12">
        <nav class="nav-primary">
          <!-- PRIMARY NAV -->
          <?php print render($content['navigation']); ?>
          <!-- END PRIMARY NAV -->
        </nav>
      </div>
    </div>
  </div>
</div>

<div class="nav-cms primary-nav-cms-dropdown">
    <nav class="nav-primary-dropdown">
      <!-- PRIMARY NAV -->
      <?php print render($content['dropdown_navigation']); ?>
      <!-- END PRIMARY NAV -->
    </nav>
</div>

<?php if (!empty($content['warning_message'])): ?>
    <div class="container-full">
        <?php print render($content['warning_message']); ?>
    </div>
<?php endif; ?>


<?php if(!empty($content['breadcrumb'])): ?>
<div class="nav-cms breadcrumb-nav-cms">
 <div class="container">
    <div class="row">
      <div class="col-xs-12">
        <nav class="nav-breadcrumb">
          <!-- SECONDARY NAV -->
          <?php print render($content['breadcrumb']); ?>
          <!-- END SECONDARY NAV -->
        </nav>
      </div>
    </div>
  </div>
</div>
<?php endif; ?>


<?php if(!empty($content['navigation_secondary'])): ?>
<div class="nav-cms secondary-nav-cms">
 <div class="container">
    <div class="row">
      <div class="col-xs-12">
        <nav class="nav-secondary">
          <!-- SECONDARY NAV -->
          <?php print render($content['navigation_secondary']); ?>
          <!-- END SECONDARY NAV -->
        </nav>
      </div>
    </div>
  </div>
</div>
<?php endif; ?>
<!-- ### END NAVIGATION ### -->

<?php if (!empty($content['tabs'])): ?>
  <div class="container">
    <div class="row">
      <div class="col-xs-12">
        <?php print render($content['tabs']); ?>
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if (!empty($content['messages'])): ?>
  <div class="container">
    <div class="message-box-cms" class="row">
      <div class="col-xs-12">
        <div class="alert alert-info" role="alert">
          <?php print render($content['messages']); ?>
        </div>
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if (!empty($content['pagetitle'])): ?>
  <div class="page-head">
    <?php print render($content['pagetitle']); ?>
  </div>
<?php endif; ?>

<?php if (!empty($content['content'])): ?>
  <div class="main-cms">
    <div class="wrap">
      <?php print render($content['content']); ?>
    </div>
  </div>
<?php endif; ?>

<div class="footer-cms rs_skip">
  <!-- ### FOOTER ### -->
  <div class="footer-area">
      <?php print render($content['footer']); ?>
  </div>
  <!-- ### END FOOTER ### -->
</div> <!-- ### END FOOTER-CMS -->


