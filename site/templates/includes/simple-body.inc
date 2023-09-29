<? if ($page->body): ?>
<div class="section">
  <div class="row">
    <div class="col m8 offset-m2">
      <h5><? echo $page->get('title_long|title') ?></h5>
    </div>
    <div class="col m8 offset-m2 center">
      <? echo str_replace("<p>", "<p class=\"abstract\">", $page->body) ?>
    </div>
  </div>
</div>
<? endif; ?>
