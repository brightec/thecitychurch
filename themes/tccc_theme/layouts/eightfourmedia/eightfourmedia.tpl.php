<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<article class="layout-eightfourmedia panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="wide-top">
  	<div class="border"></div>  
    <?php print $content['wide-top']; ?>
  </div>
  <div class="media-section clearfix">
  	<div class="border"></div>  
    <?php print $content['media-section']; ?>
  </div>
  
  <div class="details-section clearfix">
    <div class="left">
	    <?php print $content['left']; ?>
    </div>

    <div class="right">
	    <?php print $content['right']; ?>
    </div>
  </div>
  <div style="clear: both"></div>  

  <div class="wide-bottom">
  	<div class="border"></div>  
    <?php print $content['wide-bottom']; ?>
  </div>  
  
</article>

