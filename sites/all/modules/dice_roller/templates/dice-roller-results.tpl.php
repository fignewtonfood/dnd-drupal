<?php
// $Id$

/**
 * @file
 * Implements the default result display theme
 *
 * Incoming variables:  $dice_rolls, an array of roll results.
 */
?>
<div class="dice_rolls">
<?php
  $str_rolls = '';
  $last_note = '';
  if (isset($dice_rolls) && is_array($dice_rolls)) {
    foreach ($dice_rolls as $index => $dice_roll) {
      if (!empty($dice_roll['did']) && $last_note != $dice_roll['roll_notes']) {
        $str_rolls .= '<div class="dice_note">' . $dice_roll['roll_notes'] . '</div>'."\n";
      }
      $str_rolls .= '<div class="dice_roll">' . t("I rolled @roll_command, the result is @roll_results.",
        array('@roll_command' => $dice_roll['roll_command'], '@roll_results' => $dice_roll['roll_result'])) . '</div>'."\n";
      $last_note = $dice_roll['roll_notes'];
    }
  }
  print $str_rolls;
?>
</div>