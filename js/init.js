document.addEventListener('DOMContentLoaded', function() {
  var elems = document.querySelectorAll('.dropdown-trigger');
  var instances = M.Dropdown.init(elems, { coverTrigger: false, constrainWidth: false, hover: true });
});

document.addEventListener('DOMContentLoaded', function() {
  var elems = document.querySelectorAll('.sidenav');
  var instances = M.Sidenav.init(elems);
});

document.addEventListener('DOMContentLoaded', function() {
  var options = {
    onOpenStart: function(collapsible, trigger) {
      if(collapsible.firstElementChild.firstElementChild != null) {
        collapsible.firstElementChild.firstElementChild.innerHTML = "arrow_drop_up";
      }
    },
    onCloseStart: function(collapsible, trigger) {
      if(collapsible.firstElementChild.firstElementChild != null) {
        collapsible.firstElementChild.firstElementChild.innerHTML = "arrow_drop_down";
      }
    }
  };
  var elems = document.querySelectorAll('.collapsible');
  var instances = M.Collapsible.init(elems, options);
});

document.addEventListener('DOMContentLoaded', function() {
  var elems = document.querySelectorAll('.carousel');
  var instances = M.Carousel.init(elems, { fullWidth: true, indicators: true });
});
