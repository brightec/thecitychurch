<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<section class="layout-twelve panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top grid_12 alpha omega">
  	<div class="border"></div>
    <?php print $content['wide']; ?>
  </div>

  <div class="grid_12 alpha heading">
    <?php print $content['heading']; ?>
  </div>  

  <div class="grid_12 alpha omega main">
    <?php print $content['main']; ?>
  </div>

</section>
