
// sorry for this messy global function!
// it's here so that the iframe can call it when it loads/reloads

function resizeIframes() {
  $('iframe').each(function() {
    this.height = (this.contentWindow.document.body.scrollHeight + 30) + 'px';
  });
}	

