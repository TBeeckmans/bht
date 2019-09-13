<?php

/**
 * PREPROCESS HOOKS.
 */

/**
 * Implements template_preprocess_html().
 */
function bht_theme_preprocess_html(&$variables) {
  // Define important css classes.
  $classes_to_keep = array(
    'front',
    'page-taxonomy-term',
  );

  // Add the node type class to the classes to keep list.
  $nodetype = preg_grep('/^node-type/', $variables['classes_array']);
  if ($nodetype) {
    $type = current($nodetype);
    $classes_to_keep[$type] = TRUE;
  }

  // Strip all CSS classes but and keep the important ones.
  foreach ($variables['classes_array'] as $key => $class) {
    if (!in_array($class, $classes_to_keep)) {
      unset($variables['classes_array'][$key]);
    }
  }

  if (isset($type) && $type == 'node-type-events') {
    $node = menu_get_object();
    if ($node->promote) {
      $variables['classes_array'][] = 'node-type-events-promote';
    }
  }

  // Add critical css inline #perfmatters.
  if (!(bool) variable_get('bht_production', FALSE)) {
    // Read critical css file contents.
    $critical_css = file_get_contents(path_to_theme() . '/css/critical.min.css');
    // Replace css folder relative paths to site related relative paths.
    $critical_css = str_replace('../', base_path() . path_to_theme() . '/', $critical_css);
    drupal_add_css(
      $critical_css,
      array(
        'type' => 'inline',
        'weight' => 1000,
        'group' => CSS_THEME,
      )
    );
  }

  // Add the production or development javascript files #perfmatters.
  if (!(bool) variable_get('bht_production', FALSE)) {
    drupal_add_js(path_to_theme() . '/js/production.min.js', 'file');
  }
  else {
    // Remember to alter gruntfile.js to generate a correct production.min.js file.
    /*drupal_add_js(path_to_theme() . '/js/jquery.colorbox-min.js', 'file');*/
    /*drupal_add_js(path_to_theme() . '/js/jquery.fitvids-min.js', 'file');*/
    /*drupal_add_js(path_to_theme() . '/js/jquery.scrollto.min.js', 'file');*/
    drupal_add_js(path_to_theme() . '/js/scripts.js', 'file');
  }

  // Add theme folder to the variables.
  $variables['theme_folder'] = base_path() . path_to_theme() . '/';

  // Add themePath to drupal settings, cfr. existing basePath.
  $extra_js_settings = array(
    'themePath' => $variables['theme_folder'],
  );
  drupal_add_js($extra_js_settings, 'setting');

  // Strip out wbr character
  if (isset($variables['head_title_array']['title'])) {
    $variables['head_title_array']['title'] = str_replace('||', '', $variables['head_title_array']['title']);
  }
  if (isset($variables['head_title'])) {
    $variables['head_title'] = str_replace('||', '', $variables['head_title']);
  }

}

/**
 * Implements template_preprocess_page().
 */
function bht_theme_preprocess_page(&$variables, $hook) {
  // Remove div wrapper around main content.
  if (isset($variables['page']['content']['system_main']['#theme_wrappers'])
    && is_array($variables['page']['content']['system_main']['#theme_wrappers'])
  ) {
    $variables['page']['content']['system_main']['#theme_wrappers'] = array_diff($variables['page']['content']['system_main']['#theme_wrappers'], array('block'));
  }
}

/**
 * Implements template_preprocess_node()
 */
function bht_theme_preprocess_node(&$variables) {
  // Define default theme hook suggestion for nodes.
  // Set node--{view_mode}.tpl.php.
  $variables['theme_hook_suggestions'][] = "node__" . $variables['view_mode'];
  // Set node--{node_type}.tpl.php.
  $variables['theme_hook_suggestions'][] = "node__" . $variables['type'];
  // Set node--{node_type}--{view_mode}.tpl.php.
  $variables['theme_hook_suggestions'][] = "node__" . $variables['type'] . "__" . $variables['view_mode'];
  if ($variables['type'] == 'events' && $variables['view_mode'] == 'full' && $variables['promote']) {
    // Set node--{node_type}--{view_mode}.tpl.php.
    $variables['theme_hook_suggestions'][] = "node__" . $variables['type'] . "__" . $variables['view_mode'] . "_promoted";
  }
  // Set node--{nid}.tpl.php.
  $variables['theme_hook_suggestions'][] = "node__" . $variables['nid'];

  // Merge in any custom attributes set in the renderable array.
  if (isset($variables['node']->attributes_array)
    && is_array($variables['node']->attributes_array)
  ) {
    $variables['attributes_array'] = drupal_array_merge_deep($variables['attributes_array'], $variables['node']->attributes_array);
  }

  // Replace || with <wbr> tag.
  $variables['title'] = str_replace('||', '<wbr>&shy;', $variables['title']);
}

