<?php
/**
 * @file bht_custom.entities.inc
 *
 * @description
 * Alter entities by adding view modes and/of fields to them
 */



/**
 * Implements hook_entity_info_alter().
 *
 * All properties that are available in hook_entity_info() can be
 * altered here.
 *
 * @param object $entity_info
 *   The entity info array, keyed by entity name.
 *
 * @see hook_entity_info()
 */
function bht_custom_entity_info_alter(&$entity_info) {

  $entity_info['node']['view modes']['promoted'] = array(
    'label' => t('Promoted'),
    'custom settings' => TRUE,
  );
  $entity_info['node']['view modes']['teaser_promoted'] = array(
    'label' => t('Promoted teaser'),
    'custom settings' => TRUE,
  );

  $entity_info['node']['view modes']['logo'] = array(
    'label' => t('Logo'),
    'custom settings' => TRUE,
  );

  $entity_info['node']['view modes']['program'] = array(
    'label' => t('Scientific program'),
    'custom settings' => TRUE,
  );

}



/**
 * Implements hook_field_extra_fields().
 *
 * Exposes "pseudo-field" components on fieldable entities.
 *
 * The user-defined settings (weight, visible) are automatically applied on
 * rendered forms and displayed entities in a #pre_render callback added by
 * field_attach_form() and field_attach_view().
 *
 * @see _field_extra_fields_pre_render()
 * @see hook_field_extra_fields_alter()
 *
 * @return array $extra
 *   A nested array of 'pseudo-field' elements. Each list is nested within the
 *   following keys: entity type, bundle name, context. The keys are the name of
 *   the elements as appearing in the renderable array (either the entity form
 *   or the displayed entity). The value is an associative array:
 *   - label: The human readable name of the element.
 *   - description: A short description of the element contents.
 *   - weight: The default weight of the element.
 *
 * @ingroup field_types
 */
function bht_custom_field_extra_fields() {
  $extra = array();

  $extra['paragraphs_item']['date']['display']['date'] = array(
    'label' => t('Date'),
    'description' => t('CF - Date'),
    'weight' => -99,
  );

  return $extra;
}

/**
 * Implements hook_entity_presave().
 */
function bht_custom_entityform_presave($entity) {
  if ($entity->type == 'elbow_quiz') {
    $percentage = 0;

    $answer1 = 'b';
    $question1 = $entity->field_answers_1[LANGUAGE_NONE][0]['value'];
    if ($question1 == $answer1) {
      $percentage += 20;
    }

    $answer2 = 'c';
    $question2 = $entity->field_answers_2[LANGUAGE_NONE][0]['value'];
    if ($question2 == $answer2) {
      $percentage += 20;
    }

    $answer3 = 'b';
    $question3 = $entity->field_answers_3[LANGUAGE_NONE][0]['value'];
    if ($question3 == $answer3) {
      $percentage += 20;
    }

    $answer4 = 'b';
    $question4 = $entity->field_answers_4[LANGUAGE_NONE][0]['value'];
    if ($question4 == $answer4) {
      $percentage += 20;
    }

    $answer5 = 'a';
    $question5 = $entity->field_answers_5[LANGUAGE_NONE][0]['value'];
    if ($question5 == $answer5) {
      $percentage += 20;
    }

    $entity->field_percentage[LANGUAGE_NONE][0]['value'] = $percentage;
  }
}

/**
 * Alter the render array that will make the confirm page for a single Entityform Type.
 */
