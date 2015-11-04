<?php
// $Id$

/**
 * @file
 * Implements the process of parsing and rolling dice, moved here to save on code footprint when dice results are being viewed, not rolled.
 */

/**
 * Dice processing related functions.
 */

/**
 * Given user commands and notes, split command set into individual commands for processing. Then save and return roll set information.
 */
function _dice_roller_parse_roll($roll_command, $roll_notes, $pid, $origin) {
  $command_set = explode(';', trim($roll_command));
  $results = array();
  $commands = array();
  foreach ($command_set as $command) {
    $roll = _dice_roller_parse_single_roll($command);
    if ($roll !== FALSE) {
      $results[] = $roll;
      $commands[] = $command;
    }
    elseif (!empty($command)) {
      drupal_set_message(t("There was an error in rolling your dice selection @command.", array('@command' => $command)));
    }
  }
  if (!empty($results)) {
    foreach ($results as $index => $result) {
      $dids[] = _dice_roller_insert_roll($commands[$index], $results[$index], $roll_notes, $pid, $origin);
    }
    return $dids;
  }
  return FALSE;
}

/**
 * Given a single user roll command, parse command according to available behaviors, and return roll results.
 * User commands should be of the format:
 * XdY[+/-Z][.command(A,B...C)]
 * Required XdY, where X = number of dice to roll, Y = number of sides of the die
 * Optional +Z or -Z, for add or subtract Z from the result of each die roll, same as .each(Z)
 * Optional .command(A,B...C) for a configured function and parameters
 */
function _dice_roller_parse_single_roll($roll_command) {
  // Check that we have a command at all.
  if (empty($roll_command)) {
    return FALSE;
  }
  // And now we start.
  $error = FALSE;
  $err_messages = array();
  $command_set = array();
  $number_of_dice = 0;
  $max_sides = 0;
  // Prepare roll by removing all whitespaces.
  $roll_command = trim($roll_command);
  $roll_command = str_replace(' ', '', $roll_command);
  $roll_command = str_replace("\t", '', $roll_command);
  $roll_command = str_replace("\n", '', $roll_command);
  $split = explode('d', $roll_command);
  // Do we have at least 1 d?
  if (count($split) < 2) {
    return FALSE;
  }
  // Pop the number of dice off the command.
  $number_of_dice = array_shift($split);
  // Is the value before the d a positive number?
  if (!is_numeric($number_of_dice) || $number_of_dice < 1) {
    drupal_set_message(t('Unable to parse dice roll: No number of dice to roll given.'));
    return FALSE;
  }
  // Compress the rest of the command for more processing.
  $roll_command = implode('', $split);
  // Split based on having a "." character in the command.
  $split = explode('.', $roll_command);
  $max_sides = array_shift($split);
  // Check for additive or subtractive commands with sides.
  if (!is_numeric($max_sides)) {
    // If plus and minus both come back as false OR as zero we have a syntax error.
    // We're checking for a greater than 0 position, since we need a leading number.
    $plus = strpos($max_sides, '+');
    $minus = strpos($max_sides, '-');
    if ($plus || $minus) {
      // Based on the plus or minus we'll try to get the right addition here.
      // We're going to add | symbols here to split on the plus and negatives.
      // This will give us a format like 6|+3|-2|+1
      $max_sides = str_replace('+', '|+', $max_sides);
      $max_sides = str_replace('-', '|-', $max_sides);
      $split2 = explode('|', $max_sides);
      // First grab the leading value.
      $max_sides = array_shift($split2);
      // Now total up the additives.
      $total = 0;
      foreach ($split2 as $this_split) {
        // We are a little fault tolerant here, if a non number value is
        // added or subtracted on the primary dice - then we ignore it.
        if (is_numeric($this_split)) {
          $total = $total + $this_split;
        }
      }
      // Add the addition command if we have a non zero total.
      if ($total != 0) {
        $command_set['dice_roller_addition'] = array($total);
      }
    }
  }
  // Check that the max sides we found is correct.
  if (!is_numeric($max_sides) || $max_sides < 1) {
    drupal_set_message(t('Unable to parse dice roll: No number of sides for dice given.'));
    return FALSE;
  }
  // Now we can move on to the additional commands.
  // Duplicated functions overwrite each other the later they appear in the string.
  foreach ($split as $key => $this_command) {
    // Set the command name as the command for formats without ().
    $command_name = drupal_strtolower($this_command);
    $command_parameters = array();
    // Process the parenthesis options.
    // We're checking for a greater than 0 position, since we need a leading number.
    $left_p_pos = strpos($this_command, '(');
    $right_p_pos = strpos($this_command, ')');
    // If we have either parenthesis, start processing the command for parameters.
    if ($left_p_pos || $right_p_pos) {
      // Check that we have one of each in the correct order.
      if ($left_p_pos && $right_p_pos && $left_p_pos < $right_p_pos) {
        $command_name = drupal_strtolower(drupal_substr($this_command, 0, $left_p_pos));
        $command_parameters = drupal_substr($this_command, ($left_p_pos + 1), ($right_p_pos - (1 + $left_p_pos)));
        if (!empty($command_parameters) && strpos($command_parameters, ',') !== FALSE) {
          $command_parameters = explode(',', $command_parameters);
        }
        $command_parameters = !empty($command_parameters) ? (array) $command_parameters : array();
      }
    }
    // Now we have the right command name and parameters, if we're meant to have them.
    if (_dice_roller_check_function($command_name, $command_parameters) === TRUE) {
      // At this point we can confirm the name is legit and registered.
      // And that the parameters are all numbers.
      $command_set[$command_name] = $command_parameters;
    }
  }
  // Ok, let's do this.
  return _dice_roller_make_roll($number_of_dice, $max_sides, $command_set);
}