/**
 * Implements template_preprocess_taxonomy_term().
 */
function bht_theme_preprocess_taxonomy_term(&$variables) {
  // Remove taxonomy term description wrapper.
  if (!empty($variables['content']['description'])) {
    $variables['content']['description']['#prefix'] = '';
    $variables['content']['description']['#suffix'] = '';
  }

  // Define default theme hook suggestion for taxopnomy terms.
  // Set taxonomy-term--{view_mode}.tpl.php.
  $variables['theme_hook_suggestions'][] = "taxonomy_term__" . $variables['view_mode'];
  // Set taxonomy-term--{vocabulary}--{view_mode}.tpl.php.
  $variables['theme_hook_suggestions'][] = "taxonomy_term__" . $variables['vocabulary_machine_name'] . "__" . $variables['view_mode'];

  // Merge in any custom attributes.
  if (isset($variables['term']->attributes_array)
    && is_array($variables['term']->attributes_array)
  ) {
    $variables['attributes_array'] += $variables['term']->attributes_array;
  }

  // Replace || with <wbr> tag.
  $variables['name'] = str_replace('||', '<wbr>&shy;', $variables['name']);
}

/**
 * Implements template_preprocess_user_profile()
 */
function bht_theme_preprocess_user_profile(&$variables) {
  // Define default theme hook suggestion for users.
  // Set user-profile--{view_mode}.tpl.php.
  $variables['theme_hook_suggestions'][] = "user_profile__" . $variables['elements']['#view_mode'];
}

/**
 * Implements template_preprocess_views_view_table().
 */
function bht_theme_preprocess_views_view_table(&$variables) {
  // If there are no classes to be added, do nothing.
  if (!$variables['options']['default_row_class']
    && !$variables['options']['row_class_special']
  ) {
    return;
  }

  // If standard classes are to be added, remove them.
  if ($variables['options']['default_row_class']) {
    foreach ($variables['row_classes'] as $key => $class) {
      $variables['row_classes'][$key] = array();
    }
  }

  // Add first / last, odd / even classes.
  if ($variables['options']['row_class_special']) {
    $max = count($variables['rows']) - 1;
    foreach ($variables['row_classes'] as $key => $class) {
      $classes = array();

      if ($key == 0) {
        $classes[] = 'first';
      }
      if ($key == $max) {
        $classes[] = 'last';
      }

      $classes[] = $key % 2 ? 'even' : 'odd';

      $variables['row_classes'][$key] = $classes;
    }
  }
}

/**
 * Implements template_preprocess_views_view_list().
 */
function bht_theme_preprocess_views_view_list(&$variables) {
  bht_theme_preprocess_views_view_unformatted($variables);
}

/**
 * Implement template_preprocess_views_view_unformatted().
 */
function bht_theme_preprocess_views_view_unformatted(&$variables) {
  // If there are no classes to be added, do nothing.
  if (!$variables['options']['default_row_class']
    && !$variables['options']['row_class_special']
  ) {
    return;
  }

  // If standard classes are to be added, remove them.
  if ($variables['options']['default_row_class']) {
    foreach ($variables['classes_array'] as $key => $class) {
      $variables['classes_array'][$key] = '';
    }
  }

  // Add first / last, odd / even classes.
  if ($variables['options']['row_class_special']) {
    $max = count($variables['rows']) - 1;
    foreach ($variables['classes'] as $key => $class) {
      $classes = array();

      if ($variables['options']['default_row_class'] && !empty($variables['options']['row_class'])) {
        $classes[] = $variables['options']['row_class'];
      }

      if ($key == 0) {
        $classes[] = 'first';
      }
      if ($key == $max) {
        $classes[] = 'last';
      }

      $classes[] = $key % 2 ? 'even' : 'odd';
      if ($key % 3 === 0) {
        $classes[] = 'third';
      }
      if ($key % 4 === 0) {
        $classes[] = 'fourth';
      }

      $variables['classes_array'][$key] = implode(' ', $classes);
    }
  }
}

/**
 * Clean up the panel pane variables for the template.
 */