function bht_custom_entityform_elbow_quiz_confirm_page_alter(&$render_array, $entityform_type, $entityform_id) {
  $answer_1 = 'b';
  $answer_2 = 'c';
  $answer_3 = 'b';
  $answer_4 = 'b';
  $answer_5 = 'a';

  module_load_include('inc', 'entityform', 'entityform.admin');
  $entity_form_name = 'elbow_quiz';
  $elbow_quiz_form = entityform_form_wrapper(entityform_empty_load($entity_form_name), 'submit', 'embedded');

  $wrapper = entity_metadata_wrapper('entityform', $entityform_id);
  $given_1 = $wrapper->get('field_answers_1')->value();
  $given_2 = $wrapper->get('field_answers_2')->value();
  $given_3 = $wrapper->get('field_answers_3')->value();
  $given_4 = $wrapper->get('field_answers_4')->value();
  $given_5 = $wrapper->get('field_answers_5')->value();

  $correct_answer_1 = $elbow_quiz_form['field_answers_1'][LANGUAGE_NONE][$answer_1]['#title'];
  $your_answer_1 = $elbow_quiz_form['field_answers_1'][LANGUAGE_NONE][$given_1]['#title'];
  $correct_answer_2 = $elbow_quiz_form['field_answers_2'][LANGUAGE_NONE][$answer_2]['#title'];
  $your_answer_2 = $elbow_quiz_form['field_answers_2'][LANGUAGE_NONE][$given_2]['#title'];
  $correct_answer_3 = $elbow_quiz_form['field_answers_3'][LANGUAGE_NONE][$answer_3]['#title'];
  $your_answer_3 = $elbow_quiz_form['field_answers_3'][LANGUAGE_NONE][$given_3]['#title'];
  $correct_answer_4 = $elbow_quiz_form['field_answers_4'][LANGUAGE_NONE][$answer_4]['#title'];
  $your_answer_4 = $elbow_quiz_form['field_answers_4'][LANGUAGE_NONE][$given_4]['#title'];
  $correct_answer_5 = $elbow_quiz_form['field_answers_5'][LANGUAGE_NONE][$answer_5]['#title'];
  $your_answer_5 = $elbow_quiz_form['field_answers_5'][LANGUAGE_NONE][$given_5]['#title'];

  $percentage = $wrapper->get('field_percentage')->value();

  $render_array['result']['title'] = [
    '#type' => 'markup',
    '#markup' => '<p>Jouw score</p>',
  ];
  $render_array['result']['graph'] = [
    '#type' => 'markup',
    '#markup' => '<div class="c100 p' . $percentage . ' blue">
      <span>' . $percentage . '%</span>
      <div class="slice">
        <div class="bar"></div>
        <div class="fill"></div>
      </div>
  </div>'
  ];
  $render_array['#attached']['css'][] = array(
    'data' => '.rect-auto, .c100.p51 .slice, .c100.p52 .slice, .c100.p53 .slice, .c100.p54 .slice, .c100.p55 .slice, .c100.p56 .slice, .c100.p57 .slice, .c100.p58 .slice, .c100.p59 .slice, .c100.p60 .slice, .c100.p61 .slice, .c100.p62 .slice, .c100.p63 .slice, .c100.p64 .slice, .c100.p65 .slice, .c100.p66 .slice, .c100.p67 .slice, .c100.p68 .slice, .c100.p69 .slice, .c100.p70 .slice, .c100.p71 .slice, .c100.p72 .slice, .c100.p73 .slice, .c100.p74 .slice, .c100.p75 .slice, .c100.p76 .slice, .c100.p77 .slice, .c100.p78 .slice, .c100.p79 .slice, .c100.p80 .slice, .c100.p81 .slice, .c100.p82 .slice, .c100.p83 .slice, .c100.p84 .slice, .c100.p85 .slice, .c100.p86 .slice, .c100.p87 .slice, .c100.p88 .slice, .c100.p89 .slice, .c100.p90 .slice, .c100.p91 .slice, .c100.p92 .slice, .c100.p93 .slice, .c100.p94 .slice, .c100.p95 .slice, .c100.p96 .slice, .c100.p97 .slice, .c100.p98 .slice, .c100.p99 .slice, .c100.p100 .slice {
    clip: rect(auto, auto, auto, auto);
  }

.pie, .c100 .bar, .c100.p51 .fill, .c100.p52 .fill, .c100.p53 .fill, .c100.p54 .fill, .c100.p55 .fill, .c100.p56 .fill, .c100.p57 .fill, .c100.p58 .fill, .c100.p59 .fill, .c100.p60 .fill, .c100.p61 .fill, .c100.p62 .fill, .c100.p63 .fill, .c100.p64 .fill, .c100.p65 .fill, .c100.p66 .fill, .c100.p67 .fill, .c100.p68 .fill, .c100.p69 .fill, .c100.p70 .fill, .c100.p71 .fill, .c100.p72 .fill, .c100.p73 .fill, .c100.p74 .fill, .c100.p75 .fill, .c100.p76 .fill, .c100.p77 .fill, .c100.p78 .fill, .c100.p79 .fill, .c100.p80 .fill, .c100.p81 .fill, .c100.p82 .fill, .c100.p83 .fill, .c100.p84 .fill, .c100.p85 .fill, .c100.p86 .fill, .c100.p87 .fill, .c100.p88 .fill, .c100.p89 .fill, .c100.p90 .fill, .c100.p91 .fill, .c100.p92 .fill, .c100.p93 .fill, .c100.p94 .fill, .c100.p95 .fill, .c100.p96 .fill, .c100.p97 .fill, .c100.p98 .fill, .c100.p99 .fill, .c100.p100 .fill {
    position: absolute;
    border: 0.09em solid #000000;
  width: 0.82em;
  height: 0.82em;
  clip: rect(0em, 0.5em, 1em, 0em);
  border-radius: 50%;
  -moz-transform: rotate(0deg);
  -ms-transform: rotate(0deg);
  -webkit-transform: rotate(0deg);
  transform: rotate(0deg);
}

.pie-fill, .c100.p51 .bar:after, .c100.p51 .fill, .c100.p52 .bar:after, .c100.p52 .fill, .c100.p53 .bar:after, .c100.p53 .fill, .c100.p54 .bar:after, .c100.p54 .fill, .c100.p55 .bar:after, .c100.p55 .fill, .c100.p56 .bar:after, .c100.p56 .fill, .c100.p57 .bar:after, .c100.p57 .fill, .c100.p58 .bar:after, .c100.p58 .fill, .c100.p59 .bar:after, .c100.p59 .fill, .c100.p60 .bar:after, .c100.p60 .fill, .c100.p61 .bar:after, .c100.p61 .fill, .c100.p62 .bar:after, .c100.p62 .fill, .c100.p63 .bar:after, .c100.p63 .fill, .c100.p64 .bar:after, .c100.p64 .fill, .c100.p65 .bar:after, .c100.p65 .fill, .c100.p66 .bar:after, .c100.p66 .fill, .c100.p67 .bar:after, .c100.p67 .fill, .c100.p68 .bar:after, .c100.p68 .fill, .c100.p69 .bar:after, .c100.p69 .fill, .c100.p70 .bar:after, .c100.p70 .fill, .c100.p71 .bar:after, .c100.p71 .fill, .c100.p72 .bar:after, .c100.p72 .fill, .c100.p73 .bar:after, .c100.p73 .fill, .c100.p74 .bar:after, .c100.p74 .fill, .c100.p75 .bar:after, .c100.p75 .fill, .c100.p76 .bar:after, .c100.p76 .fill, .c100.p77 .bar:after, .c100.p77 .fill, .c100.p78 .bar:after, .c100.p78 .fill, .c100.p79 .bar:after, .c100.p79 .fill, .c100.p80 .bar:after, .c100.p80 .fill, .c100.p81 .bar:after, .c100.p81 .fill, .c100.p82 .bar:after, .c100.p82 .fill, .c100.p83 .bar:after, .c100.p83 .fill, .c100.p84 .bar:after, .c100.p84 .fill, .c100.p85 .bar:after, .c100.p85 .fill, .c100.p86 .bar:after, .c100.p86 .fill, .c100.p87 .bar:after, .c100.p87 .fill, .c100.p88 .bar:after, .c100.p88 .fill, .c100.p89 .bar:after, .c100.p89 .fill, .c100.p90 .bar:after, .c100.p90 .fill, .c100.p91 .bar:after, .c100.p91 .fill, .c100.p92 .bar:after, .c100.p92 .fill, .c100.p93 .bar:after, .c100.p93 .fill, .c100.p94 .bar:after, .c100.p94 .fill, .c100.p95 .bar:after, .c100.p95 .fill, .c100.p96 .bar:after, .c100.p96 .fill, .c100.p97 .bar:after, .c100.p97 .fill, .c100.p98 .bar:after, .c100.p98 .fill, .c100.p99 .bar:after, .c100.p99 .fill, .c100.p100 .bar:after, .c100.p100 .fill {
    -moz-transform: rotate(180deg);
  -ms-transform: rotate(180deg);
  -webkit-transform: rotate(180deg);
  transform: rotate(180deg);
}

.wrapper {
    width: 1200px;
  margin: 0 auto;
}

.c100 {
    position: relative;
    font-size: 160px;
  width: 1em;
  height: 1em;
  border-radius: 50%;
  float: left;
  margin: 0.1em;
  background-color: #dfe8ed;
}
.c100 *, .c100 *:before, .c100 *:after {
    -moz-box-sizing: content-box;
  -webkit-box-sizing: content-box;
  box-sizing: content-box;
}
.c100 > span {
    position: absolute;
    width: 100%;
    z-index: 1;
  left: 0;
  top: 0;
  width: 5em;
  line-height: 5em;
  font-size: 0.2em;
  color: #3c4761;
  display: block;
  text-align: center;
  white-space: nowrap;
  -moz-transition-property: all;
  -o-transition-property: all;
  -webkit-transition-property: all;
  transition-property: all;
  -moz-transition-duration: 0.2s;
  -o-transition-duration: 0.2s;
  -webkit-transition-duration: 0.2s;
  transition-duration: 0.2s;
  -moz-transition-timing-function: ease-out;
  -o-transition-timing-function: ease-out;
  -webkit-transition-timing-function: ease-out;
  transition-timing-function: ease-out;
}
.c100:after {
    position: absolute;
    top: 0.09em;
  left: 0.09em;
  display: block;
  content: " ";
  border-radius: 50%;
  background-color: #ffffff;
  width: 0.82em;
  height: 0.82em;
  -moz-transition-property: all;
  -o-transition-property: all;
  -webkit-transition-property: all;
  transition-property: all;
  -moz-transition-duration: 0.2s;
  -o-transition-duration: 0.2s;
  -webkit-transition-duration: 0.2s;
  transition-duration: 0.2s;
  -moz-transition-timing-function: ease-in;
  -o-transition-timing-function: ease-in;
  -webkit-transition-timing-function: ease-in;
  transition-timing-function: ease-in;
}
.c100 .slice {
    position: absolute;
    width: 1em;
  height: 1em;
  clip: rect(0em, 1em, 1em, 0.5em);
}
.c100.p1 .bar {
    -moz-transform: rotate(3.6deg);
  -ms-transform: rotate(3.6deg);
  -webkit-transform: rotate(3.6deg);
  transform: rotate(3.6deg);
}
.c100.p2 .bar {
    -moz-transform: rotate(7.2deg);
  -ms-transform: rotate(7.2deg);
  -webkit-transform: rotate(7.2deg);
  transform: rotate(7.2deg);
}
.c100.p3 .bar {
    -moz-transform: rotate(10.8deg);
  -ms-transform: rotate(10.8deg);
  -webkit-transform: rotate(10.8deg);
  transform: rotate(10.8deg);
}
.c100.p4 .bar {
    -moz-transform: rotate(14.4deg);
  -ms-transform: rotate(14.4deg);
  -webkit-transform: rotate(14.4deg);
  transform: rotate(14.4deg);
}
.c100.p5 .bar {
    -moz-transform: rotate(18deg);
  -ms-transform: rotate(18deg);
  -webkit-transform: rotate(18deg);
  transform: rotate(18deg);
}
.c100.p6 .bar {
    -moz-transform: rotate(21.6deg);
  -ms-transform: rotate(21.6deg);
  -webkit-transform: rotate(21.6deg);
  transform: rotate(21.6deg);
}
.c100.p7 .bar {
    -moz-transform: rotate(25.2deg);
  -ms-transform: rotate(25.2deg);
  -webkit-transform: rotate(25.2deg);
  transform: rotate(25.2deg);
}
.c100.p8 .bar {
    -moz-transform: rotate(28.8deg);
  -ms-transform: rotate(28.8deg);
  -webkit-transform: rotate(28.8deg);
  transform: rotate(28.8deg);
}
.c100.p9 .bar {
    -moz-transform: rotate(32.4deg);
  -ms-transform: rotate(32.4deg);
  -webkit-transform: rotate(32.4deg);
  transform: rotate(32.4deg);
}
.c100.p10 .bar {
    -moz-transform: rotate(36deg);
  -ms-transform: rotate(36deg);
  -webkit-transform: rotate(36deg);
  transform: rotate(36deg);
}
.c100.p11 .bar {
    -moz-transform: rotate(39.6deg);
  -ms-transform: rotate(39.6deg);
  -webkit-transform: rotate(39.6deg);
  transform: rotate(39.6deg);
}
.c100.p12 .bar {
    -moz-transform: rotate(43.2deg);
  -ms-transform: rotate(43.2deg);
  -webkit-transform: rotate(43.2deg);
  transform: rotate(43.2deg);
}
.c100.p13 .bar {
    -moz-transform: rotate(46.8deg);
  -ms-transform: rotate(46.8deg);
  -webkit-transform: rotate(46.8deg);
  transform: rotate(46.8deg);
}
.c100.p14 .bar {
    -moz-transform: rotate(50.4deg);
  -ms-transform: rotate(50.4deg);
  -webkit-transform: rotate(50.4deg);
  transform: rotate(50.4deg);
}
.c100.p15 .bar {
    -moz-transform: rotate(54deg);
  -ms-transform: rotate(54deg);
  -webkit-transform: rotate(54deg);
  transform: rotate(54deg);
}
.c100.p16 .bar {
    -moz-transform: rotate(57.6deg);
  -ms-transform: rotate(57.6deg);
  -webkit-transform: rotate(57.6deg);
  transform: rotate(57.6deg);
}
.c100.p17 .bar {
    -moz-transform: rotate(61.2deg);
  -ms-transform: rotate(61.2deg);
  -webkit-transform: rotate(61.2deg);
  transform: rotate(61.2deg);
}
.c100.p18 .bar {
    -moz-transform: rotate(64.8deg);
  -ms-transform: rotate(64.8deg);
  -webkit-transform: rotate(64.8deg);
  transform: rotate(64.8deg);
}
.c100.p19 .bar {
    -moz-transform: rotate(68.4deg);
  -ms-transform: rotate(68.4deg);
  -webkit-transform: rotate(68.4deg);
  transform: rotate(68.4deg);
}
.c100.p20 .bar {
    -moz-transform: rotate(72deg);
  -ms-transform: rotate(72deg);
  -webkit-transform: rotate(72deg);
  transform: rotate(72deg);
}
.c100.p21 .bar {
    -moz-transform: rotate(75.6deg);
  -ms-transform: rotate(75.6deg);
  -webkit-transform: rotate(75.6deg);
  transform: rotate(75.6deg);
}
.c100.p22 .bar {
    -moz-transform: rotate(79.2deg);
  -ms-transform: rotate(79.2deg);
  -webkit-transform: rotate(79.2deg);
  transform: rotate(79.2deg);
}
.c100.p23 .bar {
    -moz-transform: rotate(82.8deg);
  -ms-transform: rotate(82.8deg);
  -webkit-transform: rotate(82.8deg);
  transform: rotate(82.8deg);
}
.c100.p24 .bar {
    -moz-transform: rotate(86.4deg);
  -ms-transform: rotate(86.4deg);
  -webkit-transform: rotate(86.4deg);
  transform: rotate(86.4deg);
}
.c100.p25 .bar {
    -moz-transform: rotate(90deg);
  -ms-transform: rotate(90deg);
  -webkit-transform: rotate(90deg);
  transform: rotate(90deg);
}
.c100.p26 .bar {
    -moz-transform: rotate(93.6deg);
  -ms-transform: rotate(93.6deg);
  -webkit-transform: rotate(93.6deg);
  transform: rotate(93.6deg);
}
.c100.p27 .bar {
    -moz-transform: rotate(97.2deg);
  -ms-transform: rotate(97.2deg);
  -webkit-transform: rotate(97.2deg);
  transform: rotate(97.2deg);
}
.c100.p28 .bar {
    -moz-transform: rotate(100.8deg);
  -ms-transform: rotate(100.8deg);
  -webkit-transform: rotate(100.8deg);
  transform: rotate(100.8deg);
}
.c100.p29 .bar {
    -moz-transform: rotate(104.4deg);
  -ms-transform: rotate(104.4deg);
  -webkit-transform: rotate(104.4deg);
  transform: rotate(104.4deg);
}
.c100.p30 .bar {
    -moz-transform: rotate(108deg);
  -ms-transform: rotate(108deg);
  -webkit-transform: rotate(108deg);
  transform: rotate(108deg);
}
.c100.p31 .bar {
    -moz-transform: rotate(111.6deg);
  -ms-transform: rotate(111.6deg);
  -webkit-transform: rotate(111.6deg);
  transform: rotate(111.6deg);
}
.c100.p32 .bar {
    -moz-transform: rotate(115.2deg);
  -ms-transform: rotate(115.2deg);
  -webkit-transform: rotate(115.2deg);
  transform: rotate(115.2deg);
}
.c100.p33 .bar {
    -moz-transform: rotate(118.8deg);
  -ms-transform: rotate(118.8deg);
  -webkit-transform: rotate(118.8deg);
  transform: rotate(118.8deg);
}
.c100.p34 .bar {
    -moz-transform: rotate(122.4deg);
  -ms-transform: rotate(122.4deg);
  -webkit-transform: rotate(122.4deg);
  transform: rotate(122.4deg);
}
.c100.p35 .bar {
    -moz-transform: rotate(126deg);
  -ms-transform: rotate(126deg);
  -webkit-transform: rotate(126deg);
  transform: rotate(126deg);
}
.c100.p36 .bar {
    -moz-transform: rotate(129.6deg);
  -ms-transform: rotate(129.6deg);
  -webkit-transform: rotate(129.6deg);
  transform: rotate(129.6deg);
}
.c100.p37 .bar {
    -moz-transform: rotate(133.2deg);
  -ms-transform: rotate(133.2deg);
  -webkit-transform: rotate(133.2deg);
  transform: rotate(133.2deg);
}
.c100.p38 .bar {
    -moz-transform: rotate(136.8deg);
  -ms-transform: rotate(136.8deg);
  -webkit-transform: rotate(136.8deg);
  transform: rotate(136.8deg);
}
.c100.p39 .bar {
    -moz-transform: rotate(140.4deg);
  -ms-transform: rotate(140.4deg);
  -webkit-transform: rotate(140.4deg);
  transform: rotate(140.4deg);
}
.c100.p40 .bar {
    -moz-transform: rotate(144deg);
  -ms-transform: rotate(144deg);
  -webkit-transform: rotate(144deg);
  transform: rotate(144deg);
}
.c100.p41 .bar {
    -moz-transform: rotate(147.6deg);
  -ms-transform: rotate(147.6deg);
  -webkit-transform: rotate(147.6deg);
  transform: rotate(147.6deg);
}
.c100.p42 .bar {
    -moz-transform: rotate(151.2deg);
  -ms-transform: rotate(151.2deg);
  -webkit-transform: rotate(151.2deg);
  transform: rotate(151.2deg);
}
.c100.p43 .bar {
    -moz-transform: rotate(154.8deg);
  -ms-transform: rotate(154.8deg);
  -webkit-transform: rotate(154.8deg);
  transform: rotate(154.8deg);
}
.c100.p44 .bar {
    -moz-transform: rotate(158.4deg);
  -ms-transform: rotate(158.4deg);
  -webkit-transform: rotate(158.4deg);
  transform: rotate(158.4deg);
}
.c100.p45 .bar {
    -moz-transform: rotate(162deg);
  -ms-transform: rotate(162deg);
  -webkit-transform: rotate(162deg);
  transform: rotate(162deg);
}
.c100.p46 .bar {
    -moz-transform: rotate(165.6deg);
  -ms-transform: rotate(165.6deg);
  -webkit-transform: rotate(165.6deg);
  transform: rotate(165.6deg);
}
.c100.p47 .bar {
    -moz-transform: rotate(169.2deg);
  -ms-transform: rotate(169.2deg);
  -webkit-transform: rotate(169.2deg);
  transform: rotate(169.2deg);
}
.c100.p48 .bar {
    -moz-transform: rotate(172.8deg);
  -ms-transform: rotate(172.8deg);
  -webkit-transform: rotate(172.8deg);
  transform: rotate(172.8deg);
}
.c100.p49 .bar {
    -moz-transform: rotate(176.4deg);
  -ms-transform: rotate(176.4deg);
  -webkit-transform: rotate(176.4deg);
  transform: rotate(176.4deg);
}
.c100.p50 .bar {
    -moz-transform: rotate(180deg);
  -ms-transform: rotate(180deg);
  -webkit-transform: rotate(180deg);
  transform: rotate(180deg);
}
.c100.p51 .bar {
    -moz-transform: rotate(183.6deg);
  -ms-transform: rotate(183.6deg);
  -webkit-transform: rotate(183.6deg);
  transform: rotate(183.6deg);
}
.c100.p52 .bar {
    -moz-transform: rotate(187.2deg);
  -ms-transform: rotate(187.2deg);
  -webkit-transform: rotate(187.2deg);
  transform: rotate(187.2deg);
}
.c100.p53 .bar {
    -moz-transform: rotate(190.8deg);
  -ms-transform: rotate(190.8deg);
  -webkit-transform: rotate(190.8deg);
  transform: rotate(190.8deg);
}
.c100.p54 .bar {
    -moz-transform: rotate(194.4deg);
  -ms-transform: rotate(194.4deg);
  -webkit-transform: rotate(194.4deg);
  transform: rotate(194.4deg);
}
.c100.p55 .bar {
    -moz-transform: rotate(198deg);
  -ms-transform: rotate(198deg);
  -webkit-transform: rotate(198deg);
  transform: rotate(198deg);
}
.c100.p56 .bar {
    -moz-transform: rotate(201.6deg);
  -ms-transform: rotate(201.6deg);
  -webkit-transform: rotate(201.6deg);
  transform: rotate(201.6deg);
}
.c100.p57 .bar {
    -moz-transform: rotate(205.2deg);
  -ms-transform: rotate(205.2deg);
  -webkit-transform: rotate(205.2deg);
  transform: rotate(205.2deg);
}
.c100.p58 .bar {
    -moz-transform: rotate(208.8deg);
  -ms-transform: rotate(208.8deg);
  -webkit-transform: rotate(208.8deg);
  transform: rotate(208.8deg);
}
.c100.p59 .bar {
    -moz-transform: rotate(212.4deg);
  -ms-transform: rotate(212.4deg);
  -webkit-transform: rotate(212.4deg);
  transform: rotate(212.4deg);
}
.c100.p60 .bar {
    -moz-transform: rotate(216deg);
  -ms-transform: rotate(216deg);
  -webkit-transform: rotate(216deg);
  transform: rotate(216deg);
}
.c100.p61 .bar {
    -moz-transform: rotate(219.6deg);
  -ms-transform: rotate(219.6deg);
  -webkit-transform: rotate(219.6deg);
  transform: rotate(219.6deg);
}
.c100.p62 .bar {
    -moz-transform: rotate(223.2deg);
  -ms-transform: rotate(223.2deg);
  -webkit-transform: rotate(223.2deg);
  transform: rotate(223.2deg);
}
.c100.p63 .bar {
    -moz-transform: rotate(226.8deg);
  -ms-transform: rotate(226.8deg);
  -webkit-transform: rotate(226.8deg);
  transform: rotate(226.8deg);
}
.c100.p64 .bar {
    -moz-transform: rotate(230.4deg);
  -ms-transform: rotate(230.4deg);
  -webkit-transform: rotate(230.4deg);
  transform: rotate(230.4deg);
}
.c100.p65 .bar {
    -moz-transform: rotate(234deg);
  -ms-transform: rotate(234deg);
  -webkit-transform: rotate(234deg);
  transform: rotate(234deg);
}
.c100.p66 .bar {
    -moz-transform: rotate(237.6deg);
  -ms-transform: rotate(237.6deg);
  -webkit-transform: rotate(237.6deg);
  transform: rotate(237.6deg);
}
.c100.p67 .bar {
    -moz-transform: rotate(241.2deg);
  -ms-transform: rotate(241.2deg);
  -webkit-transform: rotate(241.2deg);
  transform: rotate(241.2deg);
}
.c100.p68 .bar {
    -moz-transform: rotate(244.8deg);
  -ms-transform: rotate(244.8deg);
  -webkit-transform: rotate(244.8deg);
  transform: rotate(244.8deg);
}
.c100.p69 .bar {
    -moz-transform: rotate(248.4deg);
  -ms-transform: rotate(248.4deg);
  -webkit-transform: rotate(248.4deg);
  transform: rotate(248.4deg);
}
.c100.p70 .bar {
    -moz-transform: rotate(252deg);
  -ms-transform: rotate(252deg);
  -webkit-transform: rotate(252deg);
  transform: rotate(252deg);
}
.c100.p71 .bar {
    -moz-transform: rotate(255.6deg);
  -ms-transform: rotate(255.6deg);
  -webkit-transform: rotate(255.6deg);
  transform: rotate(255.6deg);
}
.c100.p72 .bar {
    -moz-transform: rotate(259.2deg);
  -ms-transform: rotate(259.2deg);
  -webkit-transform: rotate(259.2deg);
  transform: rotate(259.2deg);
}
.c100.p73 .bar {
    -moz-transform: rotate(262.8deg);
  -ms-transform: rotate(262.8deg);
  -webkit-transform: rotate(262.8deg);
  transform: rotate(262.8deg);
}
.c100.p74 .bar {
    -moz-transform: rotate(266.4deg);
  -ms-transform: rotate(266.4deg);
  -webkit-transform: rotate(266.4deg);
  transform: rotate(266.4deg);
}
.c100.p75 .bar {
    -moz-transform: rotate(270deg);
  -ms-transform: rotate(270deg);
  -webkit-transform: rotate(270deg);
  transform: rotate(270deg);
}
.c100.p76 .bar {
    -moz-transform: rotate(273.6deg);
  -ms-transform: rotate(273.6deg);
  -webkit-transform: rotate(273.6deg);
  transform: rotate(273.6deg);
}
.c100.p77 .bar {
    -moz-transform: rotate(277.2deg);
  -ms-transform: rotate(277.2deg);
  -webkit-transform: rotate(277.2deg);
  transform: rotate(277.2deg);
}
.c100.p78 .bar {
    -moz-transform: rotate(280.8deg);
  -ms-transform: rotate(280.8deg);
  -webkit-transform: rotate(280.8deg);
  transform: rotate(280.8deg);
}
.c100.p79 .bar {
    -moz-transform: rotate(284.4deg);
  -ms-transform: rotate(284.4deg);
  -webkit-transform: rotate(284.4deg);
  transform: rotate(284.4deg);
}
.c100.p80 .bar {
    -moz-transform: rotate(288deg);
  -ms-transform: rotate(288deg);
  -webkit-transform: rotate(288deg);
  transform: rotate(288deg);
}
.c100.p81 .bar {
    -moz-transform: rotate(291.6deg);
  -ms-transform: rotate(291.6deg);
  -webkit-transform: rotate(291.6deg);
  transform: rotate(291.6deg);
}
.c100.p82 .bar {
    -moz-transform: rotate(295.2deg);
  -ms-transform: rotate(295.2deg);
  -webkit-transform: rotate(295.2deg);
  transform: rotate(295.2deg);
}
.c100.p83 .bar {
    -moz-transform: rotate(298.8deg);
  -ms-transform: rotate(298.8deg);
  -webkit-transform: rotate(298.8deg);
  transform: rotate(298.8deg);
}
.c100.p84 .bar {
    -moz-transform: rotate(302.4deg);
  -ms-transform: rotate(302.4deg);
  -webkit-transform: rotate(302.4deg);
  transform: rotate(302.4deg);
}
.c100.p85 .bar {
    -moz-transform: rotate(306deg);
  -ms-transform: rotate(306deg);
  -webkit-transform: rotate(306deg);
  transform: rotate(306deg);
}
.c100.p86 .bar {
    -moz-transform: rotate(309.6deg);
  -ms-transform: rotate(309.6deg);
  -webkit-transform: rotate(309.6deg);
  transform: rotate(309.6deg);
}
.c100.p87 .bar {
    -moz-transform: rotate(313.2deg);
  -ms-transform: rotate(313.2deg);
  -webkit-transform: rotate(313.2deg);
  transform: rotate(313.2deg);
}
.c100.p88 .bar {
    -moz-transform: rotate(316.8deg);
  -ms-transform: rotate(316.8deg);
  -webkit-transform: rotate(316.8deg);
  transform: rotate(316.8deg);
}
.c100.p89 .bar {
    -moz-transform: rotate(320.4deg);
  -ms-transform: rotate(320.4deg);
  -webkit-transform: rotate(320.4deg);
  transform: rotate(320.4deg);
}
.c100.p90 .bar {
    -moz-transform: rotate(324deg);
  -ms-transform: rotate(324deg);
  -webkit-transform: rotate(324deg);
  transform: rotate(324deg);
}
.c100.p91 .bar {
    -moz-transform: rotate(327.6deg);
  -ms-transform: rotate(327.6deg);
  -webkit-transform: rotate(327.6deg);
  transform: rotate(327.6deg);
}
.c100.p92 .bar {
    -moz-transform: rotate(331.2deg);
  -ms-transform: rotate(331.2deg);
  -webkit-transform: rotate(331.2deg);
  transform: rotate(331.2deg);
}
.c100.p93 .bar {
    -moz-transform: rotate(334.8deg);
  -ms-transform: rotate(334.8deg);
  -webkit-transform: rotate(334.8deg);
  transform: rotate(334.8deg);
}
.c100.p94 .bar {
    -moz-transform: rotate(338.4deg);
  -ms-transform: rotate(338.4deg);
  -webkit-transform: rotate(338.4deg);
  transform: rotate(338.4deg);
}
.c100.p95 .bar {
    -moz-transform: rotate(342deg);
  -ms-transform: rotate(342deg);
  -webkit-transform: rotate(342deg);
  transform: rotate(342deg);
}
.c100.p96 .bar {
    -moz-transform: rotate(345.6deg);
  -ms-transform: rotate(345.6deg);
  -webkit-transform: rotate(345.6deg);
  transform: rotate(345.6deg);
}
.c100.p97 .bar {
    -moz-transform: rotate(349.2deg);
  -ms-transform: rotate(349.2deg);
  -webkit-transform: rotate(349.2deg);
  transform: rotate(349.2deg);
}
.c100.p98 .bar {
    -moz-transform: rotate(352.8deg);
  -ms-transform: rotate(352.8deg);
  -webkit-transform: rotate(352.8deg);
  transform: rotate(352.8deg);
}
.c100.p99 .bar {
    -moz-transform: rotate(356.4deg);
  -ms-transform: rotate(356.4deg);
  -webkit-transform: rotate(356.4deg);
  transform: rotate(356.4deg);
}
.c100.p100 .bar {
    -moz-transform: rotate(360deg);
  -ms-transform: rotate(360deg);
  -webkit-transform: rotate(360deg);
  transform: rotate(360deg);
}
.c100.blue .bar, .c100.blue .fill {
    border-color: #30bae7 !important;
}
.c100.blue:hover > span {
    color: #3c4761;
  }
',
    'type' => 'inline',
  );

  $render_array['question_1'] = $elbow_quiz_form['field_question_1'];
  $render_array['question_1']['your_answer_1'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="yours">Jouw antwoord:</span> ' . $your_answer_1 . '</div>',
  ];
  $render_array['question_1']['correct_answer_1'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="correct">Correct antwoord:</span> ' . $correct_answer_1 . '</div>',
  ];
  $render_array['question_2'] = $elbow_quiz_form['field_question_2'];
  $render_array['question_2']['your_answer_2'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="yours">Jouw antwoord:</span> ' . $your_answer_2 . '</div>',
  ];
  $render_array['question_2']['correct_answer_2'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="correct">Correct antwoord:</span> ' . $correct_answer_2 . '</div>',
  ];
  $render_array['question_3'] = $elbow_quiz_form['field_question_3'];
  $render_array['question_3']['your_answer_3'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="yours">Jouw antwoord:</span> ' . $your_answer_3 . '</div>',
  ];
  $render_array['question_3']['correct_answer_3'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="correct">Correct antwoord:</span> ' . $correct_answer_3 . '</div>',
  ];
  $render_array['question_4'] = $elbow_quiz_form['field_question_4'];
  $render_array['question_4']['your_answer_4'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="yours">Jouw antwoord:</span> ' . $your_answer_4 . '</div>',
  ];
  $render_array['question_4']['correct_answer_4'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="correct">Correct antwoord:</span> ' . $correct_answer_4 . '</div>',
  ];
  $render_array['question_5'] = $elbow_quiz_form['field_question_5'];
  $render_array['question_5']['your_answer_5'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="yours">Jouw antwoord:</span> ' . $your_answer_5 . '</div>',
  ];
  $render_array['question_5']['correct_answer_5'] = [
    '#type' => 'markup',
    '#markup' => '<div><span class="correct">Correct antwoord:</span> ' . $correct_answer_5 . '</div>',
  ];

  $render_array['end'] = [
    '#type' => 'markup',
    '#markup' => '<p>&nbsp;</p>',
  ];
}

