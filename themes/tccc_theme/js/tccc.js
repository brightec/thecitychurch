
/*
 * Media site
 */

$(document).ready(function(){
	
  /* 
   *  Mega Menu
   */
  
  $('#nav1 > ul.menu').addClass('depth-1 clearfix');
  $('.depth-1 > li > ul.menu').addClass('depth-2');
  $('.depth-2 > li.column > ul.menu').addClass('depth-3');
  $('.depth-3 > li > ul.menu').addClass('depth-4');
	$('.menu').show();
  
  var config = {    
     over: function(){
       $(this).find('.depth-2').fadeIn();
       $(this).find('.arrow-pointer').css('visibility', 'visible');
     },   
     timeout: 200,  
     out: function(){
       $(this).find('.depth-2').fadeOut();
       $(this).find('.arrow-pointer').css('visibility', 'hidden');
     }   
  };
  

  $('#nav1 .depth-1 > li').hoverIntent( config );
 
  
  $('.depth-2').css('visibility', 'visible').hide();

  

	/* Show / Hide Sub Navigation on Resources page */
  
  
      config = {    
           over: function(){
              $(this).children('a').css({ 'background' : '#dcdcdc'}); //Add background color  on hovered list item
              $(this).find('.subnav').fadeIn(); //Show the subnav
           },   
           timeout: 200,  
           out: function(){
              $(this).children('a').css({ 'background' : 'none'}); //Ditch the background
              $(this).find('.subnav').fadeOut(); //Hide the subnav             
           }   
        };  
      
      
      $('a.item-sermons').click(function(e){
        e.preventDefault();
      });
      
      
       
      $('#topnav li').hoverIntent( config );

      

			
  /*
   * General
   */
  
  /*
   * Media
   */
  $("#player-wrapper").one("click", function() {
    $vimeo_id = $('#vimeo-id').text();
    
    $(this).children('#player').fadeIn().html('<iframe src="http://player.vimeo.com/video/' + $vimeo_id + '?title=0&amp;byline=0&amp;portrait=0&amp;autoplay=1" width="640" height="360" frameborder="0"></iframe>').siblings('img').fadeOut();;
  });
    

   //Vimeo video links
    var i = 0;
    
    $(".pane-body-1 a, .pane-body-2 a, .pane-body-3 a, a.vimeo").each(function(){
    
    i = i+1;

    //vimeo
    if ($(this).attr('href').match(/vimeo\.com/i)){
      $(this).prettyPhoto({social_tools: false});
    }
  });
  

  // Audio player


  // non mp3 support

  if (!Modernizr.audio.mp3) {

    // first move the #player link outside of .html-audio-player and remove .html-audio-player
    var fileref = $("#player").attr('href');
    var player = $('.html-audio-player #player').detach();
    player.appendTo('.audio-player');
    $(".html-audio-player").remove();

    // turn #player into a flash object if we can
    AudioPlayer.setup("/profiles/thecitychurch/themes/tccc_theme/player.swf", {width: 620});
    AudioPlayer.embed("player", {
      width: 620,
      soundFile: fileref,
      autostart: 'no',
      transparentpagebg: 'yes',
      animation: 'no'
    });
  }

	// Show Audio / Hide Video
  $(".audio-toggle").click(function () {
    $(".video").hide();
		$(this).hide();
		$(".audio-player").show();
		$(".video-toggle").show();
    return false;
  });

	// Hide Audio / Show Video
  $(".video-toggle").click(function (e) {
    $(".video").show();
		$(this).hide();
		$(".audio-player").hide();
		$(".audio-toggle").show();
		return false;
  });
	
	// if no video, only show audio
	if (!$(".video").length ) {
	  $('.audio-player').show();
		$(".audio-toggle").hide();
	}

	// if no audio player
	if (!$(".audio-player").length ) {
		$(".audio-toggle").hide();
	}
	
	// If no audio & no video, hide media box
	if (!$(".audio-player").length && !$(".video").length) {
		$(".pane-sermon-multimedia").hide();
	}	



  // make sure CCB iframes are tall enough

  $('.ccb-iframe').load(function() {
    $(this).width($(this).parent().width());
  });



  var top_menu = $('.pane-menu-menu-resource-library-menu ul.menu').first();
  top_menu.find('ul.menu').hide();
  
  top_menu.children('li').hover(
    function(){
      $(this).children('ul').fadeIn();
    },
    function(){
      $(this).children('ul').fadeOut();
    }
  );
   
   
   /*
    * Front page
    */
        
    $('.pane-header-images #slideshow').cycle({ 
      pager:  '#slide-nav' 
    });
    
  /*
   * Calendar  
   */
  
  var date = new Date();
  var d = date.getDate();
  var m = date.getMonth();
  var y = date.getFullYear(); 
    
    $('#calendar').fullCalendar({
      events: "ccb-events",
      firstDay: 1,
      header:{
        left:   '',
        center: 'title',
        right:  ''
      },
	    eventRender: function(event, element) {
					console.log(event);
					var sd = event._start;
					
				  var sminutes = sd.getMinutes();
				  var shours = sd.getHours();
				  		           
				  if (sminutes < 10){
				  	sminutes = "0" + sminutes;
				  }
				  		           
				  if(shours > 11){
				    var noon = ("PM");
				  } else {
				    var noon = ("AM");
				  }        
				  		      	
					var html_content = '<h4>' + event.title + '</h4>';
					if(event.description){html_content += '<div class="event-desc"><em>Description:</em> ' + event.description + '</div>';}
					html_content += '<div class="event-dates"><em>Date(s):</em> ' + sd.getDate() + '.' + (sd.getMonth() + 1) + '.' + sd.getFullYear() + '</div>';
					html_content += '<div class="event-time"><em>Time:</em> ' + shours + ':' + sminutes  + noon + '</div>';				  
		      				  		      				 
	        element.qtip({
	            content: html_content,
							position: {corner: {tooltip: 'bottomLeft', target: 'topleft'}},
							style: { 
					      name: 'light', // Inherit from preset style,
					      tip: { // Now an object instead of a string
					         corner: 'bottomLeft', // We declare our corner within the object using the corner sub-option
					      
					         size: {
					            x: 28, // Be careful that the x and y values refer to coordinates on screen, not height or width.
					            y : 18 // Depending on which corner your tooltip is at, x and y could mean either height or width!
					         }
					      }										
					   	}
	        });
			}
    });


	$('.calendar-actions a').click(function(e){
      e.preventDefault();
      if($(this).hasClass('back')){
	    $('#calendar').fullCalendar('prev');
      } 
      if($(this).hasClass('next')){
	    $('#calendar').fullCalendar('next');
      }
    });
    
    /* Discipleship topics page */
    $('.pane-discipleship-text a.more').click(function(e){
      e.preventDefault();
      
        $(this).slideUp();
      $('.field-name-field-main-text').slideDown(function(){
      });
    });
    
  // add div to calendar
  $('#calendar .fc-content').wrap('<div class="fc-content-white" />');
  $('#calendar .fc-content-white').wrap('<div class="fc-content-outer" />');

  
});