function bht_theme_preprocess_panels_pane(&$variables) {
  $pane = &$variables['pane'];
  $content = &$variables['content'];

  // Set basic classes.
  $variables['classes_array'] = array();
  $variables['classes_array'][] = 'pane';
  if (!empty($variables['admin_links'])) {
    $variables['classes_array'][] = 'contextual-links-region';
  }

  // Add some usable classes based on type/subtype.
  while (!empty($content) && gettype($content) == 'array' && !isset($content['#entity_type']) && !isset($content['#theme'])) {
    $content = reset($content);
  }

  // Set the entity.
  $entity = NULL;
  if (isset($content['#entity'])) {
    $entity = $content['#entity'];
  }
  elseif (isset($content['#entity_type']) && isset($content['#' . $content['#entity_type']])) {
    $entity = $content['#' . $content['#entity_type']];
  }

  // Add the entity specific classes.
  if (isset($content['#entity_type']) && isset($content['#bundle'])) {
    $variables['classes_array'][] = 'pane--' . $content['#entity_type'];
    $variables['classes_array'][] = 'pane--' . $content['#bundle'];
  }
  // Use the pane type class as fallback.
  elseif (!empty($pane->type)) {
    ctools_include('cleanstring');
    $type_class = $pane->type ? ctools_cleanstring($pane->type, array('lower case' => TRUE)) : '';
    $variables['classes_array'][] = 'pane--' . $type_class;
  }

  // Add id and custom class if sent in.
  if (!empty($pane->css['css_id'])) {
    $variables['id'] = ' id="' . $pane->css['css_id'] . '"';
  }
  if (!empty($pane->css['css_class'])) {
    $variables['classes_array'][] = $pane->css['css_class'];
  }

  // Set a BEM pane title.
  $needle = array_search('pane-title', $variables['title_attributes_array']['class']);
  if ($needle !== FALSE) {
    unset($variables['title_attributes_array']['class'][$needle]);
  }
  $variables['title_attributes_array']['class'][] = 'pane__title';

  // Check if the bean block has a link set.
  if (isset($entity) && get_class($entity) == 'Bean') {
    if (isset($entity->field_link) && !empty($entity->field_link)) {
      $link = $entity->field_link;

      // Get the link array.
      while (!isset($link['url']) && gettype($link) == 'array') {
        $link = reset($link);
      }

      // Parse the link address from the link array.
      if (isset($link['url']) && strlen($link['url']) > 0) {
        // Get the internal source link.
        $linkurl = theme_get_relative_link($link['url']);
        // If an internal link is found, wrap the block content in a link.
        if ($linkurl && ($needle = array_search('panels_pane__block', $variables['theme_hook_suggestions'])) !== FALSE) {
          // Add a theme hook suggestion before the specific nid-delta suggestion.
          array_splice($variables['theme_hook_suggestions'], ++$needle, 0, 'panels_pane__block__bean_has_link');
          // Add the block--has-link class.
          $variables['classes_array'][] .= ' pane--bean-has-link';
          // Add the internal path to the block variables.
          $variables['link'] = $linkurl;
          // Add possible link options.
          $variables['link_options'] = array();
        }
      }
    }
  }
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function bht_theme_panels_default_style_render_region($vars) {
  $output = '';
//  $output .= '<div class="region region-' . $vars['region_id'] . '">';
//  $output .= implode('<div class="panel-separator"></div>', $vars['panes']);
//  $output .= '</div>';
  $output .= implode('', $vars['panes']);
  return $output;
}


/**
 * Implements template_preprocess_block().
 */
function bht_theme_preprocess_block(&$variables) {
  $block = $variables['elements']['#block'];

  // Strip all classes except the ones we defined ourselves via the block class module
  // and the contextual links
  if (in_array('contextual-links-region', $variables['classes_array'])) {
    $variables['classes_array'] = array('contextual-links-region');
  }
  else {
    $variables['classes_array'] = array();
  }

  if (isset($block->css_class) && !empty($block->css_class)) {
    $classes_array = explode(' ', $block->css_class);
    $variables['classes_array'] = array_merge($variables['classes_array'], $classes_array);
  }

  // Add a theme suggestion to block--menu.tpl so we dont have create a ton of blocks with <nav>
  if (($block->module == "system" && $block->delta == "main-menu")
    || $block->module == "menu_block"
  ) {
    $variables['theme_hook_suggestions'][] = 'block__menu';
  }
}

/**
 * Implements template_preprocess_entity_HOOK().
 */
function bht_theme_preprocess_entity(&$variables, $hook) {
  // Check if a link is set.
  if (isset($variables['elements']['#entity_type'])
    && $variables['elements']['#entity_type'] === 'bean'
  ) {
    // Set new default bean wrapper classes.
    if (!empty($variables['elements']['#bundle'])) {
      $variables['classes_array'] = array($variables['elements']['#bundle']);
      if (isset($variables['elements']['#entity']->label)) {
        $variables['classes_array'][] = $variables['elements']['#bundle'] . '--' . $variables['elements']['#entity']->delta;
      }
    }
    else {
      $variables['classes_array'] = array('bean');
    }

    if (!empty($variables['field_link'])) {
      $link = $variables['field_link'];

      // Get the link array.
      while (!isset($link['url']) && gettype($link) == 'array') {
        $link = reset($link);
      }

      // Parse the link address from the link array.
      if (isset($link['url']) && strlen($link['url']) > 0) {
        // Try to get the internal source link.
        $linkurl = theme_get_relative_link($link['url']);
        // If an internal link is found, wrap the block content in a link.
        if ($linkurl && $needle = array_search("bean__" . $variables['elements']['#bundle'] . "__" . $variables['elements']['#view_mode'], $variables['theme_hook_suggestions'])) {
          // Add a theme hook suggestion before the specific nid-delta suggestion.
          $extra_theme_hook_suggestions = array(
            "bean__" . $variables['elements']['#bundle'] . "__has_link",
            "bean__" . $variables['elements']['#bundle'] . "__" . $variables['view_mode'] . "__has_link",
          );
          array_splice($variables['theme_hook_suggestions'], ++$needle, 0, $extra_theme_hook_suggestions);
        }
      }
    }
  }
}

/**
 * ALTER HOOKS.
 */

/**
 * Implements hook_html_head_alter().
 */
function bht_theme_html_head_alter(&$head_elements) {
  unset($head_elements['system_meta_generator']);

  // Set theme folder variable.
  $theme_folder = base_path() . path_to_theme() . '/';

  // Add standard sized Apple touch icons.
  $head_elements[] = array(
    '#type' => 'html_tag',
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'href' => $theme_folder . 'img/apple-touch-icon.png',
    ),
  );

  // Add large sized Apple touch icons.
  $sizes = array(
    '144x144',
    '114x114',
    '72x72',
  );
  foreach ($sizes as $size) {
    $head_elements[] = array(
      '#type' => 'html_tag',
      '#tag' => 'link',
      '#attributes' => array(
        'rel' => 'apple-touch-icon',
        'sizes' => $size,
        'href' => $theme_folder . 'img/apple-touch-icon-' . $size . '.png',
      ),
    );
  }

  // Add meta viewport information.
  $head_elements[] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1.0',
    ),
  );

  // Alter rdf_node_title to make it valid.
  if (isset($head_elements['rdf_node_title'])) {
    if (!empty($head_elements['rdf_node_title']['#attributes']['about'])) {
      unset($head_elements['rdf_node_title']['#attributes']['about']);
    }
    // Strip out wbr character.
    $head_elements['rdf_node_title']['#attributes']['content'] = str_replace('||', '', $head_elements['rdf_node_title']['#attributes']['content']);
  }

  // Unset shortlink & canonical meta tag.
  foreach ($head_elements as $key => $value) {
    // Unset shortlink.
    if (strpos($key, 'shortlink') !== FALSE) {
      unset($head_elements[$key]);
    }
    // Unset canonical on homepage.
    if (drupal_is_front_page()) {
      if (strpos($key, 'canonical') !== FALSE) {
        unset($head_elements[$key]);
      }
    }
  }
}

