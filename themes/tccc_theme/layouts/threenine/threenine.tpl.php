<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<section class="layout-threenine panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top">
  	<div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>

	<div class="grid_3 alpha">
    <div class="left">
	    <?php print $content['left']; ?>
    </div>
	</div>

	<div class="grid_9 omega">
    <div class="right">
	    <?php print $content['right']; ?>
    </div>
	</div>  

  <div class="wide-bottom">
  	<div class="border"></div>  
    <?php print $content['wide-bottom']; ?>
  </div>  
  
</section>
