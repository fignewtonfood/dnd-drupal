<?php
/**
 * @file
 * cleric.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cleric_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_attribute_tabs|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_attribute_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attribute_Tabs',
    'weight' => '2',
    'children' => array(
      0 => 'group_fifth_cleric_race',
      1 => 'group_raw_stats',
      2 => 'group_modifiers',
      3 => 'group_personality',
      4 => 'group_fifth_skill_prof',
      5 => 'group_fifth_other_stats',
      6 => 'group_fifth_features',
      7 => 'group_proficiencies',
      8 => 'group_equipment',
      9 => 'group_spells',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-attribute-tabs field-group-tabs',
      ),
    ),
  );
  $export['group_attribute_tabs|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_equipment|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_equipment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Equipment',
    'weight' => '233',
    'children' => array(
      0 => 'field_fifth_cleric_weapon_choice',
      1 => 'field_fifth_cleric_armor_choice',
      2 => 'field_fifth_cleric_weaponchoice2',
      3 => 'field_fifth_cleric_pack_choice',
      4 => 'field_fifth_cleric_holy_symbol',
      5 => 'field_fifth_background_bundle',
      6 => 'field_fifth_starting_money',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-equipment field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_equipment|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_fifth_cleric_race|node|character|form';
  $field_group->group_name = 'group_fifth_cleric_race';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Base Options',
    'weight' => '230',
    'children' => array(
      0 => 'field_race',
      1 => 'field_fifth_dwarven_sub_race',
      2 => 'field_fifth_class',
      3 => 'field_fifth_cleric_level',
      4 => 'field_fifth_cleric_domain',
      5 => 'field_fifth_backgrounds',
      6 => 'field_fifth_elven_sub_race',
      7 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_fifth_cleric_race|node|character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_fifth_features|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_fifth_features';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Features',
    'weight' => '235',
    'children' => array(
      0 => 'field_fifth_racial_features',
      1 => 'field_fifth_subracial_features',
      2 => 'field_fifth_class_features',
      3 => 'field_fifth_domain_features',
      4 => 'field_fifth_background_feature',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-fifth-features field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_fifth_features|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_fifth_other_stats|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_fifth_other_stats';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Other Stats',
    'weight' => '239',
    'children' => array(
      0 => 'field_fifth_armor_class',
      1 => 'field_fifth_initiative',
      2 => 'field_fifth_speed',
      3 => 'field_fifth_hit_points',
      4 => 'field_fifth_hit_dice',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-fifth-other-stats field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_fifth_other_stats|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_fifth_skill_prof|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_fifth_skill_prof';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Skill Proficiencies',
    'weight' => '238',
    'children' => array(
      0 => 'field_fifth_acrobatics_prof',
      1 => 'field_fifth_acrobatics',
      2 => 'field_fifth_animal_handling_prof',
      3 => 'field_fifth_animal_handling',
      4 => 'field_fifth_arcana_proficiency',
      5 => 'field_fifth_arcana',
      6 => 'field_fifth_athletics_prof',
      7 => 'field_fifth_athletics',
      8 => 'field_fifth_deception_prof',
      9 => 'field_fifth_deception',
      10 => 'field_fifth_history_proficiency',
      11 => 'field_fifth_history',
      12 => 'field_fifth_insight_proficiency',
      13 => 'field_fifth_insight',
      14 => 'field_fifth_intimidation_prof',
      15 => 'field_fifth_intimidation',
      16 => 'field_fifth_investigation_prof',
      17 => 'field_fifth_investigation',
      18 => 'field_fifth_medicine_proficiency',
      19 => 'field_fifth_medicine',
      20 => 'field_fifth_nature_proficiency',
      21 => 'field_fifth_nature',
      22 => 'field_fifth_perception_prof',
      23 => 'field_fifth_perception',
      24 => 'field_fifth_performance_prof',
      25 => 'field_fifth_performance',
      26 => 'field_fifth_persuasion_prof',
      27 => 'field_fifth_persuasion',
      28 => 'field_fifth_religion_proficiency',
      29 => 'field_fifth_religion',
      30 => 'field_fifth_sleight_of_hand_prof',
      31 => 'field_fifth_sleight_of_hand',
      32 => 'field_fifth_stealth_proficiency',
      33 => 'field_fifth_stealth',
      34 => 'field_fifth_survival_proficiency',
      35 => 'field_fifth_survival',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-fifth-skill-prof field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_fifth_skill_prof|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_modifiers|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_modifiers';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Modifiers',
    'weight' => '237',
    'children' => array(
      0 => 'field_fifth_strength_modifier',
      1 => 'field_fifth_dexterity_modifier',
      2 => 'field_fifth_constitution_modifie',
      3 => 'field_fifth_intelligence_modifie',
      4 => 'field_fifth_wisdom_modifier',
      5 => 'field_fifth_charisma_modifier',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-modifiers field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_modifiers|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personality|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_personality';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Personality',
    'weight' => '234',
    'children' => array(
      0 => 'field_fifth_bckgrndprsnlty_acoly',
      1 => 'field_fifth_bckgrndideal_acolyte',
      2 => 'field_fifth_bckgrnd_bond_acolyte',
      3 => 'field_fifth_bckgrnd_flaw_acolyte',
      4 => 'field_fifth_alignment',
      5 => 'field_fifth_favorite_schemes',
      6 => 'field_fifth_bckgrndprsnltychrltn',
      7 => 'field_fifth_bckgrnd_idl_chrlatan',
      8 => 'field_fifth_bckgrnd_bnd_chrlatan',
      9 => 'field_bckgrnd_flw_chrlatan',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personality|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_proficiencies|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_proficiencies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Proficiencies',
    'weight' => '232',
    'children' => array(
      0 => 'field_fifth_cleric_skills',
      1 => 'field_fifth_knwldgedomain_langgs',
      2 => 'field_fifth_knwldge_domainskills',
      3 => 'field_fifth_dwarven_tool_profici',
      4 => 'field_fifth_background_languages',
      5 => 'field_fifth_weapon_proficiency',
      6 => 'field_fifth_languages',
      7 => 'field_fifth_armor_proficiency',
      8 => 'field_fifth_background_skills',
      9 => 'field_fifth_background_tool_prof',
      10 => 'field_fifth_racial_skill_prof',
      11 => 'field_fifth_sub_race_language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-proficiencies field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_proficiencies|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_raw_stats|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_raw_stats';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Raw Stats',
    'weight' => '236',
    'children' => array(
      0 => 'field_fifth_strength',
      1 => 'field_fifth_dexterity',
      2 => 'field_fifth_constitution',
      3 => 'field_fifth_intelligence',
      4 => 'field_fifth_wisdom',
      5 => 'field_fifth_charisma',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-raw-stats field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_raw_stats|node|fifth_cleric_character|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_spells|node|fifth_cleric_character|form';
  $field_group->group_name = 'group_spells';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fifth_cleric_character';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_attribute_tabs';
  $field_group->data = array(
    'label' => 'Spells',
    'weight' => '231',
    'children' => array(
      0 => 'field_fifth_level_1_cantrips',
      1 => 'field_fifth_lvl1_spells_prepared',
      2 => 'field_fifth_domain_spells',
      3 => 'field_fifth_racial_spell',
      4 => 'field_fifth_level_2_spells',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-spells field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_spells|node|fifth_cleric_character|form'] = $field_group;

  return $export;
}