/**
 * Implements hook_css_alter().
 */
function bht_theme_css_alter(&$css) {
  global $theme;
  $path = drupal_get_path('theme', $theme);

  // Get all css we need to keep.
  $css_to_keep = array_map('trim', explode("\n", theme_get_setting('css_to_keep')));
  $css_to_keep = array_flip($css_to_keep);
  // Add some defaults ourselves.
  $css_to_keep['admin_menu_toolbar.css'] = TRUE;
  $css_to_keep['admin_menu.css'] = TRUE;
  $css_to_keep['admin_menu.uid1.css'] = TRUE;

  foreach ($css as $key => $file) {
    // Make sure we don't strip CSS from our own theme.
    $regex = "/^" . str_replace("/", "\\/", $path) . "/";

    if (!preg_match($regex, $key)) {
      $filename_array = explode('/', $key);
      $filename = end($filename_array);

      // Keep the theme and inline css files.
      if (!preg_match("/^bht_theme_(\w+)\.css$/", $filename)
        && !isset($css_to_keep[$filename])
        && !($file['type'] == 'inline')
      ) {
        unset($css[$key]);
      }
    }
  }
}

/**
 * Implements hook_js_alter().
 */
function bht_theme_js_alter(&$js) {
  // Add live reloading during development.
  //if ((bool) variable_get('bht_production', FALSE)) {
  //  drupal_add_js(
  //    '//' . $_SERVER['HTTP_HOST'] . ':35729/livereload.js?snipver=1',
  //    array(
  //      'type' => 'external',
  //      'scope' => 'header',
  //      'weight' => 20,
  //      'group' => '-200',
  //      'preprocess' => FALSE,
  //    )
  //  );
  //}

  // Strip the JS we defined in our settings.
  if (!theme_get_setting('js_to_strip')) {
    return;
  }

  global $theme;
  $path = drupal_get_path('theme', $theme);

  $js_to_strip = array_map('trim', explode("\n", theme_get_setting('js_to_strip')));
  $js_to_strip = array_flip($js_to_strip);

  foreach ($js as $key => $file) {
    // Make sure we don't strip JS from our own theme.
    $theme_key = substr($key, 0, strlen($path));

    // Determine filename.
    $filename_array = explode('/', $key);
    $filename = end($filename_array);

    if (isset($js_to_strip[$filename]) && $theme_key != $path) {
      unset($js[$key]);
    }
  }
}

