<?php
/**
 * @file
 * equipment_spells.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function equipment_spells_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function equipment_spells_node_info() {
  $items = array(
    'equipment' => array(
      'name' => t('Equipment'),
      'base' => 'node_content',
      'description' => t('Add equipment'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'spells' => array(
      'name' => t('Spells'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