/**
 * Implements hook_node_presave().
 *
 * Act on a node being inserted or updated.
 *
 * This hook is invoked from node_save() before the node is saved to the
 * database.
 *
 * @param $node
 *   The node that is being inserted or updated.
 *
 * @ingroup node_api_hooks
 */
/*function bht_custom_node_presave($node) {
  $node->foo = 'bar';
}*/



/**
 * Implements hook_node_view().
 *
 * Act on a node that is being assembled before rendering.
 *
 * The module may add elements to $node->content prior to rendering. This hook
 * will be called after hook_view(). The structure of $node->content is a
 * renderable array as expected by drupal_render().
 *
 * @description
 *   Add the extra field content in bht_custom.theme.inc
 *
 * @param $node
 *   The node that is being assembled for rendering.
 * @param $view_mode
 *   The $view_mode parameter from node_view().
 * @param $langcode
 *   The language code used for rendering.
 *
 * @see hook_entity_view()
 *
 * @ingroup node_api_hooks
 */
function bht_custom_node_view($node, $view_mode, $langcode) {
  // Check the display settings of our extra fields
  $display = field_extra_fields_get_display('node', $node->type, $view_mode);

}


/**
 * Implements hook_taxonomy_term_presave().
 *
 * Act on taxonomy terms before they are saved.
 *
 * Modules implementing this hook can act on the term object before it is
 * inserted or updated.
 *
 * @param $term
 *   A term object.
 * @param $view_mode
 * @param $langcode
 */
