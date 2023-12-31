<?
$sectionClass = "section highlight minor";
$eventLimit = 6;
if ($page == $events) {
  $sectionClass = "section";
  $eventLimit = 30;
}
$churchDeskApiVersion = $settings->churchdesk_api_version;
$partnerToken = $settings->churchdesk_api_key;
$organizationId = $settings->churchdesk_organization_id;
$parishId = $settings->churchdesk_parish_id;
$resourceId = $settings->churchdesk_resource_id;
$icalFeed = $pages->findOne("template=event-feed,include=hidden")->httpUrl();
?>
<div class="<? echo $sectionClass ?>">
  <? if ($page != $events): ?>
  <div class="row">
    <div class="col">
      <a class="action right" href="<? echo $events->url ?>">Alle <span class="hide-on-small-only">anzeigen</span></a>
      <h5><? echo $events->title ?></h5>
    </div>
  </div>
  <? endif; ?>
  <div class="row simple-cards">
    <?
    $http = new ProcessWire\WireHttp();
    $response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100");

    $result = "";
    $counter = 0;
    if($response !== false)
    {
      $eventsByDate = [];
      foreach ($response as $event)
      {
        $parishes = $event["parishes"];
        $isOwnParish = false;
        foreach ($parishes as $parish)
        {
          if ($parish["id"] == $parishId)
          {
            $isOwnParish = true;
            break;
          }
        }
        if (!$isOwnParish)
        {
          continue;
        }
        $counter++;
        if($counter > $eventLimit) {
          continue;
        }
        $startDate = new \DateTimeImmutable($event["startDate"]);
        $formatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);

        $isAllDay = $event["allDay"];
        $eventTitle = $event["title"];
        $summary = $event["summary"];
        $description = $event["description"];
        $image = $event["image"];

        $imageSrc = $events->image->size(600, 338)->url;
        if($image)
        {
          $imageUrl = $image["span4_16-9"];
          if($imageUrl)
          {
            // retrieve the 600px version of the images
            $imageUrl = str_replace("span4_16-9", "span6_16-9", $imageUrl);
            $cacheKey = $event["id"];
            $base64 = $cache->get($cacheKey);
            if ($base64 == null)
            {
              $imagedata = file_get_contents($imageUrl);
              $base64 = base64_encode($imagedata);
              $expire = 60*60*24*30; // 1 month
              $cache->save($cacheKey, $base64, $expire);
            }
            $title = $image["title"];
            $imageCopyright = $image["copyright"];
            if($imageCopyright)
            {
              $title .= " &copy; $imageCopyright";
            }
            $imageSrc = "data:image/png;base64, $base64";
          }
        }

        $result .= "<div class=\"col m6 l4\">";
        $result .= "<div class=\"card\">";

        $result .= "<div class=\"card-image\">";
        $result .= "<img src=\"$imageSrc\" alt=\"$eventTitle\">";
        $result .= "<div class=\"date-block\">";
        $formatter->setPattern('MMM');
        $result .= "<div class=\"month\">". str_replace(".", "", $formatter->format($startDate)) . "</div>";
        $formatter->setPattern('d');
        $result .= "<div class=\"day\">{$formatter->format($startDate)}</div>";
        $formatter->setPattern('EEEEEE');
        $result .= "<div class=\"weekday\">{$formatter->format($startDate)}</div>";
        $formatter->setPattern('y');
        $result .= "<div class=\"year\">{$formatter->format($startDate)}</div>";
        if (!$isAllDay) {
          $formatter->setPattern('H:mm');
          $result .= "<div class=\"time\">{$formatter->format($startDate)}</div>";
        }
        $result .= "</div>";
        $result .= "</div>";

        $result .= "<div class=\"card-content\">";
        if ($summary || $description) {
          $result .= "<span class=\"card-title truncate activator\" title=\"Weitere Informationen\"><i class=\"material-icons right\">info_outline</i>$eventTitle</span>";
        } else {
          $result .= "<span class=\"card-title truncate\">$eventTitle</span>";
        }
        $result .= "</div>";

        if ($summary || $description) {
          $result .= "<div class=\"card-reveal\">";
          $result .= "<span class=\"card-title\"><i class=\"material-icons right\">close</i>$eventTitle</span>";
          $result .= "<p>$summary</p>";
          $result .= $description;
          $result .= "</div>";
        }

        $result .= "</div>";
        $result .= "</div>";
      }
    }
    else
    {
      $result .= "<p>HTTP request failed: " . $http->getError() . "</p>";
    }
    echo $result;
    ?>
  </div>
  <? if ($page == $events): ?>
  <div class="row">
    <div class="col s12  l8 offset-l2">
      <div class="card-panel">
        <p class="valign-wrapper info-text"><i class="material-icons">info_outline</i><? echo $page->newsfeed_info ?></p>
        <pre class="language-url"><span class="copyMessage">Kopiert</span><i class="material-icons copyButton" title="URL kopieren">content_copy</i>

 <code class="copiedText language-url"><? echo $icalFeed ?></code>

</pre>
      </div>
    </div>
  </div>
  <? endif; ?>
</div>
