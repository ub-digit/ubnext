(function ($) {

  Drupal.behaviors.ubn_menu = {
    attach: function(context, settings) {
      $("#toggle-menu-btn, #menu-btn-close", context).on("click", function() {
      	if (!$("#toggle-menu-btn", context).hasClass("open")) {
      		$("#toggle-menu-btn", context).addClass("open");
      		$(".ubn-mobile-menu", context).show();
      	}
      	else {
      		$("#toggle-menu-btn", context).removeClass("open");
      		$(".ubn-mobile-menu", context).hide();
      	}
      });
      $(".ubn-mobile-menu", context).hide();
        


    }
  }

  Drupal.behaviors.ubnext_server_marking = {
    attach : function(context, settings) {
      $(window).load(function(){
        // Does not apply to production server
        if(window.location.hostname == 'beta.ub.gu.se'){
          return false;
        }

        let hostname = window.location.hostname;
        var message, env;

        // Check which server ubnext is running on and assign message accordingly
        if (hostname.indexOf('-lab.ub.gu.se') > -1){
          env = 'TESTMILJÖ (Lab)';
          message = 'Detta är en testmiljö. Använd endast för test.';
        }else if(hostname.indexOf('-staging.ub.gu.se') > -1){
          env = 'Demomiljö (Staging)';
          message = 'Här testar och demonstrerar vi nyutvecklade saker.';
        }else if(hostname.indexOf('localhost') > -1){
          env = 'localhost'
          message = 'lokal utvecklingsmiljö';
        }
        var setMarkerTopMargin = function(){
          var adminMenu = $('#admin-menu');
          if (adminMenu.length){
            $('#temp-golive-alert').css('margin-top', adminMenu.height() + 'px');  
          }
        };
        if (message){
          //Add space for message
          if (!jQuery('#temp-golive-alert').length){
            setTimeout(function(){
              $('body').prepend($('<div id="temp-golive-alert" class="server-message" style="font-size:1em;text-align:center;color:#882c2a;background:#dda6a6;padding:10px;width:100%;z-index: 100;"><strong>' + env +'</strong><br>' + message + '</div>'));
              setMarkerTopMargin();
            }, 300);
          }
          // on resize set top margin on banner
          $(window).resize(function(){
            setMarkerTopMargin();
          });
        }
      });
      
    }
  };
})(jQuery);
