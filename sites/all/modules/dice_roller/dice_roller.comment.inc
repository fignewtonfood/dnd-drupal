<?php

/**
 * @file
 * Comment related functions.
 */

/**
 * Implements hook_comment_insert().
 */
function dice_roller_comment_insert($comment) {
  dice_roller_comment_update($comment);
}

/**
 * Implements hook_comment_update().
 */
function dice_roller_comment_update($comment) {
  $node = node_load($comment->nid);
  $enabled = variable_get('dice_roller_' . $node->type, FALSE);
  if ($enabled && user_access('use dice roller')) {
    $form_provider = variable_get('dice_roller_form_'. $node->type, 'dice_roller_basic');
    if (module_exists($form_provider)) {
      module_load_include('inc', 'dice_roller', 'dice_roller.roller');
      module_invoke($form_provider, 'dice_roller_form_submit', $comment, 'comment');
    }
  }
}

/**
 * Implements hook_comment_delete().
 */
function dice_roller_comment_delete($comment) {
  _dice_roller_delete_roll($comment->cid, 'c');
}

/**
 * Implements hook_comment_view().
 */
function dice_roller_comment_view($comment) {
  if (user_access('view dice rolls')) {
    $dice_rolls = _dice_roller_get_roll($comment->cid, 'c');
    $comment->content['dice_rolls'] = array(
      '#weight' => !empty($weight) ? $weight : 100,
      '#markup' => theme('dice_roller_results', array('dice_rolls' => $dice_rolls)),
    );
  }
}

/**
 * Helper function for hook_form_alter() on comment forms.
 */
function _dice_roller_form_alter_comment(&$form, &$form_state, $form_id) {
  // Check for comment form.
  if (substr($form_id, 0, 7) == 'comment' && isset($form['#node'])) {
    $type = $form['#node']->type;
    $enabled = variable_get('dice_roller_' . $type, FALSE);
    $placement = variable_get('dice_roller_place_' . $type, 'both');
    if ($enabled == TRUE && ($placement == 'both' || $placement == 'comment') ) {
      $form_provider = variable_get('dice_roller_form_'. $type, 'dice_roller_basic');
      if (module_exists($form_provider)) {
        $new_form = module_invoke($form_provider, 'dice_roller_form', $form, $form_state, $form_id);
        if (is_array($new_form)) {
          $form = array_merge($form, $new_form);
        }
      }
    }
  }
}

/**
 * Helper function for hook_field_extra_fields().
 */
function _dice_roller_field_extra_fields_comments(&$extra, $type) {
  // Check if this is enabled and positioned for node type.
  $enabled = variable_get('dice_roller_' . $type, FALSE);
  $placement = variable_get('dice_roller_place_' . $type, 'both');
  if ($enabled == TRUE && ($placement == 'both' || $placement == 'node') ) {
    $extra['comment'][$type] = array(
      'form' => array(
        'dice_roller' => array(
          'label' => t('Dice roller form'), 
          'description' =>  t('Dice roller form'),
          'weight' => 4,
        ),
      ),
      'display' => array(
        'dice_roller' => array(
          'label' => t('Dice roller results'), 
          'description' => t('Dice roller results'), 
          'weight' => 4,
        ),
      ),
    );
  }
}
