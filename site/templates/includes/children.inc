<? /* Special articles layout for article-list parent */ ?>
<? if ($page == $articles->parent): ?>
<div class="section highlight minor">
  <div class="row">
    <div class="col">
      <a class="action right" href="<? echo $articles->url ?>">Alle <span class="hide-on-small-only">anzeigen</span></a>
      <h5><? echo $articles->title ?></h5>
    </div>
  </div>
  <div class="row flex site-cards">
    <? foreach($articles->children("limit=6") as $article): ?>
    <div class="col l4">
      <a class="card hoverable" href="<? echo $article->url ?>">
        <div class="card-image">
          <img src="<?
          if ($article->content && $article->content->first()) {
            $content = $article->content->first();
            if($content->image) {
              echo $content->image->size(415, 415)->url;
            }
          }
          ?>" alt="<? echo $article->title ?>">
        </div>
        <div class="card-content">
          <p class="header truncate"><? echo $article->date ?></p>
          <p class="card-title"><? echo $article->title ?></p>
        </div>
        <div class="card-action">
          <p class="action"><i class="material-icons">arrow_forward</i> Weiterlesen</p>
        </div>
      </a>
    </div>
    <? endforeach; ?>
  </div>
</div>
<? endif; ?>

<? /* Special events layout for events and events parent */ ?>
<? if ($page == $events || $page == $events->parent): ?>
<? include("./events.inc"); ?>
<? endif; ?>

<? /* Default layout */ ?>
<? if ($page->hasChildren("template!=article-list,template!=events")): ?>
<div class="section">
  <div class="row site-card">
    <div class="col">
      <? foreach($page->children("template!=article-list,template!=events") as $child): ?>
      <a class="card hoverable" href="<? echo $child->url ?>">
        <?
        $imageUrl = "";
        if ($child->content && $child->content->first()) {
          $content = $child->content->first();
          if($content->image) {
            $imageUrl = $content->image->size(415, 415)->url;
          }
        }
        if ($child->images && $child->images->first()) {
          $image = $child->images->first();
          if($image) {
            $imageUrl = $image->size(415, 415)->url;
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
          <?
          $label = "Weiterlesen";
          if($child->template == "gallery") {
            $label = "Ansehen";
          }
          ?>
          <p class="action"><i class="material-icons">arrow_forward</i> <? echo $label ?></p>
        </div>
      </a>
      <? endforeach; ?>
    </div>
  </div>
</div>
<? endif; ?>
