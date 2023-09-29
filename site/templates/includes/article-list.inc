<div class="section highlight minor">
  <div class="row">
    <div class="col">
      <a class="action right" href="<? echo $articles->url ?>">Alle <span class="hide-on-small-only">anzeigen</span></a>
      <h5><? echo $articles->title ?></h5>
    </div>
  </div>
  <div class="row flex site-cards">
    <? foreach($articles->children as $article): ?>
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
          ?>" alt="Abschluss Sommerprojekt">
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
