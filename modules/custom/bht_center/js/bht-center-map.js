/**
 * Created by tbeeckmans on 13/04/16.
 */

(function ($) {

  /**
   * Initialize a google map.
   * Map is rendered as an overview, which shows all bht centers.
   *
   * @param {Number} lat
   * @param {Number} long
   * @param {Number} zoom
   */
  function initializeMap(lat, lng, zoom, callback) {
    console.log('test');
    var latLng = new google.maps.LatLng(lat, lng);

    var defaultMapOptions = Drupal.settings.bht_center_map_options;

    var styles = '';
    if (defaultMapOptions.custom_style) {
      styles = JSON.parse(defaultMapOptions.custom_style);
    }

    var mapOptions = {
      mapTypeId: google.maps.MapTypeId.ROADMAP,
      center: latLng,
      zoom: zoom,
      styles: styles,
      // The MapType control lets the user toggle between map types (such as ROADMAP and SATELLITE).
      // This control appears by default in the top right corner of the map.
      mapTypeControl: JSON.parse(defaultMapOptions.map_type_control),
      mapTypeControlOptions: {
        position: google.maps.ControlPosition.LEFT_BOTTOM,
      },
      // The disableDefaultUI property disables any automatic UI behavior from the Google Maps API.
      disableDefaultUI: JSON.parse(defaultMapOptions.disable_default_ui),
      // Disable scrollwheel zooming on the map
      scrollwheel: false,
      // The streetViewControl enables/disables the Pegman control that lets the user activate a Street View panorama.
      streetViewControl: JSON.parse(defaultMapOptions.street_view_control)
    };

    // Define map as a global variable, so we can allow the navigator to set the center.
    window.map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);

    // Invoke callback function.
    callback();
    
  };

  /**
   * Converts numeric degrees to radians.
   */
  if (typeof (Number.prototype.toRadians) === "undefined") {
    Number.prototype.toRadians = function () {
      return this * Math.PI / 180;
    };
  };

  /**
   * Calculate distance between 2 bht centers
   */
  function getDistance(lat, lng, lat_center, lng_center) {
    var R = 6371; // km
    var φ1 = lat.toRadians();
    var φ2 = lat_center.toRadians();
    var Δφ = (lat_center - lat).toRadians();
    var Δλ = (lng_center - lng).toRadians();

    var a = Math.sin(Δφ / 2) * Math.sin(Δφ / 2) +
      Math.cos(φ1) * Math.cos(φ2) *
      Math.sin(Δλ / 2) * Math.sin(Δλ / 2);
    var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));

    var d = R * c;
    return d;
  };

  /**
   * Sort keys.
   *
   * @param obj
   * @returns {Array.<T>}
   */
  function getSortedKeys(obj) {
    var keys = [];
    for (var key in obj) keys.push(key);
    return keys.sort(function (a, b) {
      return obj[a] - obj[b]
    });
  };

  /**
   * Act on geolocation success.
   * This callback function takes a position object as its sole input parameter.
   *
   * @param {Object} pos
   */
  function geolocationSuccess(pos) {
    var latLng = new google.maps.LatLng(pos.coords.latitude, pos.coords.longitude);
    map.setCenter(latLng);
  };



  /**
   * Build the content of an overview map.
   * For each available bht center, a map marker is created,
   * an info window and event listener is added.
   *
   */
  function buildMapContent() {

    // Initialize a markers array in order to handle changed map boundaries.
    markersArray = [];

    $.each(Drupal.settings.bht_center_map_markers, function (key, value) {

      if (!isNaN(key)) {
        // Create marker.
        var latLng = new google.maps.LatLng(value.lat, value.lng);
        var marker = new google.maps.Marker({
          nid: key,
          position: latLng,
          map: map,
          icon: value.icon,
        });

        // Create infoWindow.
        var infoWindow = new google.maps.InfoWindow({
          content: value.html
        });

        // Add event listener on every marker.
        google.maps.event.addListener(marker, 'click', function () {
          infoWindow.open(map, marker);
        });

        // Add to markers array in order to handle changed map boundaries.
        markersArray.push(marker);

      }

    });
  }

  /**
   * Build the map filter.
   */
  function buildMapFilter() {
    // TODO: Add the search filter
  };

  /**
   * Dynamically load the bht centers information.
   * This function is called when map boundaries are changed
   * in order to reload the available bht centers in the map-overview div.
   */
  function buildOverviewContent() {
    /**
     * First check if the rendered teasers should be shown
     */
    if ($('.js-map-overview').length > 0) {
      // Check visible bht centers
      var lat_center = map.getCenter().lat();
      var lng_center = map.getCenter().lng();
      var distances = {};
      for (var a in markersArray) {
        var lat = markersArray[a].position.lat();
        var lng = markersArray[a].position.lng();
        distances[a] = getDistance(lat, lng, lat_center, lng_center);
      }
      distances = getSortedKeys(distances);

      var nids = [];
      for (var i in distances) {
        a = distances[i];
        var onMap = map.getBounds().contains(markersArray[a].getPosition());

        if (onMap) {
          nids.push(markersArray[a].nid);
        }
      }

      $('.js-map-overview').trigger('updateBhtCenters', [nids]);
    }
  };

  Drupal.behaviors.bhtCenter = {
    attach: function (context, settings) {
      google.maps.event.addDomListener(window, 'load', function () {
        // Load map.
        var zoom = Drupal.settings.bht_center_map_zoom === 0 ? parseInt(Drupal.settings.bht_center_map_options.default_zoom) : Drupal.settings.bht_center_map_zoom;
        initializeMap(Drupal.settings.bht_center_map_center.lat, Drupal.settings.bht_center_map_center.lng, zoom, function () {
          // Create search filter.
          if (Drupal.settings.bht_center_map_search) {
            buildMapFilter();
          }

          // Create bht centers markers and info windows.
          buildMapContent();

          // If teasers are dynamically loaded, react when boundaries of the map change.
          google.maps.event.addListener(map, 'bounds_changed', function () {
            buildOverviewContent();
          });

          // Clustering.
          var mcOptions = {gridSize: 30, maxZoom: 15, minZoom: 1};

          setTimeout(function () {
            var mc = new MarkerClusterer(map, markersArray, mcOptions);
          }, 500);
        });
      });

      if (Drupal.settings.bht_center_map_geolocation) {
        // If the user allows geolocation, change map focus.
        if (navigator.geolocation) {
          navigator.geolocation.getCurrentPosition(geolocationSuccess);
        }
      }
    }
  };
  
})(jQuery);
