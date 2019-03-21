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
        // If there is no admin menu present, this is irrelevant
        if(!settings.admin_menu){
          return false;
        }

        let hostname = window.location.hostname;
        var message;

        // Check which server ubnext is running on and assign message accordingly
        if (hostname.indexOf('beta-lab.ub.gu.se') > -1){
          message = 'lab';
        }else if(hostname.indexOf('beta-staging.ub.gu.se') > -1){
          message = 'staging';
        }else if(hostname.indexOf('localhost') > -1){
          message = 'local';
        }

        if (message){
          //Add space for message 
          $('body').css('padding-top','103px');
          $('body').append($('<div id="temp-golive-alert" class="server-message" style="font-size:1em;text-align:center;color:#882c2a;background:#dda6a6;padding:10px;position:fixed;top:50px;width:100%;z-index: 100;"><strong>TESTMILJÖ (' + message + ')</strong><br>Detta är en testmiljö. Använd endast för test.</div>'));
        }
      });
      
    }
  };
})(jQuery);
