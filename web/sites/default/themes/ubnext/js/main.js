(function ($) {

  Drupal.behaviors.ubnext_shortcuts = {
    attach : function(context, settings) {
      var items = $('.shortcut-widget-link-list li');
      if (items.length < 5) {
        $("#btn-load-more-shortcuts").hide();
      }
      $('#btn-load-more-shortcuts').bind('click', function() {
        //$('.latest-stories-widget-link-list li:nth-child(n+5)').toggle();
        $(".shortcut-widget").toggleClass('open');
        $('#btn-load-more-shortcuts').toggleClass('closed');
      });

      $('.shortcut-widget-link-list li').bind('click', function() {
        let url = $(this).find('a').attr("href");
        window.location.href = url;
      });


    }
  };


  Drupal.behaviors.ubnext_database = {
    attach : function(context, settings) {
      if (!$(".node-type-database").length) {
        return;
      }
      if (window.location.hash.substr(1) != "refering") {
        $('.database-back-link-wrapper').hide();
      }
    }
  };

  Drupal.behaviors.ubnext_landing = {
    attach : function(context, settings) {
      $('.ubn-theme-links .ubn-theme-links-item').bind('click', function() {
        let url = $(this).find('a').attr("href");
        window.location.href = url;
      });
    }
  };


  Drupal.behaviors.ubnext_fitvids = {
    attach: function(context, settings) {
      $('.ubn-video-player', context).fitVids();
    }
  };

  Drupal.behaviors.ubnext_equal_heights = {
    attach : function(context, settings) {
      /* TODO: rename ubn-pane */
      if ($.fn.matchHeight) {
        $('.ubn-panel-links:not(.news-widget)', context).matchHeight();
      }
    }
  };

  Drupal.ubnext = {
    scrollTo : function($element, callback) {
      if($element.length) {
        $admin_menu = $('#admin-menu-wrapper');
        var offset = $admin_menu.length ? $admin_menu.outerHeight() : 0;
        $('html, body').animate({
          scrollTop: $element.offset().top - offset
        }, 200, "swing", callback);
      }
    }
  };
})(jQuery);
