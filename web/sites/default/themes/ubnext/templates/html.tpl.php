<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */

global $base_url;

?><!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <!-- Google Tag Manager -->
  <script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
  new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
  j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
  'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
  })(window,document,'script','dataLayer','GTM-NR65TR');</script>
  <!-- End Google Tag Manager -->

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name = "format-detection" content = "telephone=no">

  <link rel="apple-touch-icon" sizes="57x57" href=<?php  print $base_url . "/" . path_to_theme(); ?>/css/img/apple-touch-icon-_57x57.png>
  <link rel="apple-touch-icon" sizes="114x114" href=<?php print $base_url . "/" . path_to_theme(); ?>/css//img/apple-touch-icon-_114x114.png>
  <link rel="apple-touch-icon" sizes="72x72" href=<?php print $base_url . "/" . path_to_theme(); ?>/css/img/apple-touch-icon-_72x72.png>    
  <link rel="apple-touch-icon" sizes="144x144" href=<?php print $base_url . "/" . path_to_theme(); ?>/css/img/apple-touch-icon-_144x144.png>
  <link rel="apple-touch-icon" sizes="60x60" href=<?php print $base_url . "/" . path_to_theme();?>/css/img/apple-touch-icon-_60x60.png>
  <link rel="apple-touch-icon" sizes="120x120" href=<?php print $base_url . "/" . path_to_theme(); ?>/css/img/apple-touch-icon-_120x120.png>
  <link rel="apple-touch-icon" sizes="76x76" href=<?php print $base_url . "/" . path_to_theme();?>/css/img/apple-touch-icon-_76x76.png>
  <link rel="apple-touch-icon" sizes="152x152" href=<?php print $base_url . "/" . path_to_theme();?>/css/img/apple-touch-icon-_152x152.png>
  <link rel="apple-touch-icon" sizes="180x180" href=<?php print $base_url . "/" . path_to_theme();?>/css/img/apple-touch-icon-_180x180.png>
  
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
    <!-- Google Tag Manager (noscript) -->
  <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-NR65TR" height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
  <!-- End Google Tag Manager (noscript) -->

  <div id="skip-link" class="sr-only rs_skip">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
