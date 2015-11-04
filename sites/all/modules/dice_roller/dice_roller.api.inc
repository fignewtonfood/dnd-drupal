<?php
// $Id$

/**
 * @file
 * Adds support for a remote API, moved here to save on code footprint
 */

function _dice_roller_make_remote_roll($request = '', $format = 'JSON') {
  if ($request == '') {
    _dice_roller_send_remote_error(t('Incomplete request.'), $format);
    return;
  }
  $allowed_ip = variable_get('dice_roller_remote_allowed_ip', 'all');
  if ($allowed_ip != 'all' && strpos($allowed_ip, ip_address()) === FALSE) {
    _dice_roller_send_remote_error(t('This address is not allowed to access this service.'), $format);
    return;
  }
  module_load_include('inc', 'dice_roller', 'dice_roller.roller');
  $dids = _dice_roller_parse_roll($request, '', -1, 'e');
  /* An EXTERNAL dice roller does not need any ouside associated key, and can use itself as key. */
  if (!empty($dids)) {
    $dice_rolls = array();
    foreach ($dids as $did) {
      $roll = _dice_roller_get_roll($did, 'e');
      $dice_rolls[] = $roll[0];
    }
    if (count($dice_rolls) == 0) {
      _dice_roller_send_remote_error(t('Requested dice rolls do not exist.'), $format);
      return;
    }
    _dice_roller_send_remote_success($dice_rolls, $format);
  }
  else {
    _dice_roller_send_remote_error(t('Error in request format dice were not rolled.'), $format);
    return;
  }
}

function _dice_roller_get_remote_roll($did = '', $format = 'JSON') {
  if ($did == '') {
    _dice_roller_send_remote_error(t('Incomplete request.'), $format);
    return;
  }
  $allowed_ip = variable_get('dice_roller_remote_allowed_ip', 'all');
  if ($allowed_ip != 'all' && strpos($allowed_ip, ip_address()) === FALSE) {
    _dice_roller_send_remote_error(t('This address is not allowed to access this service.'), $format);
    return;
  }
  $dice_rolls = _dice_roller_get_roll($did, 'e');
  if (count($dice_rolls) == 0) {
    _dice_roller_send_remote_error(t('Requested dice roll does not exist.'), $format);
    return;
  }
  _dice_roller_send_remote_success($dice_rolls, $format);
}

function _dice_roller_send_remote_error($msg = '', $format = 'JSON') {
  $format = drupal_strtoupper($format);
  if ($format == 'HTML') {
    print '<div class="dice_roller_error">' . $msg . '</div>';
    return;
  }
  else {
    print drupal_json_encode(array('error' => $msg));
    return;
  }
}

function _dice_roller_send_remote_success($dice_rolls, $format) {
  $format = drupal_strtoupper($format);
  if ($format == 'HTML') {
    print theme('dice_roller_results', array('dice_rolls' => $dice_rolls));
    return;
  }
  else {
    print drupal_json_encode($dice_rolls);
    return;
  }
}
