(function ($) {

  // ***********
  // ESSENTIAL *
  // ***********

  // Give warning for IE8
  if ($.browser.msie && $.browser.version == "8.0"){
    $('<div />')
      .attr("style", "background: pink; padding: 10px; text-align: center;")
      .text(Drupal.t("We do no longer support IE8, please update your browser!"))
      .prependTo('body');
  }

  // Add novalidate attribute to all forms because HTML5 validation fucks with
  // the Ajax callbacks in, for example, commerce checkout process
  // Also, this way a user gets to see all error messages at once instead of only one at a time
  $('form').attr('novalidate', true);


  // ***********
  // USABILITY *
  // ***********

  // Select all text on iput field click
  $('body').delegate('input', 'click', function () {
    $(this).select();
  });

  // UX telephone keyboard trigger
  if($('#edit-submitted-telephone-number').length) {
    $('#edit-submitted-telephone-number')[0].type = 'tel';
  }

  // ***********
  // ANALYTICS *
  // ***********

  // Load when header and all HTML have been sent
  var delimiters = "-|\\.|—|–|&nbsp;";
  var spechars = new RegExp("([- \(\)\.:]|\\s|" + delimiters + ")","gi"); //Special characters to be removed from the link
  $(document).ready(function() {
    $("a[href^='tel:']").click(function(e) {
      // prevent link from redirecting
      e.preventDefault();

      var link  = $(this).attr('href');

      if (window.ga) {
        var tracklink = link.replace('tel:','').replace(spechars,'');
        ga('send', 'event', 'Phone', 'Click', tracklink);
      }

      setTimeout(function() {
        window.location = link;
      },300);
    });
    $("a[href^='mailto:']").click(function(e) {
      // prevent link from redirecting
      e.preventDefault();

      var link  = $(this).attr('href');

      if (window.ga) {
        var tracklink = link.replace('mailto:','').replace(spechars,'');
        ga('send', 'event', 'Email', 'Click', tracklink);
      }

      setTimeout(function() {
        window.location = link;
      },300);
    });
  });


  //chk_dynamic
  // initial set
  $(document).ready(function(element) {
    $('.js-chk-dynamic').each(function(e){
      if ($(this).find('input[type="checkbox"]').is(":checked")) {
        $(this).toggleClass('checked');
      }
    });
  });


  // To stuff when small element is clicked
  $('.js-chk-dynamic').each(function(e){
    $(this).find('small').click(function(e) {
      toggle_state($(this));
    });

    $(this).find('input[type="checkbox"]').bind('focus blur', function(){
      $(this).parent().parent().find('small').toggleClass('focus');
    });
  });

  // old functionalty to add class when radio is checked
  $('.js-chk-dynamic').find('input[type="checkbox"]').each(function(e) {
    $(this).click(function() {
      $(this).parent().parent().toggleClass('checked');
    });
  });

  function toggle_state(item, init) {
    if (init == false || typeof init === 'undefined') {
      if ($(item).parent().find('input[type="checkbox"]').is(":checked")) {
        $(item).parent().find('input[type="checkbox"]').trigger('click').value(0);
        $(item).parent().removeClass('checked');
      }
      else {
        $(item).parent().find('input[type="checkbox"]').trigger('click').value(1);
        $(item).parent().find('input[type="text"]').focus();
        $(item).parent().addClass('checked');
      }
    }
  }

  // ***************
  // FUNCTIONALITY *
  // ***************

  // (MENU) TOGGLE
  $('.js-nav-toggle .nav__title').click(function() {
    $(this).parent().toggleClass('open');
  });

  // (HEADER) TOGGLE
  updatePage = function () {
    scrollTop = $(window).scrollTop();
    if (scrollTop > giInitiateFixedPosition) {
      $('body').addClass('is-fixed-header');
      $('#main').css('padding-top', giInitiateFixedPosition+'px');
      if (prevTop - 4 > scrollTop) {
        $('body').addClass('show-fixed-header');
      }
      if (prevTop+2 < scrollTop) {
        $('body').removeClass('show-fixed-header');
      }
    } else if (scrollTop <= giInitiateFixedPosition) {
      $('body').removeClass('is-fixed-header').removeClass('show-fixed-header');
      $('#main').css('padding-top', '0');
    }
    prevTop = $(window).scrollTop();
  }

  var oTargetElement = $('.js-fixed-header');
  var scrollTop = 0;
  var prevTop = 0;
  var giInitiateFixedPosition = oTargetElement.height() + oTargetElement.offset().top;
  //check scrolling from user
  var scrollIntervalID = setInterval(updatePage, 10);

  // Everything that needs to be executed when all our images/files/... are
  // loaded, not only when DOM is ready
  $(window).load(function() {
    // // FLEXSLIDER
    // $('.js-flexslider').flexslider({
    //   selector: ".banner__list > .banner__item",
    //   animation: "slide",
    //   mousewheel: false,
    //   slideshow: true,
    //   animationLoop: true,
    //   slideshowSpeed: 4000,
    //   animationSpeed: 600,
    //   controlNav: false,
    //   touch: true
    // });

    // // COLORBOX
    // $(".js-colorbox a").colorbox({
    //   rel:'gal',
    //   transition:'fade',
    //   maxWidth:'100%',
    //   maxHeight:'100%',
    //   title:function(){
    //     return $(this).find("img").attr('alt')
    //   }
    // });
    // // Hide title tag where empty
    // $(document).bind("cbox_complete", function(){
    //   if($('#cboxTitle').is(':empty')) {
    //     $("#cboxTitle").hide();
    //   }
    // });

    // FITVIDS
    // $(".player").fitVids();

  });
})(jQuery);
