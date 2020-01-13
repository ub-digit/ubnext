//jQuery plugin:
//TODO: cleanup
//TODO: Uncouple this plugin from drupal, do not use Drupal.settings.gmap_tools for example
//TODO: or make (this)? a drupal-specific plugin

// wrapped in this because google maps do not always load  (https://stackoverflow.com/questions/9228958/how-to-check-if-google-maps-api-is-loaded)
if (typeof google === 'object' && typeof google.maps === 'object') {
  (function($, maps) {
      //TODO: items should not be required, switch argument order?
      $.fn.gmap_tools_gmap = function(conf) {
        var markers_options = {};
        var gmap_tools = this.data('gmap_tools');

        if(gmap_tools) {
          return gmap_tools;
        }

        var conf = conf || {};

        //This is a little shitty, but convenient
        //Compile marker type options
        if(typeof Drupal.settings.gmap_tools != 'undefined' && typeof Drupal.settings.gmap_tools.markers != 'undefined') {
          conf.markers = Drupal.settings.gmap_tools.markers;
        }

        return this.each(function() {
          $this = $(this);
          gmap_tools = $this.data('gmap_tools');
          if(!gmap_tools) {
            $this.data('gmap_tools', new Drupal.gmap_tools.gmap(this, conf));
          }
        });
        return gmap_tools ? gmap_tools : this;
      }
  })(jQuery, google.maps);

  //TODO: check gmaps for reference, to avoid all this.function() etc
  (function($, maps) {

  //TODO: marker types goes here also

  Drupal.gmap_tools = {
    maps : {},
    behaviors : {}
  };

  Drupal.gmap_tools.gmap = function(map_wrapper, conf) {

    var self = this;
    this.gmap = {};
    // Internal private state variables
    var _items = {};

    var options = options || {};

    //init to all items

    var key;
    var i;
    var marker;
    var latlng;
    var info_window;
    var item;

    var conf_defaults = {
      gmap_conf: {
        zoom: 10,
        //center: new maps.LatLng(0,0), //todo: fix this
        mapTypeId: maps.MapTypeId.ROADMAP
      }
    };

    var conf = $.extend(true, {}, conf_defaults, conf);

    //TODO: correct way of handling this?
    //Fix conflicting options
    //Removing this for now
    /*
    if ('gmap_conf' in conf && 'center' in conf.gmap_conf) {
      conf.fit_markers_bounds = false;
    }
    else {
      conf.fit_markers_bounds = true;
    }

    if ('gmap_conf' in conf && 'zoom' in conf.gmap_conf) {
      conf.set_zoom = true;
    }
    else {
      conf.set_zoom = false;
    }
    */

    function maps_icon(icon_options) {
      //TODO: validation
      var maps_icon = {};

      if('anchor' in icon_options) {
        maps_icon.anchor = new maps.Point(icon_options.anchor[0], icon_options.anchor[1]);
      }

      if('origin' in icon_options) {
        maps_icon.origin = new maps.Point(icon_options.origin[0], icon_options.origin[1]);
      }

      if('scaled_size' in icon_options) {
        maps_icon.scaledSize = new maps.Size(icon_options.scaled_size[0], icon_options.scaled_size[1]);
      }

      if('size' in icon_options) {
        maps_icon.size = new maps.Size(icon_options.size[0], icon_options.size[1]);
      }

      maps_icon.url = icon_options.url;

      return maps_icon; 
    }

    //Compile marker styles
    //TODO: support other marker_options
    if('markers' in conf) {
      var icon_options;
      var style_options;
      // Icons
      for(icon in conf.markers.icons) {
        icon_options = conf.markers.icons[icon];
        conf.markers.icons[icon] = maps_icon(icon_options);
      }
      // Shadows
      if('shadows' in conf.markers) {
        for(shadow in conf.markers.shadows) {
          icon_options = conf.markers.shadows[shadow];
          conf.markers.icons[shadow] = maps_icon(icon_options);
        }
      }
      // Marker styles
      for(style in conf.markers.styles) {
        style_options = conf.markers.styles[style];
        conf.markers.styles[style].icon = conf.markers.icons[style_options.icon];
        conf.markers.styles[style].shape = conf.markers.shapes[style_options.shape];
        if('shadow' in conf.markers.styles[style]) {
          conf.markers.styles[style].shadow = conf.markers.shadows[style_options.shadow];
        }
      }
    }

    //TODO: allow override of conf
    //jquery extend?
    var gmap_conf = conf.gmap_conf;
    gmap_conf.minZoom = 2;
    this.gmap = new maps.Map(map_wrapper, gmap_conf);

    // center gmap on window resize
    var gmap = this.gmap;
    maps.event.addDomListener(window, "resize", function() {
        var center = gmap.getCenter();
        maps.event.trigger(gmap, "resize");
        gmap.setCenter(center); 
    });
    //save position (LatLng) directly on item?
    this.get_items_bounds = function() {
      var key;

      var bounds = new maps.LatLngBounds();
      for(key in _items) {
        bounds.extend(_items[key]._marker.getPosition());
      }

      return bounds;
    };

    this.set_marker = function(item) {
      var latlng = new maps.LatLng(item.lat, item.lng);

      //TODO: this smells?
      //TODO: correct to _marker

      var marker_options = {};

      if('markers' in  conf) {
        var marker_style = {};
        if ('marker' in item) {
          marker_style = conf.markers.styles[item.marker];
          if(typeof marker_style == 'undefined') {
            //Not throw just notice?
            throw "Marker style \"" + item.marker + "\" not defined in marker styles.";
          }
        }
        else if('default' in conf.markers.styles) {
          marker_style = conf.markers.styles['default'];
        }
        for(option in marker_style) {
          marker_options[option] = marker_style[option];
        }
      }

      marker_options.position = latlng;
      marker_options.title = item.title;

      var marker = new maps.Marker(marker_options);

      marker.setMap(this.gmap);

      return marker;
    };

    //todo, make private? clear _markers, delete??

    this.remove_marker = function(marker) {
      marker.setMap(null);
    };

    this.remove_items = function(items_keys) {
      //if undefined delete all
      for(i in items_keys) {
        var key = items_keys[i];
        maps.event.trigger(this.gmap, 'gmap_tools_item_removed', _items[key]);
        //Cleanup marker
        this.remove_marker(_items[key]._marker);
        delete _items[key];
      }
    }

    this.set_items = function(items) {
      //Remove old items
      var items_keys = [];
      for(key in _items) {
        items_keys.push(key);
      }
      this.remove_items(_items_keys);
      this.add_items(item);
    };

    this.add_items = function(items) {
      //TODO: item format validation
      for(key in items) {
        _items[key] = items[key];
        _items[key]._key = key;

        var marker = this.set_marker(_items[key]);

        _items[key]._marker = marker;

        maps.event.trigger(this.gmap, 'gmap_tools_item_added', _items[key]);
      }
      maps.event.trigger(this.gmap, 'gmap_tools_items_added', _items);
    };

    //or get items keys?
    this.empty_behavior = function() {
    };

    this.update_view = function() {
      /*
      if ('set_zoom' in conf && conf.set_zoom) {
        var listener = maps.event.addListener(this.gmap, 'idle', function() {
            self.gmap.setZoom(conf.gmap_conf.zoom);
            maps.event.removeListener(listener);
          }
        );
      }
      else {
        this.ajust_zoom();
      }
      */
    };

    this.get_marker = function(key) {
      return _items[key]._marker;
    };

    //Convenience methods for behaviors etc
    //TODO: filter here is perhaps kludgy, try to fix this
    this.get_visible_items = function(limit, filter) {
      var visible_items = [];
      var bounds = this.gmap.getBounds();
      var limit = limit || 0;
      var count = 0;
      var item;
      for(var key in _items) {
        item = _items[key];
        if((typeof filter === 'undefined' || filter(item)) && bounds.contains(item._marker.getPosition())) {
          if(limit && ++count > limit) {
            return false;
          }
          visible_items.push(item);
        }
      }
      return visible_items;
    };

    //apply behaviors
    if(typeof conf.behaviors !== 'undefined') {
      for(i in conf.behaviors) {
        //TODO: attach actually might be a better name, despite possible confusion with drupal's attach
        conf.behaviors[i].init(this);
      }
    }
    if('items' in conf) {
      this.add_items(conf.items);
    }
    this.update_view();
    //Temporary hack, fix this
    maps.event.trigger(this.gmap, 'zoom_changed');
  }
  })(jQuery, google.maps);

} // end wrapped google is defined check

