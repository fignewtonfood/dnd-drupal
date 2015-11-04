<?php

/**
 * @file
 * Node related functions.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function dice_roller_form_node_type_form_alter(&$form, &$form_state) {
  if (isset($form['type'])) {
    $form['dice_roller'] = array(
      '#type' => 'fieldset',
      '#title' => t('Dice roller settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'additional_settings',
    );
    $form['dice_roller']['dice_roller'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable dice roller?'),
      '#default_value' => variable_get('dice_roller_' . $form['#node_type']->type, FALSE),
      '#description' => t('Enable this checkbox if you want to provide a dice roller.'),
    );
    $form_providers = module_implements('dice_roller_form', TRUE);
    if (!empty($form_providers)) {
      $form['dice_roller']['dice_roller_place'] = array(
        '#type' => 'select',
        '#title' => t('Place dice roller'),
        '#options' => array(
          'both' => t('On both nodes and comments'),
          'comment' => t('Only on comment forms'),
          'node' => t('Only on node forms')
        ),
        '#default_value' => variable_get('dice_roller_place_' . $form['#node_type']->type, 'both'),
        '#description' => t('Enable this checkbox if you want to provide a dice roller for your users.'),
      );
      $form_providers = array_combine($form_providers, $form_providers);
      $form['dice_roller']['dice_roller_form'] = array(
        '#type' => 'select',
        '#title' => t('Dice roller form'),
        '#options' => $form_providers,
        '#default_value' => variable_get('dice_roller_form_'. $form['#node_type']->type, 'dice_roller_basic'),
        '#description' => t('Select the module you want to have handle your dice input.'),
      );
    }
    else {
      // Give a warning.
      $form['dice_roller']['dice_roller_form'] = array(
        '#type' => 'markup',
        '#item' => t('You have not enabled a module able to provide a dice form. No dice will be available ' .
          'at posting. If this is not your intention, please enable a module that can provide a form, ' .
          'for example "Dice roller basic".'),
      );
    }
  }
}

/**
 * Implements hook_node_insert().
 */
function dice_roller_node_insert($node) {
  dice_roller_node_update($node);
}

/**
 * Implements hook_node_update().
 */
function dice_roller_node_update($node) {
  $enabled = variable_get('dice_roller_' . $node->type, FALSE);
  if ($enabled && user_access('use dice roller')) {
    $form_provider = variable_get('dice_roller_form_'. $node->type, 'dice_roller_basic');
    if (module_exists($form_provider)) {
      module_load_include('inc', 'dice_roller', 'dice_roller.roller');
      module_invoke($form_provider, 'dice_roller_form_submit', $node, 'node');
    }
  }
}

/**
 * Implements hook_node_delete().
 */
function dice_roller_node_delete($node) {
  _dice_roller_delete_roll($node->nid, 'n');
}

/**
 * Implements hook_node_view().
 */
function dice_roller_node_view($node, $view_mode = 'full', $langcode) {
  if ($view_mode != 'full') {
    return; /* Exit if not in full mode. */
  }
  if (user_access('view dice rolls')) {
    // Show any prior dice even if roller is disabled.
    $dice_rolls = _dice_roller_get_roll($node->nid, 'n');
    $node->content['dice_rolls'] = array(
      '#weight' => !empty($weight) ? $weight : 100,
      '#markup' => theme('dice_roller_results', array('dice_rolls' => $dice_rolls)),
    );
  }
}

/**
 * Helper function for hook_form_alter() on node forms.
 */
function _dice_roller_form_alter_node(&$form, &$form_state, $form_id) {
  // Check for node form.
  if (strpos($form_id, '_node_form')) {
    $type = isset($form['type']['#value']) ? $form['type']['#value'] : '';
    $enabled = variable_get('dice_roller_' . $type, FALSE);
    $placement = variable_get('dice_roller_place_' . $type, 'both');
    if ($enabled == TRUE && ($placement == 'both' || $placement == 'node') ) {
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
function _dice_roller_field_extra_fields_nodes(&$extra, $type) {
  // Check if this is enabled and positioned for node type.
  $enabled = variable_get('dice_roller_' . $type, FALSE);
  $placement = variable_get('dice_roller_place_' . $type, 'both');
  if ($enabled == TRUE && ($placement == 'both' || $placement == 'node') ) {
    $extra['node'][$type] = array(
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
