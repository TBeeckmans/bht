<?php
header('X-UA-Compatible: IE=edge,chrome=1');
/**
 * @file
 * Default theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 *
 * @ingroup themeable
 */
?>

<!DOCTYPE html>

<!--[if IEMobile 7]><html class="iem7"><![endif]-->
<!--[if (IE 7)&!(IEMobile)]><html class="no-js ie ie7" lang="<?php print $language->language; ?>"><![endif]-->
<!--[if (IE 8)&!(IEMobile)]><html class="no-js ie ie8" lang="<?php print $language->language; ?>"><![endif]-->
<!--[if (IE 9)&!(IEMobile)]><html class="no-js ie ie9" lang="<?php print $language->language; ?>"><![endif]-->
<!--[if (gt IE 9)|(gt IEMobile 7)|!(IE)]><!--><html class="no-js" lang="<?php print $language->language; ?>"><!--<![endif]-->

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>

  <?php if ((bool) variable_get('bht_production', FALSE)): ?>
    <script>
      ;(function(){function k(a,b){var d=!1;a&&"string"===typeof a&&(d=void 0===c[a]?void 0:Boolean(c[a]))&&b&&"function"===typeof b&&(d=Boolean(b(a)));return d}function l(a,b){try{c.setItem(a,b);if(Boolean(c.getItem(a)!==b))throw Error();m(a)}catch(d){try{c.setItem(a,"")}catch(e){}n(a)}}function p(a){for(var b in a)a.hasOwnProperty(b)&&q(b)}function q(a){var b=new XMLHttpRequest;b.open("GET","<?php print base_path() . path_to_theme(); ?>/css/"+f[a]+'?<?php print variable_get("css_js_query_string", "0"); ?>',
        !0);b.onload=function(){if(200<=b.status&&400>b.status){var c=b.responseText.replace(/\.\.\//g,"<?php print base_path() . path_to_theme(); ?>/");l(a,c)}else l(a,"")};b.send()}function n(a){if("queryString"!==a){a=f[a];var b=document.head,c=document.createElement("link");c.type="text/css";c.rel="stylesheet";c.href="<?php print base_path() . path_to_theme(); ?>/css/"+a;b.appendChild(c)}}function m(a){if("queryString"!==a){var b=document.createElement("style");b.rel="stylesheet";document.head.appendChild(b);
        b.textContent=c[a]}}function r(a){var b=!0;'<?php print variable_get("css_js_query_string", "0"); ?>'!==c[a]&&(b=!1);return b}var c,g,d,f={a:"style.min.css"};try{d=(new Date).toDateString(),(c=window.localStorage).setItem(d,d),g=c.getItem(d)!=d,c.removeItem(d),g=g&&(c=!1)}catch(a){try{(c=window.sessionStorage).setItem(d,d),g=c.getItem(d)!=d,c.removeItem(d),g=g&&(c=!1)}catch(b){}}if(c)try{var e,h=k("queryString",r);if(void 0===h)throw new TypeError;if(!1===h)throw new RangeError;for(e in f)if(f.hasOwnProperty(e)&&
        (h=k(e,void 0),void 0===h))throw new RangeError;for(e in f)f.hasOwnProperty(e)&&((h=k(e,void 0))?m(e):n(e))}catch(a){if(a instanceof RangeError){try{c.removeItem("queryString")}catch(b){}for(e in f)if(f.hasOwnProperty(e))try{c.removeItem(e)}catch(b){}}l("queryString",'<?php print variable_get("css_js_query_string", "0"); ?>');p(f)}})();
    </script>
    <!--[if gt IE 8]><!--><noscript><!--<![endif]-->
      <link rel="stylesheet" href="<?php print base_path() . path_to_theme(); ?>/css/style.min.css?<?php print variable_get('css_js_query_string', '0'); ?>">
                                    <!--[if gt IE 8]><!--></noscript><!--<![endif]-->
  <?php else: ?>
  <link rel="stylesheet" href="<?php print base_path() . path_to_theme(); ?>/css/style.css?<?php print variable_get('css_js_query_string', '0'); ?>">
  <?php endif; ?>

  <script src="<?php print base_path() . path_to_theme(); ?>/js/modernizr.custom.min.js?<?php print variable_get('css_js_query_string', '0'); ?>" type="text/javascript"></script>

  <!--[if lt IE 9]>
  <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js" type="text/javascript"></script>
  <![endif]-->
</head>

<body itemscope itemtype="http://schema.org/WebPage" class="<?php print $classes; ?>" <?php print $attributes;?>>

  <div class="wrapper">

    <header>
      <div class="container">
        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php ($site_slogan) ? print $site_slogan : print t('Home')  ?>" />
          </a>
        <?php endif; ?>
        <?php print $header; ?>
      </div>
    </header>

    <div id="main">
      <div class="container">
        <?php if ($messages): ?>
          <?php print $messages; ?>
        <?php endif; ?>

        <section id="content">
          <article role="article">
            <?php if (!empty($title)): ?>
              <h1><?php print $title; ?></h1>
            <?php endif; ?>
            <?php print $content; ?>
          </article>
        </section>
      </div>
    </div>

  </div>
  
  <?php print $scripts; ?>
  <?php /* ios-orientationchange-fix */ ?>
  <!--[if !(IE)]><!-->
    <script>
      (function(j){var i=j.document;if(!i.querySelectorAll){return}var l=i.querySelectorAll("meta[name=viewport]")[0],a=l&&l.getAttribute("content"),h=a+", maximum-scale=1.0",d=a+", maximum-scale=10.0",g=true,c=j.orientation,k=0;if(!l){return}function f(){l.setAttribute("content",d);g=true}function b(){l.setAttribute("content",h);g=false}function e(m){c=Math.abs(j.orientation);k=Math.abs(m.gamma);if(k>8&&c===0){if(g){b()}}else{if(!g){f()}}}j.addEventListener("orientationchange",f,false);j.addEventListener("deviceorientation",e,false)})(this);
    </script>
  <!--<![endif]-->
</body>
</html>
