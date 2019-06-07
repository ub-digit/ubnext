(function($) {
  Drupal.behaviors.ubn_news_equal_heights = {
    attach: function(context, settings) {
      if ($.fn.matchHeight) {
        $('.story-promoted', context).matchHeight();
      }
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
