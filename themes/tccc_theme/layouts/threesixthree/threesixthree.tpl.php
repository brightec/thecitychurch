<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<article class="layout-threesixthree panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top grid_12 alpha omega">
  	<div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>
  
  <div class="grid_6 alpha push_3">
    <div class="panel-middle-column">
      <?php print $content['middle-column']; ?>
    </div>
  </div>
  
  <div class="grid_3 pull_6">
    <div class="panel-left-sidebar">
	    <?php print $content['left-sidebar']; ?>
    </div>
  </div>
  
  <div class="grid_3 omega">
    <div class="panel-right-sidebar">
	    <?php print $content['right-sidebar']; ?>
    </div>
  </div>
  
</article>
