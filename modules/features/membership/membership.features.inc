<?php
/**
 * @file
 * membership.features.inc
 */

/**
 * Implements hook_default_entityform_type().
 */
function membership_default_entityform_type() {
  $items = array();
  $items['membership'] = entity_import('entityform_type', '{
    "type" : "membership",
    "label" : "Membership",
    "data" : {
      "draftable" : 0,
      "draft_redirect_path" : "",
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "full_html" },
      "submit_button_text" : "Send application form",
      "submit_confirm_msg" : "",
      "your_submissions" : "",
      "disallow_resubmit_msg" : "",
      "delete_confirm_msg" : "",
      "page_title_view" : "",
      "preview_page" : 0,
      "submission_page_title" : "We are glad you have joined us.",
      "submission_text" : {
        "value" : "\\u003Cp\\u003EYour interest in our organisation does make us happy.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EIn return we\\u0027ll give you a nice discount on our\\u0026nbsp;Belgian Hand Therapists events.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EKind regards\\u003Cbr \\/\\u003E\\r\\nV\\u00e9ronique Bertrandt\\u003C\\/p\\u003E\\r\\n",
        "format" : "full_html"
      },
      "submission_show_submitted" : 0,
      "submissions_view" : "default",
      "user_submissions_view" : "default",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "1" : "1", "2" : "2", "4" : 0, "3" : 0 },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : {
        "value" : "\\u003Cp\\u003EBecome a member, get informed about our latest news and receive discounts on our BHT conferences.\\u003C\\/p\\u003E\\r\\n",
        "format" : "full_html"
      }
    },
    "weight" : "0",
    "paths" : {
      "submit" : {
        "source" : "eform\\/submit\\/membership",
        "alias" : "member\\/membership",
        "language" : "und"
      },
      "confirm" : {
        "source" : "eform\\/membership\\/confirm",
        "alias" : "member\\/membership\\/thank-you",
        "language" : "und"
      }
    }
  }');
  return $items;
}
