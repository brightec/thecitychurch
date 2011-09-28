<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<div class="layout-bricks panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top grid_12 alpha omega">
  	<div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>
  
  <div class="grid_4 alpha">
    <div class="panel-left-above">
	    <?php print $content['above-left']; ?>
    </div>
  </div>
  
  <div class="grid_7 prefix_1 omega">
    <div class="panel-right-above">
	    <?php print $content['above-right']; ?>
    </div>
  </div>
  
  <div class="grid_4 alpha">
    <div class="panel-left-middle">
	    <?php print $content['middle-left']; ?>
    </div>
  </div>
  <div class="grid_8 omega">
    <div class="panel-right-middle">
	    <?php print $content['middle-right']; ?>
    </div>
  </div>
  
  <div class="grid_4 alpha">
    <div class="panel-left-lower">
	    <?php print $content['lower-left']; ?>
    </div>
  </div>
  <div class="grid_7 prefix_1 omega">
    <div class="panel-right-lower">
	    <?php print $content['lower-right']; ?>
    </div>
  </div>
  <div class="wide-bottom grid_12 alpha omega">
  	<div class="border"></div>  
    <?php print $content['wide-bottom']; ?>
  </div>
  
</div>
