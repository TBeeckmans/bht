/*
 * This file is used/requested by the 'Styles' button.
 * The 'Styles' button is not enabled by default in DrupalFull and DrupalFiltered toolbars.
 */
if(typeof(CKEDITOR) !== 'undefined') {
    CKEDITOR.addStylesSet( 'drupal',
    [
            /* Block Styles */

            // These styles are already available in the "Format" drop-down list, so they are
            // not needed here by default. You may enable them to avoid placing the
            // "Format" drop-down list in the toolbar, maintaining the same features.
            { name : 'Paragraph'    , element : 'p' },
            { name : 'Intro'        , element : 'p', attributes: { 'class': 'intro' } },
            { name : 'Heading 1'    , element : 'div', attributes: { 'class': 'page-title--intro' } },
            { name : 'Heading 2'    , element : 'h2' },
            { name : 'Heading 3'    , element : 'h3' },
            { name : 'CTA Heading'  , element : 'div', attributes: { 'class': 'block__title' } },
            { name : 'Quote'        , element : 'blockquote' },

            // Buttons
            { name : 'Button default'   , element : 'a', attributes: { 'class': 'btn btn--default' } },
            { name : 'Button more'      , element : 'a', attributes: { 'class': 'btn btn--more' } },
            { name : 'Button link'      , element : 'a', attributes: { 'class': 'btn btn--link' } },

            /* Inline Styles */

            // These are core styles available as toolbar buttons. You may opt enabling
            // some of them in the "Styles" drop-down list, removing them from the toolbar.
            /*
            { name : 'Strong'     , element : 'strong', overrides : 'b' },
            { name : 'Emphasis'     , element : 'em'  , overrides : 'i' },
            { name : 'Underline'    , element : 'u' },
            { name : 'Strikethrough'  , element : 'strike' },
            { name : 'Subscript'    , element : 'sub' },
            { name : 'Superscript'    , element : 'sup' },
            */

            // { name : 'Marker: Yellow' , element : 'span', styles : { 'background-color' : 'Yellow' } },
            // { name : 'Marker: Green'  , element : 'span', styles : { 'background-color' : 'Lime' } },

            // { name : 'Big'        , element : 'big' },
            // { name : 'Small'      , element : 'small' },
            // { name : 'Typewriter'   , element : 'tt' },

            // { name : 'Computer Code'  , element : 'code' },
            // { name : 'Keyboard Phrase'  , element : 'kbd' },
            // { name : 'Sample Text'    , element : 'samp' },
            // { name : 'Variable'     , element : 'var' },

            // { name : 'Deleted Text'   , element : 'del' },
            // { name : 'Inserted Text'  , element : 'ins' },

            // { name : 'Cited Work'   , element : 'cite' },
            // { name : 'Inline Quotation' , element : 'q' },

            // { name : 'Language: RTL'  , element : 'span', attributes : { 'dir' : 'rtl' } },
            // { name : 'Language: LTR'  , element : 'span', attributes : { 'dir' : 'ltr' } },

            /* Object Styles */
            
            // Clear
            { name : 'Clear'   , element : ['div', 'p', 'h2', 'h3'], attributes: { 'class': 'clear' } },
    ]);
}