/**
 * Implements hook_block_view_alter()
 */
function bht_theme_block_view_alter(&$data, $block) {
  global $language;

  switch ($block->delta) {
    // Change language switcher block title to current language.
    case 'language':
      $block->title = $language->language;
      break;
  }

}

/**
 * NAVIGATION.
 */

/**
 * Overwrite theme_menu_tree().
 */
function bht_theme_menu_tree($variables) {
  return '<ul class="nav__list">' . $variables['tree'] . '</ul>';
}

/**
 * Overwrite theme_menu_link().
 */
function bht_theme_menu_link(&$variables) {
  $element = &$variables['element'];
  $sub_menu = '';

  // Remove the has-children class from the nav item
  // if it has no renderable child items below
  if (!isset($element['#below']) || empty($element['#below'])) {
    $key = array_search('has-children', $element['#attributes']['class']);
    if ($key) {
      unset($element['#attributes']['class'][$key]);
    }
  }

  // Define the default classes we want to strip from the nav item
  $strip_classes = array(
    'leaf',
    'menu-mlid-[0-9]',
  );

  // Strip some default classes from the nav item
  _strip_classes($element['#attributes']['class'], $strip_classes);

  // Add BEM classes to the nav item
  _bemify_classes($element['#attributes']['class'], 'nav__item');

  // Add the attributes array for the nav link
  if (!isset($element['#localized_options']['attributes']['class'])) {
    $element['#localized_options']['attributes']['class'] = array();
  }

  // Add BEM classes to the nav link
  _bemify_classes($element['#localized_options']['attributes']['class'], 'nav__link');

  // Render the child items
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Render the nav link
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  // Return the nav item
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * @param array $source the referenced class array you are about to alter
 * @param array $strip the classes that you are about to remove
 */
function _strip_classes(&$source, $strip) {
  foreach ($strip as $class) {
    if (strpos($class, '[') !== FALSE && strpos($class, ']') !== FALSE) {
      $matches = preg_grep('/^' . $class . '/i', $source);
      if (!empty($matches)) {
        foreach ($matches as $key => $matched) {
          unset($source[$key]);
        }
      }
    }
    elseif (($key = array_search($class, $source)) !== FALSE) {
      unset($source[$key]);
    }
  }
}

/**
 * @param array $source the referenced class array you are about to alter
 * @param string $prefix the block__element class
 * @param array $decline the classes that should be left as they are
 */
function _bemify_classes(&$source, $prefix = '', $decline = array(
  'first',
  'last',
  'active-trail',
  'active',
)) {
  foreach ($source as $key => $class) {
    if (!in_array($class, $decline)) {
      $source[$key] = strtolower($prefix) . '--' . $class;
    }
  }
  array_unshift($source, strtolower($prefix));
}

/**
 * Overwrite theme_breadcrumb().
 */
function bht_theme_breadcrumb($variables) {
  $output = '';

  // Remove breadcrumbs for 403 / 404.
  $headers = drupal_get_http_header();
  if (isset($headers['status']) && $headers['status'] == '404 Not Found') {
    return NULL;
  }
  if (isset($headers['status']) && $headers['status'] == '403 Forbidden') {
    return NULL;
  }

  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    $total_crumbs = count($breadcrumb);

    // Replace any placeholders for wbr tags.
    foreach (element_children($breadcrumb) as $key => $value) {
      $breadcrumb[$value] = str_replace('||', '', $breadcrumb[$value]);
    }

    $output = '<span class="breadcrumb__title">' . t('You are here: ') . '</span>';

    $i = 0;
    $output .= '<ol class="breadcrumb__list" itemscope itemtype="https://schema.org/BreadcrumbList">';
    foreach ($breadcrumb as $crumb) {
      // Add classes to the crumb.
      $crumb_attributes = array('class' => array('breadcrumb__item'));
      if (++$i === 1) {
        $crumb_attributes['class'][] = 'first';
      }
      if ($i === $total_crumbs) {
        $crumb_attributes['class'][] = 'last';
      }

      $output .= '<li ' . drupal_attributes($crumb_attributes) . ' itemprop="itemListElement" itemscope itemtype="https://schema.org/ListItem">';
      $output .= $crumb . '<meta itemprop="position" content="' . $i . '" />'; // Each crumb is themed by bht_mtbp module
      $output .= '</li>';
    }
    $output .= '</ol>';

    // Add a back button at the end of the menu trail.
    if (module_exists('bht_mtbp')) {
      $output .= _bht_mtbp_back_link();
    }
  }

  return $output;
}

