/**
 * Copyright (c) 2007-2012 Ariel Flesler - aflesler(at)gmail(dot)com | http://flesler.blogspot.com
 * Dual licensed under MIT and GPL.
 * @author Ariel Flesler
 * @version 1.4.3.1
 */
;(function($){var h=$.scrollTo=function(a,b,c){$(window).scrollTo(a,b,c)};h.defaults={axis:'xy',duration:parseFloat($.fn.jquery)>=1.3?0:1,limit:true};h.window=function(a){return $(window)._scrollable()};$.fn._scrollable=function(){return this.map(function(){var a=this,isWin=!a.nodeName||$.inArray(a.nodeName.toLowerCase(),['iframe','#document','html','body'])!=-1;if(!isWin)return a;var b=(a.contentWindow||a).document||a.ownerDocument||a;return/webkit/i.test(navigator.userAgent)||b.compatMode=='BackCompat'?b.body:b.documentElement})};$.fn.scrollTo=function(e,f,g){if(typeof f=='object'){g=f;f=0}if(typeof g=='function')g={onAfter:g};if(e=='max')e=9e9;g=$.extend({},h.defaults,g);f=f||g.duration;g.queue=g.queue&&g.axis.length>1;if(g.queue)f/=2;g.offset=both(g.offset);g.over=both(g.over);return this._scrollable().each(function(){if(e==null)return;var d=this,$elem=$(d),targ=e,toff,attr={},win=$elem.is('html,body');switch(typeof targ){case'number':case'string':if(/^([+-]=)?\d+(\.\d+)?(px|%)?$/.test(targ)){targ=both(targ);break}targ=$(targ,this);if(!targ.length)return;case'object':if(targ.is||targ.style)toff=(targ=$(targ)).offset()}$.each(g.axis.split(''),function(i,a){var b=a=='x'?'Left':'Top',pos=b.toLowerCase(),key='scroll'+b,old=d[key],max=h.max(d,a);if(toff){attr[key]=toff[pos]+(win?0:old-$elem.offset()[pos]);if(g.margin){attr[key]-=parseInt(targ.css('margin'+b))||0;attr[key]-=parseInt(targ.css('border'+b+'Width'))||0}attr[key]+=g.offset[pos]||0;if(g.over[pos])attr[key]+=targ[a=='x'?'width':'height']()*g.over[pos]}else{var c=targ[pos];attr[key]=c.slice&&c.slice(-1)=='%'?parseFloat(c)/100*max:c}if(g.limit&&/^\d+$/.test(attr[key]))attr[key]=attr[key]<=0?0:Math.min(attr[key],max);if(!i&&g.queue){if(old!=attr[key])animate(g.onAfterFirst);delete attr[key]}});animate(g.onAfter);function animate(a){$elem.animate(attr,f,g.easing,a&&function(){a.call(this,e,g)})}}).end()};h.max=function(a,b){var c=b=='x'?'Width':'Height',scroll='scroll'+c;if(!$(a).is('html,body'))return a[scroll]-$(a)[c.toLowerCase()]();var d='client'+c,html=a.ownerDocument.documentElement,body=a.ownerDocument.body;return Math.max(html[scroll],body[scroll])-Math.min(html[d],body[d])};function both(a){return typeof a=='object'?a:{top:a,left:a}}})(jQuery);
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


  // ***************
  // FUNCTIONALITY *
  // ***************

  // (LANGUAGE) TOGGLE
  $('.js-language-toggle .nav__title').click(function() {
    $(this).siblings('*').slideToggle('fast').parent().toggleClass('open');
  });

  // (MENU) TOGGLE
  $('.js-nav-toggle .nav__title').click(function() {
    $(this).siblings('*').slideToggle('fast').parent().toggleClass('open');
  });

  // (HEADER) TOGGLE
  $('.js-header-toggle .nav__title, .js-header-toggle .block__title').click(function() {
    var element = $(this);
    var timeout = 0;
    if($('.js-header-toggle.open')) {
      var timeout = 200;
      $('.js-header-toggle.open .nav__title, .js-header-toggle.open .block__title').not($(this)).siblings('*').slideToggle('fast');
      $('.js-header-toggle.open').not($(this).parent()).removeClass('open');
    }
    setTimeout( function() {
      element.parent().toggleClass('open');
      element.siblings('*').slideToggle(300);
    }, timeout)
  });

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
