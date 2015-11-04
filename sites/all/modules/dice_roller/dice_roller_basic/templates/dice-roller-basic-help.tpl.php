<?php
// $Id$

/**
 * @file
 * Implements the default help theme
 *
 * Incoming variables:  $roll_help, an array of help tips.
 */
?>
<div class="tips">
<p>
<?php print t("This die roller is based on the excellent OpenRPG, and uses exactly the same options. If you know how to use dice in OpenRPG, you know how to do it here. Enter dice like you would see them in an RPG rule book. So, '3d6' means to roll 3 six-siders and total the result. Similarly, '1d20+5' means to roll one twenty-sider and add five to the result. Multiple rolls can be made by separating commands with a semi-colon such as: 1d20; 2d20; 3d20"); ?>
</p><p>
<?php print t("If you want to get fancier, you format the roll like this: 3d6.option(value) For example, you could enter '4d6.takeHighest(3)', which would roll 4 six-siders, and keep only the highest 3 rolls. You can even chain multiple options, for example '10d10.minroll(4).takeLowest(5)'. This one would roll 10d10 with a minimum roll of 4, taking only the lowest 5."); ?>
</p><p>
<?php
  if(!empty($roll_help)) {
    print t('Available options are:');
    print '<ul class="dice_help"><li>'. implode('</li><li>', $roll_help) .'</li></ul>';
 }
?>
<?php print t("(Portions of the above are copied verbatim from OpenRPG, and are Copyright (C) 2000-2001 <a href='http://openrpg.com/'>The OpenRPG Project</a>)"); ?>
</p>
</div>
