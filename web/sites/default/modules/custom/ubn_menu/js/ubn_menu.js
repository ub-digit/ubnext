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
        // If there is no admin menu present or if we're at production server, this is irrelevant
        if(window.location.hostname == 'beta.ub.gu.se'){
          return false;
        }

        let hostname = window.location.hostname;
        var message, env;

        // Check which server ubnext is running on and assign message accordingly
        if (hostname.indexOf('beta-lab.ub.gu.se') > -1){
          env = 'TESTMILJÖ (Lab)';
          message = 'Detta är en testmiljö. Använd endast för test.';
        }else if(hostname.indexOf('beta-staging.ub.gu.se') > -1){
          env = 'Demomiljö (Staging)';
          message = 'Här testar och demonstrerar vi nyutvecklade saker.';
          //Demomiljö (staging). Här testar och demonstrerar vi nyutvecklade saker.
        }else if(hostname.indexOf('localhost') > -1){
          env = 'localhost'
          message = 'lokal utvecklingsmiljö';
        }

        if (message){
          //Add space for message
          var padding_top = 0;
          if (settings.admin_menu) padding_top = 24;
          $('body').css('padding-top', padding_top + 'px');
          $('body').prepend($('<div id="temp-golive-alert" class="server-message" style="font-size:1em;text-align:center;color:#882c2a;background:#dda6a6;padding:10px;width:100%;z-index: 100;"><strong>' + env +'</strong><br>' + message + '</div>'));
        }
      });
      
    }
  };
})(jQuery);
