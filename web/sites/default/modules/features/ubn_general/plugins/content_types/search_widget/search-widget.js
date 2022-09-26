(function($) {
  Drupal.behaviors.searchWidget = {
    attach: function(context, settings) {
     // $('input[name="query"]', context).focus();
    }
  };
  // hijack form and redirect to Primo
  $(document).ready(function() {
    $('body').on('click', '.custom-form button', function(e) {
      e.preventDefault();
      var lang = $('html').attr('lang');
      lang = lang == 'sv' ? 'sv_SE' : 'en_US';
      var query = $('.custom-form input[name="query"]').val();
      window.dataLayer = window.dataLayer || [];
      window.dataLayer.push({'event': 'UAEvent', 'eventCategory': 'Startsida', 'eventAction': 'Supersök', 'eventLabel': query});
      var seachCriteria = query.length > 0 ? 'any,contains,' : '';
      query = encodeURIComponent(query);
      var url = 'https://gu-se-primo.hosted.exlibrisgroup.com/primo-explore/search?query=' + seachCriteria + query + '&vid=46GUB_VU1&search_scope=default_scope&sortby=rank&lang=' + lang;
      window.location.href = url;
    });
  });

})(jQuery);