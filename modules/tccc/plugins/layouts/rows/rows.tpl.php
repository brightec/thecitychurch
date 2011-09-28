<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<div class="layout-fourrows panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

<?php

  for ($x=1; $x<=8; $x++) {
    $row = 'row-' . $x;
    if ($content[$row]) {
      print '<div class="row ' . $row . '">';
      print $content[$row];
      print '</div>';
      print '<div style="clear: both"></div>';
    }
  }

?>

</div>
