<? if ($page->slider && $page->slider->count()): ?>
<div class="section">
  <div class="carousel carousel-slider center">
    <? foreach($page->slider as $slide): ?>
    <?
    $imageUrl = "";
    if ($slide->content && $slide->content->first()) {
      $content = $slide->content->first();
      if($content->image) {
        $imageUrl = $content->image->size(1280, 400)->url;
      }
    }
    if ($slide->images && $slide->images->first()) {
      $image = $slide->images->first();
      if($image) {
        $imageUrl = $image->size(1280, 400)->url;
      }
    }
    ?>
    <? if ($imageUrl): ?>
    <div class="carousel-item" href="#" style="background-image: url('<? echo $imageUrl ?>')" >
      <div class="valign-wrapper">
        <div class="row center">
          <h2><? echo $slide->get('title_long|title') ?></h2>
          <a class="hoverable" href="<? echo $slide->url ?>"><?
            $label = $slide->title;
            if($slide->template == "gallery") {
              $label = "Ansehen";
            } elseif ($slide->template == "article") {
              $label = "Weiterlesen";
            }
            echo $label;
          ?></a>
        </div>
      </div>
    </div>
    <? endif; ?>
    <? endforeach; ?>
  </div>
</div>
<? endif; ?>
