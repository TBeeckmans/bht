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

$bIntro = FALSE;
if (isset($content['field_intro'])) {
  $bIntro = TRUE;
}
?>


<?php
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
  if ($bIntro) {
    $attributes_array['class'][] = 'article--intro';
    $attributes_array['class'][] = $css_block . '__article--intro';
  }
}
elseif ($view_mode !== 'tax_content_teaser') {
  $attributes_array['class'][] = 'content-item';
  $attributes_array['class'][] = 'content-item--' . $css_modifier;
  $attributes_array['class'][] = $css_block . '__content-item';
  $attributes_array['class'][] = $css_block . '__content-item--' . $css_modifier;
}
else {
  $attributes_array['class'][] = $css_block . '__item';
  $attributes_array['class'][] = $css_block . '__item--' . $css_modifier;
}

// Add the title classes to the title_attributes_array
if ($page) {
  $title_attributes_array['class'][] = 'page-title';
  $title_attributes_array['class'][] = $css_block . '__page-title';
  if ($bIntro) {
    $title_attributes_array['class'][] = 'page-title--intro';
    $title_attributes_array['class'][] = $css_block . '__page-title--intro';
  }
}
else {
  $title_attributes_array['class'][] = 'item-title';
  $title_attributes_array['class'][] = $css_block . '__item-title';
  $title_attributes_array['class'][] = $css_block . '__item-title--' . $css_modifier;
}

// Add the title link classes to the link_attributes_array
$link_attributes_array = array();
$link_attributes_array['class'][] = 'item-link';
$link_attributes_array['class'][] = $css_block . '__item-link';
$link_attributes_array['class'][] = $css_block . '__item-link--' . $css_modifier;

// Add the intro link classes to the intro_attributes_array
$intro_attributes_array['class'][] = 'intro';
$intro_attributes_array['class'][] = $css_block . '__intro';
if (!$page) {
  $intro_attributes_array['class'][] = $css_block . '__intro--' . $css_modifier;
}

// Add the read more link classes to the readmore_attributes_array
$readmore_attributes_array['class'][] = 'btn';
$readmore_attributes_array['class'][] = 'btn--more';

?>

<article role="article" itemscope
         itemtype="//schema.org/Article"
  <?php print drupal_attributes($attributes_array); ?>>

  <?php if ($bIntro): ?>
    <div class="layout__intro">

      <h1 itemprop="name"
        <?php print drupal_attributes($title_attributes_array); ?>>
        <?php print $h1; ?>
      </h1>

      <?php if ($bIntro): ?>
        <div <?php print drupal_attributes($intro_attributes_array); ?>>
          <?php print render($content['field_intro']); ?>
        </div>
      <?php endif; ?>

    </div>

  <?php else: ?>

    <h1 itemprop="name"
      <?php print drupal_attributes($title_attributes_array); ?>>
      <?php print $h1; ?>
    </h1>

  <?php endif; ?>

  <?php print render($content); ?>

</article>
