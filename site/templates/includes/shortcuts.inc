<? if ($page->shortcuts && $page->shortcuts->count()): ?>
<div class="section">
  <div class="row button-cards">
      <? foreach($page->shortcuts as $shortcut): ?>
      <div class="col s4">
        <a class="card hoverable waves-effect" href="<? echo $shortcut->reference->url ?>">
          <div class="card-content">
            <h5 class="flow-text truncate"><i class="material-icons"><? echo $shortcut->icon ?></i><br><? echo $shortcut->reference->title ?></h5>
          </div>
        </a>
      </div>
      <? endforeach; ?>
  </div>
</div>
<? endif; ?>
