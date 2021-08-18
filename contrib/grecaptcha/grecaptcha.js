var grecaptcha_ready = false;
(function($) {
  Drupal.grecaptcha = {
    'elements' : {},
  };
  Drupal.behaviors.grecaptcha = {
    'attach' : function (context, settings) {
      if(!grecaptcha_ready) {
        return;
      }
      var recaptcha_settings = settings.grecaptcha.settings;
      for(i in settings.grecaptcha.elements) {
        var setting = settings.grecaptcha.elements[i];
        var $element = $('#' + setting.id, context);
        if($element.length) {
          var element = $element.get(0);
          var params = {
            'sitekey' : recaptcha_settings.sitekey,
            'theme' : recaptcha_settings.theme,
            'type' : recaptcha_settings.type,
            'size' : recaptcha_settings.size
          };
          if(recaptcha_settings.compact_breakpoint && $(window).width() < recaptcha_settings.compact_breakpoint) {
            params.size = 'compact';
          }
          if(recaptcha_settings.disable_submit) {
            //How safe is this selector?
            var $form_submit = $element.closest('form').find('.form-submit').attr('disabled', 'disabled');
            params.callback = (function(element_id, $submit) { return function(response) {
                $submit.removeAttr('disabled');
              };
            })(setting.id, $form_submit);

            params.expired_callback = (function(element_id, $submit) { return function() {
                $submit.attr('disabled', 'disabled');
              };
            })(setting.id, $form_submit);
          }
          if('tabindex' in recaptcha_settings && recaptcha_settings.tabindex) {
            params.tabindex = recaptcha_settings.tabindex;
          }
          Drupal.grecaptcha.elements[setting.id] = grecaptcha.render(element, params);
        }
      }
    }
  };
})(jQuery);

var grecaptcha_onload_callback = function() {
  grecaptcha_ready = true;
  (function ($) {
    $(function () {
      Drupal.behaviors.grecaptcha.attach(document, Drupal.settings);
    });
  })(jQuery);
};
