(function($) {
  Drupal.behaviors.ubn_news_equal_heights = {
    attach: function(context, settings) {
      if ($.fn.matchHeight) {
        $('.story-promoted', context).matchHeight();
      }
    }
  };


   Drupal.behaviors.ubn_news_accessibility = {
    attach: function(context, settings) {
      $(document).keydown(function(e){
        if(e.keyCode == 9){
         $('.promoted-wrapper').addClass('show-focus-outlines');
        }
      });

      $(document).on('mousedown', function(){
        $('.promoted-wrapper').removeClass('show-focus-outlines');
      });
    }
  };

  Drupal.behaviors.ubn_news_blurb_mouse = {
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
})(jQuery);
