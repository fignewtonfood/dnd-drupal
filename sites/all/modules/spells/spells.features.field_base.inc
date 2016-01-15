<?php
/**
 * @file
 * spells.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function spells_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_at_higher_level'.
  $field_bases['field_at_higher_level'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_at_higher_level',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_casting_level'.
  $field_bases['field_casting_level'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_casting_level',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Cantrip',
        1 => '1st Level',
        2 => '2nd Level',
        3 => '3rd Level',
        4 => '4th Level',
        5 => '5th Level',
        6 => '6th Level',
        7 => '7th Level',
        8 => '8th Level',
        9 => '9th Level',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_casting_time'.
  $field_bases['field_casting_time'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_casting_time',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => '1 reaction',
        2 => '1 bonus action',
        3 => '1 action',
        4 => '1 minute',
        5 => '10 minutes',
        6 => '1 hour',
        7 => '8 hours',
        8 => '12 hours',
        9 => '24 hours',
        10 => '1 action or 8 hours',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_components'.
  $field_bases['field_components'] = array(
    'active' => 1,
    'cardinality' => 3,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_components',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Verbal',
        2 => 'Somatic',
        3 => 'Material',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_concentration_bool'.
  $field_bases['field_concentration_bool'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_concentration_bool',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_duration'.
  $field_bases['field_duration'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_duration',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Instantaneous',
        2 => '1 round',
        3 => '6 rounds',
        4 => '1 minute',
        5 => '10 minutes',
        6 => '1 hour',
        7 => '2 hours',
        8 => '8 hours',
        9 => '24 hours',
        10 => '1 day',
        11 => '7 days',
        12 => '10 days',
        13 => '30 days',
        14 => 'Until dispelled',
        15 => 'Until dispelled or triggered',
        16 => 'Special',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_edition'.
  $field_bases['field_edition'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_edition',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => '5th Edition D&D',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_higher_level_description'.
  $field_bases['field_higher_level_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_higher_level_description',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'field_material_components'.
  $field_bases['field_material_components'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_material_components',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_range'.
  $field_bases['field_range'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_range',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Self',
        2 => 'Self (10-foot radius)',
        3 => 'Self (10-foot radius hemisphere)',
        4 => 'Self (15-foot cone)',
        5 => 'Self (15-foot cube)',
        6 => 'Self (15-foot radius)',
        7 => 'Self (30-foot cone)',
        8 => 'Self (30-foot radius)',
        9 => 'Self (60-foot line)',
        10 => 'Self (60-foot cone)',
        11 => 'Self (100-foot line)',
        12 => 'Self (5-mile radius)',
        13 => 'Touch',
        14 => '5 feet',
        15 => '10 feet',
        16 => '30 feet',
        17 => '60 feet',
        18 => '90 feet',
        19 => '100 feet',
        20 => '120 feet',
        21 => '150 feet',
        22 => '300 feet',
        23 => '500 feet',
        24 => '1 mile',
        25 => '500 miles',
        26 => 'Sight',
        27 => 'Unlimited',
        28 => 'Special',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_ritual_bool'.
  $field_bases['field_ritual_bool'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ritual_bool',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_school_of_magic'.
  $field_bases['field_school_of_magic'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_school_of_magic',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Abjuration',
        2 => 'Conjuration',
        3 => 'Divination',
        4 => 'Enchantment',
        5 => 'Evocation',
        6 => 'Illusion',
        7 => 'Necromancy',
        8 => 'Transmutation',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_spell_description'.
  $field_bases['field_spell_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_spell_description',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
