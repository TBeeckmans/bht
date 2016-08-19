<?php
header('X-UA-Compatible: IE=edge,chrome=1');
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
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

  <?php if (!(bool) variable_get('bht_production', FALSE)): ?>
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
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $scripts; ?>
  <?php /* ios-orientationchange-fix */ ?>
  <!--[if !(IE)]><!-->
    <script>
      (function(j){var i=j.document;if(!i.querySelectorAll){return}var l=i.querySelectorAll("meta[name=viewport]")[0],a=l&&l.getAttribute("content"),h=a+", maximum-scale=1.0",d=a+", maximum-scale=10.0",g=true,c=j.orientation,k=0;if(!l){return}function f(){l.setAttribute("content",d);g=true}function b(){l.setAttribute("content",h);g=false}function e(m){c=Math.abs(j.orientation);k=Math.abs(m.gamma);if(k>8&&c===0){if(g){b()}}else{if(!g){f()}}}j.addEventListener("orientationchange",f,false);j.addEventListener("deviceorientation",e,false)})(this);
    </script>
  <!--<![endif]-->
  <?php print $page_bottom; ?>
</body>
</html>
