<?php
/**
 * @file
 * cleric.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cleric_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cleric_node_info() {
  $items = array(
    'fifth_cleric_character' => array(
      'name' => t('Cleric'),
      'base' => 'node_content',
      'description' => t('Create a cleric!'),
      'has_title' => '1',
      'title_label' => t('Character name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
