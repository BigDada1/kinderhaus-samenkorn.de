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
$icalFeed = "https://api2.churchdesk.com/ical/resource/$parishId?organizationId=$organizationId&cache=0";
?>
<div class="<? echo $sectionClass ?>">
  <? if ($page != $events): ?>
  <div class="row">
    <div class="col">
      <a class="action right" href="<? echo $events->url ?>">Alle <span class="hide-on-small-only">anzeigen</span></a>
      <h5><? echo $events->title ?></h5>
    </div>
  </div>
  <? else: ?>
  <div class="row">
    <div class="col">
      <p class="center">Alle Termine können Sie auch bequem im <a href="<? echo $icalFeed ?>">iCal-Format</a> in ihren digitalen Kalender integrieren.</p>
    </div>
  </div>
  <? endif; ?>
  <div class="row flex">
    <?
    $http = new ProcessWire\WireHttp();
    $response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100");

    $result = "";
    $counter = 1;
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
          $formatter->setPattern('H.mm');
          $result .= "<div class=\"time\">{$formatter->format($startDate)}</div>";
        }
        $result .= "</div>";
        $result .= "</div>";

        $result .= "<div class=\"card-content\">";
        if ($summary || $description) {
          $result .= "<span class=\"card-title activator\" title=\"Weitere Informationen\">$eventTitle<i class=\"material-icons right\">info</i></span>";
        } else {
          $result .= "<span class=\"card-title\">$eventTitle</span>";
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
</div>
