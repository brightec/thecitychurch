<?php
/**
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 */
?>

<div class="layout-discipleshiplanding panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <article>
    <?php print $content['main']; ?>
  </article>
  
  <div>
    <?php print $content['bottom']; ?>
  </div>
  
</div>
