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
?>

<?php
if (isset($field_date[LANGUAGE_NONE][0]['value'])) {
  $start_date = $field_date[LANGUAGE_NONE][0]['value'];
}
if (isset($field_date[LANGUAGE_NONE][0]['value2'])) {
  $end_date = $field_date[LANGUAGE_NONE][0]['value2'];
}

// Determine the BEM block
$css_block = drupal_clean_css_identifier($type);

// Determine the BEM modifier
$css_modifier = drupal_clean_css_identifier($view_mode);

// The attributes_array contains classes defined in overviews
if (!isset($attributes_array['class'])) {
  $attributes_array['class'] = array();
}

// Add the wrapper classes to the attributes_array
$attributes_array['class'][] = $css_block . '__item';
$attributes_array['class'][] = $css_block . '__item--' . $css_modifier;

// Add the title classes to the title_attributes_array
$title_attributes_array['class'][] = 'item-title';
$title_attributes_array['class'][] = $css_block . '__item-title';
$title_attributes_array['class'][] = $css_block . '__item-title--' . $css_modifier;

// Add the title link classes to the link_attributes_array
$link_attributes_array = array();
$link_attributes_array['class'][] = 'item-link';
$link_attributes_array['class'][] = $css_block . '__item-link';
$link_attributes_array['class'][] = $css_block . '__item-link--' . $css_modifier;
$link_attributes_array['itemprop'][] = 'url';

// Add the read more link classes to the readmore_attributes_array
$readmore_attributes_array['class'][] = 'btn';
$readmore_attributes_array['class'][] = 'btn--more';
$readmore_attributes_array['class'][] = 'btn--small';
$readmore_attributes_array['itemprop'][] = 'url';
?>

<article role="article" itemscope
         itemtype="http://schema.org/EducationEvent"
  <?php print drupal_attributes($attributes_array); ?>>


  <div class="events__tags">
    <?php print render($content['field_tags']); ?>
  </div>

  <div class="events__date events__date--<?php print $css_modifier; ?>">
    <span class="events__date--start" itemprop="startDate"
          content="<?php print format_date($start_date, 'custom', 'c'); ?>">
      <span class="events__day">
        <?php print format_date($start_date, 'custom', 'j'); ?>
      </span>
      <span class="events__month">
        <?php print format_date($start_date, 'custom', 'M'); ?>
      </span>
      <span class="events__year">
        <?php print format_date($start_date, 'custom', 'Y'); ?>
      </span>
    </span>
    <?php if (format_date($start_date, 'custom', 'Ymd') !== format_date($end_date, 'custom', 'Ymd')): ?>
      -
      <span class="events__date--end" itemprop="endDate"
            content="<?php print format_date($end_date, 'custom', 'c'); ?>">
        <span class="events__day">
          <?php print format_date($end_date, 'custom', 'j'); ?>
        </span>
        <span class="events__month">
          <?php print format_date($end_date, 'custom', 'M'); ?>
        </span>
        <span class="events__year">
          <?php print format_date($end_date, 'custom', 'Y'); ?>
        </span>
      </span>
    <?php endif; ?>
  </div>

  <div itemprop="name"
    <?php print drupal_attributes($title_attributes_array); ?>>
    <?php print l(
      $title,
      'node/' . $nid, array(
        'attributes' => $link_attributes_array,
        'html' => TRUE,
      )
    ); ?>
  </div>

  <?php print render($content); ?>

  <div class="layout__btn">
    <?php print l(
      t(
        'Read more<span class="element-invisible"> about @title</span>',
        array('@title' => $title)
      ),
      'node/' . $nid,
      array(
        'attributes' => $readmore_attributes_array,
        'html' => TRUE,
      )
    ); ?>
  </div>

</article>
