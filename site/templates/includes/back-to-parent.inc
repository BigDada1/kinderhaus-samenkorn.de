<? if ($page != $home): ?>
<div class="section">
  <div class="row">
    <div class="col">
      <p class="center"><a class="action" href="<? echo $page->parent->url ?>"><i class="material-icons">arrow_back</i><? echo $page->parent->title ?></a></p>
    </div>
  </div>
</div>
<? endif; ?>
