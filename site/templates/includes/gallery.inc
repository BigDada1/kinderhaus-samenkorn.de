<? if ($page->images && $page->images->count()): ?>
<div class="section">
  <div class="row center">
    <? foreach($page->images as $image): ?>
    <?
    $copyright = "";
    if ($image->copyright) {
      $copyright = "© {$image->copyright}";
    }
    ?>
    <a class="spotlight" href="<? echo $image->url ?>" title="<? echo $image->image_description ?>" data-description="<? echo $copyright ?>" data-src-800="<? echo $image->size(800, 533)->url ?>" data-src-1200="<? echo $image->size(1200, 800)->url ?>" data-fit="cover" data-control="page,fullscreen,close">
      <img src="<? echo $image->size(200, 133)->url ?>" alt="<? echo $image->image_description ?>">
    </a>
    <? endforeach; ?>
  </div>
</div>
<? endif; ?>
