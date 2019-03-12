<?php
/**
 * @file
 * ubn_styles.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ubn_styles_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "breakpoints" && $api == "default_breakpoint_group") {
    return array("version" => "1");
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return array("version" => "2");
  }
  if ($module == "scald" && $api == "context_config") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ubn_styles_image_default_styles() {
  $styles = array();

  // Exported image style: blurb_extra_small.
  $styles['blurb_extra_small'] = array(
    'label' => 'Blurb extra small',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 720,
          'height' => 450,
          'upscale' => 1,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'blurb_extra_small',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: content_admin.
  $styles['content_admin'] = array(
    'label' => 'Content admin',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 266,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: hero_small.
  $styles['hero_small'] = array(
    'label' => 'Hero small',
    'effects' => array(
      4 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1200,
          'height' => 340,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'hero_small',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: hero_small_extra_small.
  $styles['hero_small_extra_small'] = array(
    'label' => 'Hero extra small',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 750,
          'height' => 500,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'hero_small_extra_small',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: page_content.
  $styles['page_content'] = array(
    'label' => 'Page content',
    'effects' => array(
      5 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1200,
          'height' => 576,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'page_content',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: page_content_extra_small.
  $styles['page_content_extra_small'] = array(
    'label' => 'Page content extra small',
    'effects' => array(
      10 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 750,
          'height' => 422,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'page_content_extra_small',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: page_content_inline_extra_small.
  $styles['page_content_inline_extra_small'] = array(
    'label' => 'Page content inline extra small',
    'effects' => array(
      17 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 325,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: page_content_inline_large.
  $styles['page_content_inline_large'] = array(
    'label' => 'Page content inline large',
    'effects' => array(
      14 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1024,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: page_content_inline_medium.
  $styles['page_content_inline_medium'] = array(
    'label' => 'Page content inline medium',
    'effects' => array(
      15 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 768,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: page_content_inline_small.
  $styles['page_content_inline_small'] = array(
    'label' => 'Page content inline small',
    'effects' => array(
      16 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 512,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: page_content_portrait.
  $styles['page_content_portrait'] = array(
    'label' => 'Page content portrait',
    'effects' => array(
      13 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 465,
          'height' => 576,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'page_content_portrait',
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
}
