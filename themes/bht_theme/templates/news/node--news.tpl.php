<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php
hide($content['comments']);
hide($content['links']);
if (isset($content['language'])) {
  hide($content['language']);
}
if (isset($content['cover_image'])) {
  hide($content['cover_image']);
}

$paragraph_title = FALSE;
$paragraph_tags = FALSE;
$paragraph_date = FALSE;
if (isset($content['field_body']) && !empty($content['field_body'])) {
  $paragraph_title = _bht_paragraphs_title_set($content['field_body']);
  $paragraph_tags = _bht_paragraphs_tags_set($content['field_body']);
  $paragraph_date = _bht_paragraphs_date_set($content['field_body']);
}
?>


<?php

$date = $created;
if (isset($news_date[LANGUAGE_NONE][0]['value'])) {
  $date = $news_date[LANGUAGE_NONE][0]['value'];
}

// Determine the BEM block
$css_block = drupal_clean_css_identifier($type);

// Determine the BEM modifier
$css_modifier = '';
if (!$page) {
  $css_modifier = drupal_clean_css_identifier($view_mode);
}

// The attributes_array contains classes defined in overviews
if (!isset($attributes_array['class'])) {
  $attributes_array['class'] = array();
}

// Add the wrapper classes to the attributes_array
if ($page) {
  $attributes_array['class'][] = 'article';
  $attributes_array['class'][] = $css_block . '__article';
}
else {
  $attributes_array['class'][] = $css_block . '__item';
  $attributes_array['class'][] = $css_block . '__item--' . $css_modifier;
}

// Add the title classes to the title_attributes_array
if ($page) {
  $title_attributes_array['class'][] = $css_block . '__page-title';
}
else {
  $title_attributes_array['class'][] = 'item-title';
  $title_attributes_array['class'][] = $css_block . '__item-title';
  $title_attributes_array['class'][] = $css_block . '__item-title--' . $css_modifier;
}
?>


<?php if ($page): ?>

  <article role="article" itemscope
           itemtype="http://schema.org/NewsArticle"
    <?php print drupal_attributes($attributes_array); ?>>

    <?php if (!$paragraph_title): ?>
      <h1 itemprop="name"
        <?php print drupal_attributes($title_attributes_array); ?>>
        <?php print $title; ?>
      </h1>
    <?php endif; ?>

    <?php if (!$paragraph_date): ?>
      <div class="news__date news__date--page">
        <span class="news__day">
          <?php print format_date($date, 'custom', 'j', NULL, $language); ?>
        </span>
        <span class="news__month">
          <?php print format_date($date, 'custom', 'F', NULL, $language); ?>
        </span>
        <span class="news__year">
          <?php print format_date($date, 'custom', 'Y', NULL, $language); ?>
        </span>
      </div>
    <?php endif; ?>

    <?php print render($content); ?>

  </article>

<?php else: ?>

  <a href="<?php print url('node/' . $nid); ?>" <?php print drupal_attributes($attributes_array); ?>>

    <div class="news__date news__date--<?php print $css_modifier; ?>">
      <span class="news__day">
        <?php print format_date($date, 'custom', 'j', NULL, $language); ?>
      </span>
      <span class="news__month">
        <?php print format_date($date, 'custom', 'F', NULL, $language); ?>
      </span>
      <span class="news__year">
        <?php print format_date($date, 'custom', 'Y', NULL, $language); ?>
      </span>
    </div>

    <div itemprop="name" <?php print drupal_attributes($title_attributes_array); ?>>
      <?php print $title; ?>
    </div>

    <?php if (isset($content['cover_image'])): ?>
      <div class="news__image">
        <?php print theme_strip_links(render($content['cover_image'])); ?>
      </div>
    <?php endif; ?>

  </a>

<?php endif; ?>

