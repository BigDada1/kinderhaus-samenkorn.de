<? if ($page->slider && $page->slider->count()): ?>
<div class="section">
  <div class="slider">
    <ul class="slides">
      <? foreach($page->slider as $slide): ?>
      <? if ($slide->content->count() && $slide->content->first()->image): ?>
      <li>
        <div class="img" style="background-image: url('<? echo $slide->content->first()->image->size(1280, 350)->url ?>')">
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
      </li>
      <? endif; ?>
      <? endforeach; ?>
    </ul>
  </div>
</div>
<? endif; ?>
