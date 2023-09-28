<?
// render main navigation dropdown content
foreach ($home->children() as $child) {
  if ($child->hasChildren()) {
    echo "<ul id=\"{$child->id}\" class=\"dropdown-content\">\n";
    foreach ($child->children() as $subchild) {
      $listItemClass = "";
      if ($subchild->id == $page->id || $subchild->id == $page->parent->id) {
        $listItemClass = " class=\"active\"";
      }
      echo "<li$listItemClass><a href=\"{$subchild->url}\">" . $subchild->get("title") . "</a></li>\n";
    }
    echo "</ul>\n";
  }
}
?>
  <nav role="navigation">
    <div class="nav-wrapper container">
      <a id="logo-container" class="brand-logo" href="/"><?php echo $siteLogo ?></a>
      <ul class="nav-regular right hide-on-med-and-down">
<?
// render main navigation
foreach ($home->children() as $child) {
  $listItemClass = "";
  if ($child->id == $page->rootParent->id) {
    $listItemClass = " class=\"active\"";
  }
  $dropdownTarget = "";
  $dropdownIcon = "";
  if ($child->hasChildren()) {
    $dropdownTarget = " class=\"dropdown-trigger\" data-target=\"{$child->id}\"";
    $dropdownIcon = "<i class=\"material-icons right\">arrow_drop_down</i>";
  }
  echo "<li$listItemClass><a href=\"{$child->url}\"$dropdownTarget>{$child->title}$dropdownIcon</a></li>\n";
}
// render edit link
if ($page->editable()) {
  echo "<li><a href=\"{$page->editUrl}\" title=\"'$page->title' bearbeiten\">✎</a></li>\n";
}
?>
      </ul>

      <ul id="nav-mobile" class="sidenav collapsible">
        <li class="center"><?php echo $navMobileLogo ?></li>
<?
// render side navigation
foreach ($home->children() as $child) {
  $listItemClass = "";
  if ($child->id == $page->rootParent->id) {
    $listItemClass = " class=\"active\"";
  }

  $dropdownIcon = "";
  $href = " href=\"{$child->url}\"";
  if ($child->hasChildren()) {
    $dropdownIcon = "<i class=\"material-icons right\">arrow_drop_down</i>";
    $href = "";
  }

  echo "<li$listItemClass>\n";
  $anchorClass = "collapsible-header waves-effect";
  if ($child->template == "contact") {
    $anchorClass = "waves-effect";
  }
  echo "<a$href class=\"$anchorClass\">{$child->title}$dropdownIcon</a>\n";

  if ($child->hasChildren()) {
    echo "<div class=\"collapsible-body\">\n";
    echo "<ul>\n";
    $subchildren = $child->children();
    foreach ($subchildren as $subchild) {
      $listItemClass = "";
      if ($subchild->id == $page->id || $subchild->id == $page->parent->id) {
        $listItemClass = " class=\"active\"";
      }
      echo "<li$listItemClass><a href=\"{$subchild->url}\">{$subchild->title}</a></li>\n"; //subpages can have long title
    }
    echo "</ul>\n";
    echo "</div>\n";
  }
  echo "</li>\n";
}
?>
      </ul>
      <a href="#" data-target="nav-mobile" class="sidenav-trigger"><i class="material-icons">menu</i></a>
    </div>
  </nav>
  <div class="container">