/**
 * Overwrite theme_links().
 * Specifically for language switcher.
 */
function bht_theme_links__locale_block($variables) {
  $links = $variables['links'];

  $output = '';

  if (count($links) > 0) {
    $output .= '<ul class="language">';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first & last classes to the list
      // We've removed the active class because it's on the anchor element already.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }

      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Remove the 'language-link' class.
        $link['attributes'] = array();

        // Pass in $link as $options, they share the same keys.
        $output .= l($link['language']->language, $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        $output .= '<span>' . $link['language']->language . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Overwrite theme_pager().
 *
 * You can also adjust pager navigation seperately using theme overwriting of:
 * - pager_first
 * - pager_previous
 * - pager_next
 * - pager_last
 */
function bht_theme_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re quantity).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re quantity).
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];
  // End of marker calculations.
  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme(
    'pager_first',
    array(
      'text' => (isset($tags[0]) ? $tags[0] : t('« first')),
      'element' => $element,
      'parameters' => $parameters,
    )
  );
  $li_previous = theme(
    'pager_previous',
    array(
      'text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')),
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  $li_next = theme(
    'pager_next',
    array(
      'text' => (isset($tags[3]) ? $tags[3] : t('next ›')),
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  $li_last = theme(
    'pager_last',
    array(
      'text' => (isset($tags[4]) ? $tags[4] : t('last »')),
      'element' => $element,
      'parameters' => $parameters,
    )
  );

  if ($pager_total[$element] > 1) {
    if (!empty($li_first)) {
      $items[] = array(
        'class' => array('pager__item', 'pager__item--first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager__item', 'pager__item--prev'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager__item'),
            'data' => theme(
              'pager_previous',
              array(
                'text' => $i,
                'element' => $element,
                'interval' => ($pager_current - $i),
                'parameters' => $parameters,
              )
            ),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager__item', 'pager__item--current'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager__item'),
            'data' => theme(
              'pager_next',
              array(
                'text' => $i,
                'element' => $element,
                'interval' => ($i - $pager_current),
                'parameters' => $parameters,
              )
            ),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager__item', 'pager__item--next'),
        'data' => $li_next,
      );
    }
    if (!empty($li_last)) {
      $items[] = array(
        'class' => array('pager__item', 'pager__item--last'),
        'data' => $li_last,
      );
    }
    return '<p class="element-invisible">' . t('Pages') . '</p>' . theme(
      'item_list',
      array(
        'items' => $items,
        'attributes' => array('class' => array('pager')),
      )
    );
  }
}

/**
 * FORM HOOKS.
 */

/**
 * Overwrite theme_form().
 */
function bht_theme_form($variables) {
  $element = $variables['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }

  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}

/**
 * Overwrite theme_form_element().
 */
function bht_theme_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element's title as class
  // but do some illegal character removing first.
  $attributes = array();
  if (isset($variables['element']['#title'])) {
    $class = strtolower(str_replace(' ', '_', trim(preg_replace("/[^A-Za-z0-9 ]/", '', $variables['element']['#title']))));
    $attributes['class'][] = $class;
  }


  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span>' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span>' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<small>' . $element['#description'] . "</small>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Overwrite theme_webform_element().
 */
function bht_theme_webform_element($variables) {
  // Ensure defaults.
  $variables['element'] += array(
    '#title_display' => 'before',
  );

  $element = $variables['element'];

  $output = '<div class="' . $variables['element']['#webform_component']['form_key'] . '">' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span>' . _webform_filter_xss($element['#field_prefix']) . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span>' . _webform_filter_xss($element['#field_suffix']) . '</span>' : '';

  switch ($element['#title_display']) {
    case 'inline':
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= ' <small>' . $element['#description'] . "</small>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Overwrite theme_webform_email().
 */
function bht_theme_webform_email($variables) {
  $element = $variables['element'];

  // This IF statement is mostly in place to allow our tests to set type="text"
  // because SimpleTest does not support type="email".
  if (!isset($element['#attributes']['type'])) {
    $element['#attributes']['type'] = 'email';
  }

  // Convert properties to attributes on the element if set.
  foreach (array('id', 'name', 'value', 'size') as $property) {
    if (isset($element['#' . $property]) && $element['#' . $property] !== '') {
      $element['#attributes'][$property] = $element['#' . $property];
    }
  }
  /*_form_set_class($element, array('form-text', 'form-email'));*/

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overwrite theme_form_element_label().
 */
function bht_theme_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  $attributes = array();

  // If the element is required, add a required class.
  if (!empty($element['#required'])) {
    $attributes['class'][] = 'required';
  }
  // If it's invisble, add class.
  if ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  $title = filter_xss_admin($element['#title']);

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title', array('!title' => $title)) . "</label>\n";
}

/**
 * Overwrite theme_textfield().
 */
function bht_theme_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes(
    $element,
    array(
      'id',
      'name',
      'value',
      'size',
      'maxlength',
    )
  );
  _form_set_class($element, '');

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Overwrite theme_fieldset().
 */
function bht_theme_fieldset($variables) {
  $element = $variables['element'];

  // If we have a webform component, use the key as class.
  if (isset($variables['element']['#webform_component']['form_key'])) {
    $class = $variables['element']['#webform_component']['form_key'];
    // Format the css class to Drupal standards.
    $class = drupal_clean_css_identifier($class);
    $element['#attributes']['class'] = $class;
  }
  // If no key is available, use a title.
  elseif (isset($variables['element']['#title'])) {
    // Keep only lowercase printable standard ASCII characters.
    $class = strtolower(trim(preg_replace("/[^A-Za-z0-9 ]/", '', $variables['element']['#title'])));
    // Format the css class to Drupal standards.
    $class = drupal_clean_css_identifier($class);
    $element['#attributes']['class'] = $class;
  }

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    $output .= '<legend>' . $element['#title'] . '</legend>';
  }
  if (!empty($element['#description'])) {
    $output .= '<small>' . $element['#description'] . '</small>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= "</fieldset>\n";
  return $output;
}

/**
 * Overwrite theme_textarea().
 */
function bht_theme_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));

  if (isset($element['#required']) && $element['#required']) {
    $element['#attributes']['class'][] = 'required';
  }

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
  }

  $output = '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';

  return $output;
}

