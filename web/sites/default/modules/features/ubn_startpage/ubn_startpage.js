(function($) {
  Drupal.behaviors.ubn_startpage_equal_heights = {
    attach: function(context, settings) {
      if ($.fn.matchHeight) {
        $('.blurb', context).matchHeight();
      }
    }
  };

  Drupal.behaviors.ubn_startpage_blurb_mouse = {
    attach: function(context, settings) {
      $('.promoted-wrapper').on('mouseenter mouseleave', function(){
      	let el = $(this);
      	el.toggleClass('active');
      	 let img = el.find('.image-placeholder');
        if(img){
          img.toggleClass('active');
        }
      });
    }
  };

  Drupal.behaviors.ubn_startpage_accessibility = {
    attach: function(context, settings) {
      $(document).keydown(function(e){
        if(e.keyCode == 9){
         $('.blurb-wrapper').addClass('show-focus-outlines');
        }
      });

      $(document).on('mousedown', function(){
        $('.blurb-wrapper').removeClass('show-focus-outlines');
      });
    }
  };

  Drupal.behaviors.ubn_startpage_main_blurb_mouse = {
    attach: function(context, settings) {
      $('.blurb-wrapper').on('mouseenter mouseleave', function(){
        let el = $(this);
        el.toggleClass('active');
         let img = el.find('.image-placeholder');
        if(img){
          img.toggleClass('active');
        }
      });
    }
  };
})(jQuery);
