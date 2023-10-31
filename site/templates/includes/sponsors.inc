<? if ($page->sponsors && $page->sponsors->count()): ?>
<div class="section">
  <? if ($page->sponsors_title): ?>
  <div class="row">
    <div class="col">
      <h5><? echo "{$page->sponsors_title}"; ?></h5>
    </div>
  </div>
  <? endif; ?>
  <div class="row flex site-cards">
    <? foreach($page->sponsors as $sponsor): ?>
    <div class="col s4 center">
      <a class="card hoverable waves-effect" href="<? echo "{$sponsor->url}"; ?>" target="_blank">
        <img class="responsive-img" src="<? echo "{$sponsor->url}"; ?>" alt="<? echo "{$sponsor->description}"; ?>">
        <h5><? echo "{$sponsor->description}"; ?></h5>
      </a>
    </div>
    <? endforeach; ?>
  </div>
</div>
<? endif; ?>
