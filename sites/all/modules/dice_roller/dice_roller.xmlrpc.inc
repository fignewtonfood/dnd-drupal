<?php
// $Id$

/**
 * @file
 * Adds support for a XMLRPC API, moved here to save on code footprint.
 */

/**
 * Remote XMLRPC functions.
 */

/**
 * Implements hook_xmlrpc().
 */
function dice_roller_xmlrpc() {
  $results = array(
    'dice_roller.make_roll' => '_dice_roller_make_xmlrpc_roll',
    'dice_roller.get_roll' => '_dice_roller_get_xmlrpc_roll',
  );

  $allowed_ip = variable_get('dice_roller_xmlrpc_allowed_ip', '127.0.0.1');
  if ($allowed_ip != 'all' && strpos($allowed_ip, ip_address()) === FALSE) {
    foreach ($results as $name => $func) {
      $results[$name] = '_dice_roller_xmlrpc_ip_error';
    }
  }
  return $results;
}

/**
 * Return an error message.
 */
function _dice_roller_xmlrpc_ip_error() {
  return array('error' => t('This address is not allowed to access this service.'));
}

/**
 * Execute the xmlrpc request to make a roll.
 */
function _dice_roller_make_xmlrpc_roll($request = '') {
  if ($request == '') {
    return array('error' => t('Incomplete request.'));
  }
  module_load_include('inc', 'dice_roller', 'dice_roller.roller');
  $dids = _dice_roller_parse_roll($request, '', -1, 'e');
  /* An EXTERNAL dice roller does not need any ouside associated key, and can use itself as key. */
  if (count($dids) > 0) {
    $dice_rolls = array();
    foreach ($dids as $did) {
      $roll = _dice_roller_get_roll($did, 'e');
      $dice_rolls[] = $roll[0];
    }
    if (count($dice_rolls) == 0) {
      return array('error' => t('Requested dice rolls do not exist.'));
    }
    return $dice_rolls;
  }
  else {
    return array('error' => t('Error in request format dice were not rolled.'));
  }
}

/**
 * Execute the xmlrpc request to retrieve a roll.
 */
function _dice_roller_get_xmlrpc_roll($did = '') {
  if ($did == '') {
    return array('error' => t('Incomplete request.'));
  }
  $roll = _dice_roller_get_roll($did, 'e');
  $dice_rolls[] = $roll[0];
  if (count($dice_rolls) == 0) {
    return array('error' => t('Requested dice rolls do not exist.'));
  }
  return $dice_rolls;
}
