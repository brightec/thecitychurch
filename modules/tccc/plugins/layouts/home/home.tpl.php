<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<section class="layout-home panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top grid_12 alpha omega">
    <div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>
  
  <div class="grid_4 alpha">
    <div class="panel-column-1">
      <div class="button_1"></div>
      <?php print $content['column-1']; ?>
    </div>
  </div>
  
  <div class="grid_4">
    <div class="panel-column-2">
      <div class="button_2"></div>
      <?php print $content['column-2']; ?>
    </div>
  </div>
  
  <div class="grid_4 omega">
    <div class="panel-column-3">
      <div class="button_3"></div>
      <?php print $content['column-3']; ?>
    </div>
  </div>
  
</section>
