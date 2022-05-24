/* BRIEF DESCRIPTION OF SCRIPT'S PURPOSE.

   developer:   estevaot
   requires:    
                
  ========================================================================== */

/* ==========================================================================
   Function for the left-side/header menu
   ========================================================================== */

  const leftSide = document.querySelector(".left-side");
  const openBtn  = document.querySelector("#header-dropdown-menu");

  if(openBtn!=undefined) {
    const dropdownCloseBtn = document.querySelector("#dropdown-topics-menu-close");

    if(dropdownCloseBtn!=undefined) {
      openBtn.addEventListener('click',function(){
        leftSide.classList.add("show-menu");
      });

      dropdownCloseBtn.addEventListener('click',function(){
        leftSide.classList.remove("show-menu")
      });
    }
  }

/* ==========================================================================
   Search animation
   ========================================================================== */

  const header = document.querySelector("header");
  const headerSearchForm  = document.querySelector("header form");
  const headerSearchBtn   = document.querySelector("header #search .search-btn");

  if(headerSearchBtn!=undefined) {

    const headerSearchClose = document.querySelector("header #search-close");

    headerSearchBtn.addEventListener('click',function(e){
      header.classList.add('openSearch');
      searchInput = document.getElementsByName('query')[0];
      if(searchInput!=undefined)
        searchInput.focus();
    });

    headerSearchClose.addEventListener('click',function(e){
      header.classList.remove('openSearch');
    });
  }

/* ==========================================================================
   Show more/less breadcrumbs
   ========================================================================== */

  const breadcrumbsNavs  = document.querySelectorAll("#content nav.breadcrumbs");

  if(breadcrumbsNavs!=undefined) {

    breadcrumbsNavs.forEach(function(element) {

      breadcrumbs = element.querySelectorAll(".breadcrumb")

      if(breadcrumbs.length > 3) { 
        
        // navBreadcrumbs  = element
        viewMoreBcrumbs = element.querySelector("a.show-more");
        viewLessBcrumbs = element.querySelector("a.show-less");
        
        if(viewMoreBcrumbs!=undefined && viewLessBcrumbs!=undefined) {

          viewMoreBcrumbs.classList.remove('display-n');

          viewMoreBcrumbs.addEventListener('click',function(e){
            this.classList.add('display-n');
            this.parentElement.classList.add('open');
            this.nextElementSibling.classList.remove('display-n');
          });

          viewLessBcrumbs.addEventListener('click',function(e){
            this.classList.add('display-n');
            this.parentElement.classList.remove('open');
            this.previousElementSibling.classList.remove('display-n');
          });
        } 
      }
    })
  }
  
/* ==========================================================================
   Auto populate Wolfram Alpha Pod
   ========================================================================== */  
  window.addEventListener('load', function(){
      var linktext = document.querySelectorAll('.try ul li a');
      if(typeof linktext != undefined && linktext[0] != undefined){
          linktext = linktext[0].textContent;
      		document.querySelectorAll('#WAwidget .WAwidget-wrapper form input')[0].value = linktext;
      }
  });