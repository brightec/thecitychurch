<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<article class="layout-fiveseven panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top grid_12 alpha omega">
  	<div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>

  <div class="grid_7 alpha push_5">
    <div class="panel-right">
	    <?php print $content['right']; ?>
    </div>
  </div>  
 
  <div class="grid_5 omega pull_7">
    <div class="panel-left">
      <?php print $content['left']; ?>
    </div>
  </div>

  <div class="wide-bottom grid_12 alpha omega">
  	<div class="border"></div>  
    <?php print $content['wide-bottom']; ?>
  </div>
  
</article>
