<?php

  
function _tccc_header() {
  $output = '';
  $output .= '<header>';
  
  $output .= '<div class="grid_3 alpha">';
  $output .= (drupal_is_front_page()) ? '<h1>' : '';
  $output .= l('<span>The City Church</span>', '', array('attributes' => array('id' => 'logo'), 'html' => TRUE));
  $output .= (drupal_is_front_page()) ? '</h1>' : '';
  $output .= '</div>';
  
  $output .= '<div class="grid_4 omega other-locations">';
  $output .= '<div class="b">';  
  $output .= drupal_render(drupal_get_form('search_form') );
  $output .= '<div id="header_sites">';
  $output .= '<a class="canterbury first" href="/canterbury">canterbury</a>';
  $output .= '<a class="whitstable last" href="/whitstable">whitstable</a>';
  $output .= '<div id="footer_tag">one church, two locations</div>';
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</div>';
  
  $output .= '<nav id="nav1" class="clearfix grid_8 alpha omega">';
  $output .= drupal_render(_tccc_header_menu());
  $output .= '</nav>'; 
  $output .= '<script type="text/javascript">
                $("#nav1 > ul.menu > li > ul.menu").css("visibility", "hidden");  
              </script>';
  
  $output .= '</header>';
  return $output;
}


function _tccc_header_menu() {
  $tree = menu_tree_all_data('main-menu');
  return menu_tree_output($tree);
}


function _tccc_footer() {
  $output = '';
  $output .= '<footer>';
  $output .= '<div class="b">';
  
  $output .= '<div id="footer_text">';
  $output .='The City Church meets in <a href="/canterbury">Canterbury</a> and <a href="/whitstable">Whitstable</a>&nbsp;&nbsp;&nbsp;Email: <a href="mailto:info@thecitychurch.org.uk">info@thecitychurch.org.uk</a>&nbsp;&nbsp;&nbsp;Tel: 01227 455440&nbsp;&nbsp;&nbsp;<a href="/website-credits">Website Credits</a>';
  
  $output .='<div id="footer_logos">';
  $output .='<a href="http://www.facebook.com/thecitychurchcanterbury"><img src="'.base_path().'sites/default/themes/tccc_theme/images/footer_fb.png" alt="Find us on Facebook"></a>';
  $output .='<a href="http://twitter.com/citychurchcbury"><img src="'.base_path().'sites/default/themes/tccc_theme/images/footer_twitter.png" alt="Follow us on Twitter"></a>';
  $output .='<a href="http://feeds.feedburner.com/tccc-update"><img src="'.base_path().'sites/default/themes/tccc_theme/images/footer_rss.png" alt="RSS"></a>';
  $output .='<a href="/resources"><img src="'.base_path().'sites/default/themes/tccc_theme/images/footer_audio.png" alt="Audio"></a>';
  $output .='</div>';
  $output .='</div>';

  $output .='<div id="footer_nf">';
  $output .='<a href="http://www.newfrontierstogether.org/"><img src="'.base_path().'sites/default/themes/tccc_theme/images/footer_nf.png" alt="Newfrontiers"></a>';
  $output .='The City Church Canterbury is a company limited by guarantee<br>Company Number 06732225, Registered Charity Number 1130031';
  $output .='</div>';

  $output .= '<div id="ccb-login-button">';
  $output .= l('Login', 'https://thecitychurch.ccbchurch.com/login.php', array('attributes' => array('target' => '_blank')));
  $output .= '</div>';

  
  $output .='</div>'; //end b
  $output .= '</footer>';
  return $output;
}

