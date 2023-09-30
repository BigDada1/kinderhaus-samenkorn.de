<? if ($page->slider && $page->slider->count()): ?>
<div class="section">
  <div class="carousel carousel-slider center">
    <? foreach($page->slider as $slide): ?>
    <? if ($slide->content->count() && $slide->content->first()->image): ?>
    <div class="carousel-item" href="#" style="background-image: url('<? echo $slide->content->first()->image->size(1280, 400)->url ?>')" >
      <div class="valign-wrapper">
        <div class="row center">
          <h2><? echo $slide->get('title_long|title') ?></h2>
          <a class="hoverable" href="<? echo $slide->url ?>"><?
            if ($slide->template == "article") {
              echo "Weiterlesen";
            } else {
             echo $slide->title;
            }
          ?></a>
        </div>
      </div>
    </div>
    <? endif; ?>
    <? endforeach; ?>
  </div>
</div>
<? endif; ?>