/**
 * Make calls to additional commands and return the result string.
 */
function _dice_roller_make_roll($number_of_dice, $max_sides, $command_set) {
  /* These are our registered roll keywords. */
  $rolls = module_invoke_all('dice_roller_register_keywords');

  /* PRE ROLL FUNCS:  minroll */
  /* Preroll functions make any changes required to the context of dice rolling.
   * This includes gathering information from sheets, game, etc, or marking DB changes.
   * DEFAULT: The default context is: min=1, max=value of die
   * FOOTPRINT: preroll_function(&$context, $funcParas) where $funcParas come from the user.
   * RETURN: updated context variable
   */
  $context = array(
    'number' => $number_of_dice,
    'min' => 1,
    'max' => $max_sides,
  );
  foreach ($command_set as $command => $command_parameters) {
    if (isset($rolls[$command]['pre_callback']) && function_exists($rolls[$command]['pre_callback'])) {
      $context = call_user_func_array($rolls[$command]['pre_callback'], array($context, $command_parameters));
    }
  }

  $roll_set = array();
  for ($i = 0; $i < $context['number']; $i++) {
    $this_roll = array(
      'result' => NULL,
      'extra' => NULL, // This is an array of rolls of the same structure as $thisRoll
      'read' => TRUE,
    );
    $this_roll['result'] = mt_rand($context['min'], $context['max']);

    /* MID ROLL FUNCS:   extra, open, hitsopen (calls open) */
    /* Midroll functions modify things on the fly as the dice are rolled.
     * Midroll functions are called on each dice that is rolled in the set.
     * This includes adding additional rolls for open-ended rolls, or rolling bonus dice.
     * Dice rolled here may change the context as well as the result set.
     * Additional dice are added as an array to the parent roll for display purposes later.
     * DEFAULT: The rollset returns flat value rolled within min/max context
     * FOOTPRINT: midroll_function($context, &$thisRoll, $funcParas) where $funcParas come from the user
     * RETURN: updated thisroll variable
     * WARNING: This has the potential to become an infinate recursive situation if dicerolls
     * create guaranteed additional dicerolls based on always true parameters.
     * ALWAYS CHECK FOR THIS CONDITION IN YOUR API CALL.
     */
    foreach ($command_set as $command => $command_parameters) {
      if (isset($rolls[$command]['mid_callback']) && function_exists($rolls[$command]['mid_callback'])) {
        $this_roll = call_user_func_array($rolls[$command]['mid_callback'], array($context, $this_roll, $command_parameters));
      }
    }
    $roll_set[] = $this_roll;
  }

  /* POST ROLL FUNCS: each */
  /* Postroll functions make any additional modifications required to a roll to read the later result.
   * DEFAULT: No changes are made to the rolls
   * FOOTPRINT: preroll_function(&$context, &rollSet, $funcParas) where $funcParas come from the user.
   * RETURN: updated rollSet variable
   */
  foreach ($command_set as $command => $command_parameters) {
    if (isset($rolls[$command]['post_callback']) && function_exists($rolls[$command]['post_callback'])) {
      $roll_set = call_user_func_array($rolls[$command]['post_callback'], array($context, $roll_set, $command_parameters));
    }
    elseif ($command == 'each') {
      /* If each() comes up but has been disabled as a keyword - then the required each is called.
       * This is where the +/-Z feature is handled, as .each(Z)
       */
      $roll_set = _dice_roller_required_each($context, $roll_set, $command_parameters);
    }
  }

  /* READ ROLL FUNCS: takehighest, takelowest */
  /* Readroll functions filter or remove rolls that don't meet requirements.
   * They only change the display format to determine success. This may be better handled with theming.
   * DEFAULT: No changes are made to the rollset
   * FOOTPRINT: preroll_function(&$context, &rollSet, $funcParas) where $funcParas come from the user.
   * RETURN: updated context variable
   */
  foreach ($command_set as $command => $command_parameters) {
    if (isset($rolls[$command]['read_callback']) && function_exists($rolls[$command]['read_callback'])) {
      $roll_set = call_user_func_array($rolls[$command]['read_callback'], array($context, $roll_set, $command_parameters));
    }
    if ($command == 'dice_roller_addition') {
      /*
       * This is where the +/-Z feature is handled, as an additional sum for sumto only results (Z)
       */
      $roll_set = _dice_roller_required_addition($context, $roll_set, $command_parameters);
    }
  }

  /* OUTPUT ROLL FUNCS: hits, takelowest
   * At this point we should have an array of dice rolls in a tree structure (for bonus rolls).
   * We now have some choices on how to display this information:
   * Outputroll functions grab the values against which we format our output.
   * A summation(against a target value) OR a selection of hits (against a target value)
   * DEFAULT: summation, without any defined target number
   * FOOTPRINT: outputroll_function(&$mode, $funcParas) where $funcParas come from the user.
   * RETURN: updated displayFormat variable
   * While the output itself may be better handled in theme (later!) the determination of which form
   * comes from the user's own input. (Ex: hits, hitsopen implies a hits format)
   */
  $display_format = array(
    'mode' => 'default',
    'target' => NULL,
  );
  foreach ($command_set as $command => $command_parameters) {
    if (isset($rolls[$command]['output_callback']) && function_exists($rolls[$command]['output_callback'])) {
      $display_format = call_user_func_array($rolls[$command]['output_callback'], array($context, $roll_set, $display_format, $command_parameters));
    }
  }

  /* Now we know if any of the values selected require an explicit hit vs. sumto output. */
  /* Preserve the 'extra' set format, for reading the roll order sequence. */
  $roll_strings = array();
  $hits = 0;
  $sumto = 0;
  foreach ($roll_set as $this_roll) {
    $this_roll['extra'] = _dice_roller_flatten_set($this_roll['extra']);
    if ($this_roll['read'] == TRUE) {
      $sumto += $this_roll['result'];
    }
    if ($this_roll['read'] == TRUE) {
      if ($this_roll['result'] >= $display_format['target']) {
        $hits++;
      }
    }
    $extra_results = array();
    if (count($this_roll['extra']) > 0) {
      foreach ($this_roll['extra'] as $extra_roll) {
        $extra_results[] = $extra_roll['result'];
        if ($extra_roll['read'] == TRUE) {
          $sumto += $extra_roll['result'];
        }
        if ($extra_roll['read'] == TRUE) {
          if ($extra_roll['result'] >= $display_format['target']) {
            $hits++;
          }
        }
      }
    }
    $extra_string = '';
    if (count($extra_results) > 0) {
      $extra_string = ', [' . implode(', ', $extra_results) . '] ';
    }
    $roll_strings[] = $this_roll['result'] . $extra_string;
  }
  if (count($roll_strings) > 0) {
    $rolls_string = implode(', ', $roll_strings);
  }

  /* Now, output based on hit vs. sums. */
  if ($display_format['mode'] == 'hits' && isset($display_format['target'])) {
    $result_string = $hits . ' vs. ' . $display_format['target'];
  }
  elseif ( $display_format['mode'] == 'sumto' && isset($display_format['target'])) {
    $result_string = $sumto . ' vs. ' . $display_format['target'];
  }
  else {
    $result_string = $sumto;
  }

  return $rolls_string . ' = ' . $result_string;
}