/**
 * Overwrite theme_checkboxes().
 */
function bht_theme_checkboxes($variables) {
  $element = $variables['element'];
  $attributes = array();

  $attributes['class'][] = 'form-checkboxes';
  if (isset($element['#required']) && $element['#required']) {
    $attributes['class'][] = 'required';
  }

  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

/**
 * Overwrite theme_checkbox().
 */
function bht_theme_checkbox($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'checkbox';
  element_set_attributes(
    $element,
    array(
      'id',
      'name',
      '#return_value' => 'value',
    )
  );

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overwrite theme_radios().
 */
function bht_theme_radios($variables) {
  $element = $variables['element'];
  $attributes = array();
  $attributes['class'][] = 'form-radios';
  if (isset($element['#required']) && $element['#required']) {
    $attributes['class'][] = 'required';
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

/**
 * Overwrite theme_radio().
 */
function bht_theme_radio($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'radio';
  element_set_attributes(
    $element,
    array(
      'id',
      'name',
      '#return_value' => 'value',
    )
  );

  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overwrite theme_select().
 */
function bht_theme_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  if (isset($element['#required']) && $element['#required']) {
    $element['#attributes']['class'][] = 'required';
  }

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}

/**
 * Overwrite theme_button().
 */
function bht_theme_button($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'value'));
  $element['#attributes']['type'] = 'submit';

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  if ($element['#type'] == 'button') {
    return '<button' . drupal_attributes($element['#attributes']) . ' >' . $variables['element']['#value'] . '</button>';
  }
  else {
    return '<input' . drupal_attributes($element['#attributes']) . ' />';
  }
}

/**
 * GENERAL.
 */

/**
 * Overwrite theme_item_list().
 */
function bht_theme_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(
          array(
            'items' => $children,
            'title' => NULL,
            'type' => $type,
            'attributes' => $attributes,
          )
        );
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

/**
 * Overwrite theme_file_link().
 */
function bht_theme_file_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $url = file_create_url($file->uri);
  $icon = theme(
    'file_icon',
    array(
      'file' => $file,
      'icon_directory' => $icon_directory,
    )
  );

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $options = array(
    'attributes' => array(
      'type' => $file->filemime . '; length=' . $file->filesize,
    ),
  );

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }

  // Calculate filesize.
  // Taken from http://www.ascadnetworks.com/Guides-and-Tips/Format-a-File-Size-in-PHP
  if (($file->filesize / 1073741824) > 1) {
    $filesize = round(($file->filesize / 1073741824), 2) . "Gb";
  }
  elseif (($file->filesize / 1048576) > 1) {
    $filesize = round(($file->filesize / 1048576), 2) . "Mb";
  }
  elseif (($file->filesize / 1024) > 1) {
    $filesize = round(($file->filesize / 1024), 2) . "Kb";
  }
  else {
    $filesize = $file->filesize . " bytes";
  }

  return '<span class="file">' . $icon . ' ' . l($link_text, $url, $options) . ' (' . $filesize . ')</span>';
}

