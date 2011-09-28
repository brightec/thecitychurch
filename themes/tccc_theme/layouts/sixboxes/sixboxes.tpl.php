<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<section class="layout-sixboxes mini-panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="box-1 box first">
    <?php print $content['box_1']; ?>
  </div>
  <div class="box-2 box">
    <?php print $content['box_2']; ?>
  </div>
  <div class="box-3 box last">
    <?php print $content['box_3']; ?>
  </div>
  <div class="box-4 box first">
    <?php print $content['box_4']; ?>
  </div>
  <div class="box-5 box">
    <?php print $content['box_5']; ?>
  </div>
  <div class="box-6 box last">
    <?php print $content['box_6']; ?>
  </div>

</section>
