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

  <? /* Skip contents with missing first body or first icon list */ ?>
  <? if ($page->content && $page->content->count() && ($page->content->first()->body || $page->content->first()->icon_list->count())): ?>

  <? foreach($page->content as $content): ?>
  <div class="row">
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
      <? if ($content->icon_list->count()): ?>
      <table>
        <? foreach($content->icon_list as $icon_list_item): ?>
        <tr><td><i class="material-icons"><? echo $icon_list_item->icon ?></i></td><td><?
        $text = $icon_list_item->icon_list_text;
        $text = str_replace("<p>", "", $text);
        $text = str_replace("</p>", "<br>", $text);
        echo $text;
        ?></td></tr>
        <? endforeach; ?>
      </table>
      <? endif; ?>
    </div>
    <? else: ?>
    <div class="col m8 offset-m2">
      <? echo $content->body ?>
      <? if ($content->icon_list->count()): ?>
      <table>
        <? foreach($content->icon_list as $icon_list_item): ?>
        <tr><td><i class="material-icons"><? echo $icon_list_item->icon ?></i></td><td><?
          $text = $icon_list_item->icon_list_text;
          $text = str_replace("<p>", "", $text);
          $text = str_replace("</p>", "<br>", $text);
          echo $text;
          ?></td></tr>
        <? endforeach; ?>
      </table>
      <? endif; ?>
    </div>
    <? endif; ?>
  </div>
  <? endforeach; ?>

  <? /* Template 'events' only */ ?>
  <? if ($page->date): ?>
  <div class="row">
    <div class="col l10 offset-l1">
      <p class="right"><em>— <?
      if ($page->author) {
        echo "{$page->author}, ";
      }
      echo $page->date;
      ?></em></p>
    </div>
  </div>
  <? endif; ?>

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
</div>

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

<? if ($page == $events || $page == $events->parent): ?>
<? include("./events.inc"); ?>
<? endif; ?>

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

<? include("./gallery.inc"); ?>

<? if ($page != $home): ?>
<div class="section">
  <div class="row">
    <div class="col">
      <p class="center"><a class="action" href="<? echo $page->parent->url ?>"><i class="material-icons">arrow_back</i><? echo $page->parent->title ?></a></p>
    </div>
  </div>
</div>
<? endif; ?>