(function($) {
    Drupal.behaviors.gmap_tools = {
      'attach' : function(context, settings) {
        if ('gmap_tools' in settings) {
          for (namespace in settings.gmap_tools) {
            var options = settings.gmap_tools[namespace];

            //TODO: ajax and attach behaviors? Will this work?
            if(!(namespace in settings.gmap_tools.maps)) {

              $map_container = $('#' + options.container_id, context);

              if($map_container.length) {
                //Build  conf
                //Clone?
                var gmap_conf = options.gmap_options;
                if('mapTypeId' in options.gmap_options) {
                  gmap_conf.mapTypeId = google.maps.MapTypeId[options.gmap_options.mapTypeId];
                }
                if('center' in options.gmap_options) {
                  gmap_conf.center = new google.maps.LatLng(
                    options.gmap_options.center.lat,
                    options.gmap_options.center.lng
                  );
                }
                //TODO: provide gmap_tools specific settings
                var conf = {
                  gmap_conf : gmap_conf
                };

                if ('items' in options) {
                  conf.items = options.items;
                }
                conf.behaviors = [];
                for (behavior in options.behaviors) {
                  if(behavior in Drupal.gmap_tools.behaviors) {
                    var behavior_options = options.behaviors[behavior];

                    //TODO: fix this kludy thing
                    for(var behavior_option in behavior_options) {
                      behavior_options[behavior_option] = Drupal.gmap_tools_js_data_process(behavior_options[behavior_option]);
                    }

                    conf.behaviors.push(new Drupal.gmap_tools.behaviors[behavior](behavior_options));
                  }
                  else {
                    //TODO
                    console.log('FAIL');
                  }
                }
                $map_container.gmap_tools_gmap(conf);
              }
            }
          }
        }
      }
    };
})(jQuery);
