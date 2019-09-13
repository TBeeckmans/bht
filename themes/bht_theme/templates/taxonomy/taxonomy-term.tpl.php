<?php theme_helper(__FILE__); ?>

<?php
/**
 * @file
 * Default theme implementation to display a term.
 *
 * Available variables:
 * - $name: (deprecated) The unsanitized name of the term. Use $term_name
 *   instead.
 * - $content: An array of items for the content of the term (fields and
 *   description). Use render($content) to print them all, or print a subset
 *   such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $term_url: Direct URL of the current term.
 * - $term_name: Name of the current term.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - taxonomy-term: The current template type, i.e., "theming hook".
 *   - vocabulary-[vocabulary-name]: The vocabulary to which the term belongs to.
 *     For example, if the term is a "Tag" it would result in "vocabulary-tag".
 *
 * Other variables:
 * - $term: Full term object. Contains data that may not be safe.
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $page: Flag for the full page state.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the term. Increments each time it's output.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_taxonomy_term()
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
  hide($content['field_intro']);
  $bIntro = TRUE;
}
?>


<?php
// Determine the BEM block name
$css_block = drupal_clean_css_identifier($vocabulary_machine_name);

// Determine the BEM modifier name
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
elseif ($view_mode === 'tax_children_teaser') {
  $attributes_array['class'][] = 'child-item';
  $attributes_array['class'][] = $css_block . '__child-item';
  $attributes_array['class'][] = $css_block . '__child-item--' . $css_modifier;
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


  <?php if ($page): ?>

    <?php if ($bIntro): ?>
      <div class="layout__intro">

        <h1 itemprop="name"
          <?php print drupal_attributes($title_attributes_array); ?>>
          <?php print $name; ?>
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
      <?php print $name; ?>
    </h1>

    <?php endif; ?>

    <?php print render($content); ?>

  <?php else: ?>

    <div itemprop="name"
      <?php print drupal_attributes($title_attributes_array); ?>>
      <?php print l(
        $name,
        'taxonomy/term/' . $tid,
        array(
          'attributes' => $link_attributes_array,
          'html' => TRUE
        )
      ); ?>
    </div>

    <?php if ($bIntro): ?>
      <div itemprop="articleBody"
        <?php print drupal_attributes($intro_attributes_array); ?>>
        <?php print render($content['field_intro']); ?>
      </div>
    <?php endif; ?>

    <?php print render($content); ?>

    <p class="layout__btn">
      <?php print l(
        t(
          'Read more<span class="element-invisible"> about @title</span>',
          array('@title' => $name)
        ),
        'taxonomy/term/' . $tid,
        array(
          'attributes' => $readmore_attributes_array,
          'html' => TRUE
        )
      ); ?>
    </p>

  <?php endif; ?>

</article>
