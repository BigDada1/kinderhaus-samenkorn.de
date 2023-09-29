<div class="section">
  <div class="row">
    <div class="col m8 offset-m2">
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
  </div>

  <? /* Skip contents with missing first body */ ?>
  <? if ($page->content && $page->content->count() && $page->content->first()->body): ?>
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

    <? /* Template 'events' only */ ?>
    <? if ($page->date): ?>
    <div class="col l10 offset-l1">
      <p class="right"><em>— <?
      if ($page->author) {
        echo "{$page->author}, ";
      }
      echo $page->date;
      ?></em></p>
    </div>
    <? endif; ?>

  </div>
  <? endif; ?>

  <? if ($page->downloads && $page->downloads->count()): ?>
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
  <? endif; ?>

  <? if ($page->hasChildren()): ?>
  <div class="row site-card">
    <div class="col">
      <? foreach($page->children as $child): ?>
      <a class="card hoverable" href="<? echo $child->url ?>">
        <?
        $imageUrl = "";
        if ($child->content && $child->content->first()) {
          $content = $child->content->first();
          if($content->image) {
            $imageUrl = $content->image->size(415, 415)->url;
          }
        }
        ?>
        <div class="card-image">
          <? if ($imageUrl): ?>
          <img src="<? echo $imageUrl ?>" alt="<? echo $child->title ?>">
          <? endif; ?>
        </div>
        <div class="card-content">
          <? if ($child->date): ?>
          <p class="header truncate"><? echo $child->date ?></p>
          <? endif; ?>
          <p class="card-title"><? echo $child->title ?></p>
          <? if ($child->abstract): ?>
          <p><? echo $child->abstract ?></p>
          <? endif; ?>
        </div>
        <div class="card-action">
          <p class="action"><i class="material-icons">arrow_forward</i> Weiterlesen</p>
        </div>
      </a>
      <? endforeach; ?>
    </div>
  </div>
  <? endif; ?>

  <? if ($page != $home): ?>
  <div class="row">
    <div class="col">
      <p class="center"><a class="action" href="<? echo $page->parent->url ?>"><i class="material-icons">arrow_back</i><? echo $page->parent->title ?></a></p>
    </div>
  </div>
  <? endif; ?>
</div>
