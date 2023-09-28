<div class="section">
  <div class="row">
    <h5>
      <? echo $page->get('title_long|title') ?>
      <? if ($page->editable()): ?>
      <a href="<? echo $page->editUrl ?>" title="'<? echo $page->title ?>' bearbeiten">✎</a>
      <? endif; ?>
    </h5>
    <? if ($page->abstract): ?>
    <p class="abstract"><? echo $page->abstract ?></p>
    <? endif; ?>
  </div>

  <div class="row">
    <? foreach($page->content as $content): ?>
    <? if ($content->image): ?>
    <div class="col m6 l5 offset-l1">
      <div class="card">
        <div class="card-image">
          <img class="body-image" src="<? echo $content->image->size(550)->url ?>" alt="<? echo $content->image->image_description ?>">
        </div>
      </div>
      <? if ($content->image->image_description): ?>
      <p class="caption"><?
        echo $content->image->image_description;
        if ($content->image->copyright) {
          echo " –&nbsp;© {$content->image->copyright}";
        }
        ?></p>
      <? endif; ?>
    </div>
    <div class="col m6 l5">
      <? echo $content->body ?>
    </div>
    <? else: ?>
    <div class="col m8 offset-m2">
      <? echo $content->body ?>
    </div>
    <? endif; ?>
    <? endforeach; ?>
  </div>

  <div class="row">
    <div class="col center">
      <? foreach($page->downloads as $file): ?>
      <p>
        <a class="action" href="<? echo $file->url ?>" target="_blank">
          <i class="material-icons">file_download</i>
          <? echo "{$file->get('description|basename')} ({$file->filesizeStr})"; ?>
        </a>
      </p>
      <? endforeach; ?>
    </div>
  </div>

  <? if ($page != $home): ?>
  <div class="col">
    <p class="center"><a class="action" href="<? echo $page->parent->url ?>"><i class="material-icons">arrow_back</i><? echo $page->parent->title ?></a></p>
  </div>
  <? endif; ?>
</div>