/**
 * Helper functions
 */

/**
 * Check if the given behavior requested is a legitimate command.
 */
function _dice_roller_check_function($command_name, $command_parameters) {
  $approved_commands = variable_get('dice_roller_keywords', array());
  if (!in_array($command_name, $approved_commands, TRUE)) {
    return FALSE;
  }
  $command_parameters = (array) $command_parameters;
  foreach ($command_parameters as $this_parameter) {
    if (!is_numeric($this_parameter)) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Flatten extra sets into the main set for sorting.
 */
function _dice_roller_flatten_set($roll_set) {
  if (!is_array($roll_set)) {
    return $roll_set;
  }

  // Ah yes. Good old recursion.
  $flat_set = array();
  foreach ($roll_set as $this_roll) {
    $flat_set[] = $this_roll;
    if (is_array($this_roll['extra'])) {
      $extra_set = _dice_roller_flatten_set($this_roll['extra']);
      $flat_set = array_merge($flat_set, $extra_set);
    }
  }
  return $flat_set;
}

/**
 * This is the one absolutely required extension. This handles the +Z feature for XdY+/-Z.
 */
function _dice_roller_required_addition($context, $roll_set, $command_parameters) {
  if (is_numeric($command_parameters[0])) {
    $roll_set[] = array(
      'result' => $command_parameters[0],
      'extra' => NULL,
      'read' => TRUE,
    ); // Flat add as if another die was rolled.
  }
  return $roll_set;
}
