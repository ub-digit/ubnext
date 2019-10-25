(function ($) {
Drupal.behaviors.database = {
  attach: function(context, settings) {
   /*   var that = this;
      that.showRecommended(window.location.href);
      //Drupal.setupHistory();
      if ($(".form-autocomplete").val() === "") {
        if (/=field_topics_depth_/.test(window.location.href)) {
          $('.ubn-search-sorts').hide();
        }
        else {
          $('.ubn-search-sorts .last').hide();
        }
      }
      else {
        $('.ubn-search-sorts .last').show();
        $(".clear-search-btn").show();
      }

      $(".form-autocomplete", context).on("change paste keyup", function() {
          if ($(this).val().length > 0) {
            Drupal.toggleClearFilters(context, true);
          }
          else {
            Drupal.toggleClearFilters(context, false);
          }
      });

      $(".facet-filter a, .clear-search-btn, .ubn-search-results-show-all, .sort-item", context).on("click", function() {
          //Drupal.loadHTMLFragment($(this).attr("href"), that.showRecommended);
          if ($(this).hasClass("clear-search-btn"))
          {
            $('.form-autocomplete',context).val(''); // does not trigger change..
            Drupal.toggleClearFilters(context, false);
            let sv = window.location.pathname.indexOf('/sv/');
            if (sv != - 1) {
              window.location.href = "/sv/databaser/sok";
            }
            else {
              window.location.href = "/en/databases/search";
            }
            $(".form-autocomplete", context).focus();
            return false; 
          }
          //return false;
      });

      $('.database-item-link-title a', context).on( "click", function() {
        window.location.href = $(this).attr("href") + "#refering";
        return false;
      });

      $('.ubn-facet-header', context).on( "click", function() {
        var $next = $(this).next();
        if ($next.hasClass("item-list")) {
          if ($next.hasClass("expanded")) {
              $next.removeClass("expanded")
              var $fa = $(this).find(".fa")
              if ($fa.hasClass("fa-chevron-up")) {
                $fa.removeClass("fa-chevron-up");
                $fa.addClass("fa-chevron-down");
              }
          }
          else {
            $next.addClass("expanded");
            var $fa = $(this).find(".fa")
            if ($fa.hasClass("fa-chevron-down")) {
              $fa.removeClass("fa-chevron-down");
              $fa.addClass("fa-chevron-up");
            }

          }
        }
      });
    }*/
  };
})(jQuery);