/*function hook_taxonomy_term_presave($term) {
  $term->obj = 'foo';
}*/



/**
 * Implements hook taxonomy_term_view().
 *
 * Act on a taxonomy term that is being assembled before rendering.
 *
 * The module may add elements to $term->content prior to rendering. The
 * structure of $term->content is a renderable array as expected by
 * drupal_render().
 *
 * @description
 * Add the extra field content in bht_custom.theme.inc
 *
 *  @param $term
 *   The term that is being assembled for rendering.
 * @param $view_mode
 *   The $view_mode parameter from taxonomy_term_view().
 * @param $langcode
 *   The language code used for rendering.
 *
 * @see hook_entity_view()
 */
/*function bht_custom_taxonomy_term_view($term, $view_mode, $langcode) {
  // Check the display settings of our extra fields
  $display = field_extra_fields_get_display('taxonomy_term', $term->vocabulary_machine_name, $view_mode);
}*/


/**
 * Implements hook paragraphs_item_view().
 *
 * @see hook_entity_view()
 */
function bht_custom_paragraphs_item_view($paragraphs_item, $view_mode, $langcode) {
  // Check the display settings of our extra fields.
  $display = field_extra_fields_get_display('paragraphs_item', $paragraphs_item->bundle, $view_mode);

  // Check if the date field is active.
  if (isset($display['date']) && $display['date']['visible']) {
    // Build the date renderable array.
    $date = _paragraphs_date_content($paragraphs_item);
    // Set field content.
    $paragraphs_item->content['date'] = $date;
  }

}