/**
 * Theme function for table view.
 */
function bht_theme_tablefield_view($variables) {
  $output = '';
  $delta = (int) $variables['delta'];
  $table_field_zebra = ((++$delta % 2) === 0) ? 'even' : 'odd';

  if (empty($variables['rows'])) {
    return $output;
  }

  // Build the wrapper.
  $output .= "\n\r<div class=\"table-field $table_field_zebra\">";

  // Build the header.
  if (!empty($variables['header'])) {
    $output .= "\n\r\t<div class=\"table-field__head\">";
    $output .= "\n\r\t\t<div class=\"table-field__row\">";
    foreach ($variables['header'] as $thid => $th) {
      $output .= "\n\r\t\t\t<div class=\"table-field__cell\">" . $th['data'] . "</div>";
    }
    $output .= "\n\r\t\t</div>";
    $output .= "\n\r\t</div>";
  }

  // Build the body.
  $output .= "\n\r\t<div class=\"table-field__body\">";
  foreach ($variables['rows'] as $trid => $tr) {
    $table_field__row_zebra = ((++$trid % 2) === 0) ? 'even' : 'odd';
    if ($trid == 1) {
      $table_field__row_zebra .= ' first';
    }
    $output .= "\n\r\t\t<div class=\"table-field__row $table_field__row_zebra\">";
    foreach ($tr as $tdid => $td) {
      $table_field__cell_zebra = ((++$tdid % 2) === 0) ? 'even' : 'odd';
      $output .= "\n\r\t\t\t<div class=\"table-field__cell $table_field__cell_zebra\"";
      if (!empty($variables['header'])) {
        $output .= " data-label=\"" . $variables['header'][--$tdid]['data'] . "\"";
      }
      $output .= ">" . $td['data'] . "</div>";
    }
    $output .= "\n\r\t\t</div>";
  }
  $output .= "\n\r\t</div>";

  $output .= "\n\r</div>";

  return $output;
}

/**
 * CUSTOM FUNCTIONS.
 */

/**
 * Helper function for returning the relative source path.
 *
 * @param string $source_link
 *    The source link.
 *
 * @return string
 *    The relative link to the entity or boolean false.
 */
function theme_get_relative_link($source_link) {
  global $language_url, $base_url, $base_path;
  $langcode = $language_url->prefix;
  $http_host = $base_url . $base_path . $langcode;

  // Format absolute internal link as a relative internal link.
  $link = preg_replace('/^' . preg_quote($http_host, '/') . '/', '', $source_link);

  // Strip possible leading forward slash.
  if (!is_null($link)) {
    $link = preg_replace('/^\//', '', $link);
  }

  // Get the internal source link.
  if (!is_null($link)) {
    $link = drupal_get_normal_path($link, $langcode);
  }
  else {
    return (bool) $link;
  }

  return $link;
}

/**
 * Helper function for stripping text of all links.
 *
 * @param string $text
 *    The text to alter possible links into.
 *
 * @return string
 *    The text without links.
 */
function theme_strip_links($text) {
  return preg_replace(
    array('/<a(\s+[^>]+)>/im', '/<a>/im'),
    array(
      '<span$1>',
      '',
    ),
    preg_replace(
      array(
        '/\s+href=[\'""](?:.+?)[\'""]/im',
        '/<\/a>/im',
      ),
      array('', '</span>'), $text
    )
  );
}
