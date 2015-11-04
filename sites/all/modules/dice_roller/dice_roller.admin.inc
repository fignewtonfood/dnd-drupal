<?php
// $Id$

/**
 * @file
 * Adds administrative settings for dice roller, moved here to save on code footprint.
 */

/**
 * Implementation of admin settings form.
 */
function dice_roller_admin_settings($form, &$form_state) {

  $roll_types = module_invoke_all('dice_roller_register_keywords');
  if (count($roll_types) > 0) {
    $options = array();
    foreach ($roll_types as $roll_key => $roll) {
      $options[$roll_key] = $roll_key .': '. $roll['help'];
    }
    $default_rolls = array();
    $form['dice_roller_keywords'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Enable dice keywords'),
      '#required' => TRUE,
      '#default_value' => variable_get('dice_roller_keywords', $default_rolls),
      '#options' => $options,
      '#description' => t('Select the keywords available to use with the dice roller.'),
    );
  }
  else {
    $form['dice_roller_keywords'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Enable dice keywords'),
      '#options' => $roll_types,
      '#description' => 'No additional keywords found. Are all your dice modules currently installed?',
    );
  }

  $form['dice_roller_remote_allowed_ip'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed IP addresses for remote API in canonical format, separated by commas'),
    '#default_value' => variable_get('dice_roller_remote_allowed_ip', 'all'),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('Remote API calls to this module from any other IP will be rejected.'),
  );

  $form['dice_roller_remote_allowed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable remote dice rolling'),
    '#default_value' => variable_get('dice_roller_remote_allowed', ''),
    '#description' => t('Turn on to allow remote access to the dice roller api by HTML and JSON results.'),
  );

  $form['dice_roller_xmlrpc_allowed_ip'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed IP addresses for XMLRPC API in canonical format, separated by commas'),
    '#default_value' => variable_get('dice_roller_xmlrpc_allowed_ip', '127.0.0.1'),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('XMLRPC API calls to this module from any other IP will be rejected.'),
  );

  $form['dice_roller_xmlrpc_allowed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable XMLRPC dice rolling'),
    '#default_value' => variable_get('dice_roller_xmlrpc_allowed', ''),
    '#description' => t('Turn on to allow XMLRPC access to the dice roller api.'),
  );

  return system_settings_form($form);
}