/**
 * Implements hook_contextual_links_view_alter().
 *
 * Alter a contextual links element before it is rendered.
 *
 * This hook is invoked by contextual_pre_render_links(). The renderable array
 * of #type 'contextual_links', containing the entire contextual links data that
 * is passed in by reference. Further links may be added or existing links can
 * be altered.
 *
 * @param $element
 *   A renderable array representing the contextual links.
 * @param $items
 *   An associative array containing the original contextual link items, as
 *   generated by menu_contextual_links(), which were used to build
 *   $element['#links'].
 *
 * @see hook_menu_contextual_links_alter()
 * @see contextual_pre_render_links()
 * @see contextual_element_info()
 */
// function bht_custom_contextual_links_view_alter(&$element, &$items) {
//   global $language;

//   // This hook is called for EVERY set of contextual links on a page.
//   // We first want to check the $element to make sure we are adding a link to
//   // the correct list of contextual links. In this case we only want to add a
//   // link to blocks where ctsort module could alter the output. We just add
//   // links using the same array structure as is used by theme_links.
//   if (isset($element['#element']['#block']) && $element['#element']['#block']->delta == 'cb_hello_world') {
//     $element['#links']['ctlist'] = array(
//       'title' => t('Sort the world'),
//       'href' => url('ctlist/hello-world/sort', array('language' => $language, 'absolute' => TRUE)),
//     );
//   }
// }

