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

  <? if ($page->content && $page->content->count()): ?>

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

<? include("./sponsors.inc"); ?>
<? include("./children.inc"); ?>
<? include("./gallery.inc"); ?>
<? include("./back-to-parent.inc"); ?>
