/**
 * Created by tbeeckmans on 07/04/16.
 */

(function ($) {

  /**
   * Updates the overview of rendered teasers depending on which bht centers are visible on the map
   *
   * Should be called when bounds of the Google map change
   */

  $(function() {
    $('.js-map-overview').bind('updateBhtCenters', function (event, nids) {
      var overviewMarkup = '';
      for (var i = 0; i < nids.length; i++) {
        overviewMarkup += Drupal.settings.bht_center_items[nids[i]];
      }

      $(this).html(overviewMarkup);
    })
  });

})(jQuery);
