<?php
/**
 * @file
 * Default theme implementation for beans.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) entity label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-{ENTITY_TYPE}
 *   - {ENTITY_TYPE}-{BUNDLE}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */

// Add button class to the link field items
if (isset($content['field_link']) && !empty($content['field_link'])) {
    $links = element_children($content['field_link']);
    if (!empty($links)) {
        foreach ($links as $lid) {
            if (isset($content['field_link'][$lid]['#element']['title'])) {
                if ($content['field_link'][$lid]['#element']['title'] !== $content['field_link'][$lid]['#element']['display_url']) {
                    $content['field_link'][$lid]['#element']['attributes']['class'] = 'btn btn--more';
                }
                else {
                    unset($content['field_link'][$lid]);
                }
            }
            else {
                unset($content['field_link'][$lid]);
            }
        }
    }
}
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php print theme_strip_links(render($content)); ?>
</div>
