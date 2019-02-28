(function ($) {
Drupal.behaviors.database = {

  showRecommended: function(url) {
    if (url.includes('field_topics_depth')) {
      var ids_1 = [];
      var ids_0 = [];
      var ids = [];
      url.split('?')[1].split('&').forEach(function(param) {
        if (param.includes("field_topics_depth_1%3A")) {
            ids_1.push(param.split('field_topics_depth_1%3A')[1]);
            return;
        }
        else {
          if (param.includes("field_topics_depth_0%3A")) {
            ids_0.push(param.split('field_topics_depth_0%3A')[1]);
          }
        }
      });
      if (ids_1.length > 0) {
        ids = ids_1;
      }
      else {
        ids = ids_0;
      }
      ids.forEach(function(id) {
        $(".recommended-database.recid_" + id).show();
      });
    }
  },
  attach: function(context, settings) {
      var that = this;
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
    }
  };

  Drupal.toggleClearFilters = function(context, show) {
    if (show === true) {
      $(".clear-search-btn", context).fadeIn(200);
    }
    else {
      $(".clear-search-btn", context).fadeOut(200);
    }
  };


  var getSetting = function (input, setting, defaultValue) {
    // Earlier versions of jQuery, like the default for Drupal 7, don't properly
    // convert data-* attributes to camel case, so we access it via the verbatim
    // name from the attribute (which also works in newer versions).
    var search = $(input).data('search-api-autocomplete-search');
    if (typeof search == 'undefined'
        || typeof Drupal.settings.search_api_autocomplete == 'undefined'
        || typeof Drupal.settings.search_api_autocomplete[search] == 'undefined'
        || typeof Drupal.settings.search_api_autocomplete[search][setting] == 'undefined') {
      return defaultValue;
    }
    return Drupal.settings.search_api_autocomplete[search][setting];
  };

  if (Drupal.jsAC) {
      Drupal.jsAC.prototype.onkeyup = function (input, e) {
        if (!e) {
          e = window.event;
        }
        // This comes from drupals autocomplete.js
        if (!e) {
          e = window.event;
        }
        switch (e.keyCode) {
          case 16: // Shift.
          case 17: // Ctrl.
          case 18: // Alt.
          case 20: // Caps lock.
          case 33: // Page up.
          case 34: // Page down.
          case 35: // End.
          case 36: // Home.
          case 37: // Left arrow.
          case 38: // Up arrow.
          case 39: // Right arrow.
          case 40: // Down arrow.
            return true;

          case 9:  // Tab.
          case 13: 
            if ($(input).hasClass('auto_submit')) {
                var selector = getSetting(input, 'selector', ':submit');
                $(selector, input.form).trigger('click');
                Drupal.alreadyTriggered = true;
            }
          case 27: // Esc.
            this.hidePopup(e.keyCode);
            return true;

          default: // All other keys.
            if (input.value.length > 0 && !input.readOnly) {
              this.populatePopup();
            }
            else {
              this.hidePopup(e.keyCode);
            }
            return true;
        }
      };


      Drupal.jsAC.prototype.select = function(node) {
        var autocompleteValue = $(node).data('autocompleteValue');
        // Check whether this is not a suggestion but a "link".
        if (autocompleteValue.charAt(0) == ' ') {
          window.location.href = autocompleteValue.substr(1);
          return false;
        }
        this.input.value = autocompleteValue;
        $(this.input).trigger('autocompleteSelect', [node]);
        if ($(this.input).hasClass('auto_submit')) {
          if (typeof Drupal.search_api_ajax != 'undefined') {
            // Use Search API Ajax to submit
            Drupal.search_api_ajax.navigateQuery($(this.input).val());
          }
          else {
            if (!Drupal.alreadyTriggered) {
              var selector = getSetting(this.input, 'selector', ':submit');
              $(selector, this.input.form).trigger('click');
              Drupal.alreadyTriggered = false;
            }
          }
          return true;
        }
      };
    }

})(jQuery);


