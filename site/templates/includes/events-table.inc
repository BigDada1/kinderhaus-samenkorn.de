<?
$sectionClass = "section highlight minor";
$eventLimit = 6;
if ($page->template == "events") {
  $sectionClass = "section";
  $eventLimit = 100;
}
$churchDeskApiVersion = $settings->churchdesk_api_version;
$partnerToken = $settings->churchdesk_api_key;
$organizationId = $settings->churchdesk_organization_id;
$parishId = $settings->churchdesk_parish_id;
$resourceId = $settings->churchdesk_resource_id;
$icalFeed = $pages->findOne("template=event-feed,include=hidden")->httpUrl();
$categoryFilter = $page->churchdesk_category_filter;
?>
<div class="<? echo $sectionClass ?>">
  <? if ($page == $home): ?>
  <div class="row">
    <div class="col">
      <a class="action right" href="<? echo $events->url ?>">Alle <span class="hide-on-small-only">anzeigen</span></a>
      <h5><? echo $events->title ?></h5>
    </div>
  </div>
  <? endif; ?>
  <div class="row">
    <div class="col">
      <table class="highlight white">
        <thead>
          <tr>
              <th></th>
              <th>Datum</th>
              <th>Beschreibung</th>
              <th>Ort</th>
          </tr>
        </thead>
        <tbody>
    <?
    $http = new ProcessWire\WireHttp();

    $mergedEvents = [];
    for($pageMarker = 0; $pageMarker < 10; $pageMarker++)
    {
      $response = $http->getJSON("https://api2.churchdesk.com/api/$churchDeskApiVersion/events?partnerToken=$partnerToken&organizationId=$organizationId&itemsNumber=100&pageMarker=$pageMarker");
      if($response !== false)
      {
        if(sizeof($response) == 0)
        {
          break;
        }
        foreach ($response as $event)
        {
          // limit events to the next $eventLimit
          if(sizeof($mergedEvents) < $eventLimit)
          {
            $parishes = $event["parishes"];
            $categories = $event["categories"];
            foreach ($parishes as $parish)
            {
              if ($parish["id"] != $parishId)
              {
                break;
              }
              if ($categories && $categoryFilter)
              {
                foreach ($categories as $category)
                {
                  if ($category["title"] == $categoryFilter)
                  {
                    array_push($mergedEvents, $event);
                    break;
                  }
                }
              }
              else
              {
                array_push($mergedEvents, $event);
              }
            }
          }
        }
      }
      else
      {
        echo "<p>HTTP request failed: " . $http->getError() . "</p>";
      }
    }

    $result = "";
    foreach ($mergedEvents as $event)
    {
      $now = new \DateTimeImmutable("now");
      $tomorrow = new \DateTime("now");
      $tomorrow->modify('+1 day');
      $rawStartDate = new \DateTimeImmutable($event["startDate"]);
      $rawEndDate = new \DateTimeImmutable($event["endDate"]);
      $formatter = new \IntlDateFormatter('de_DE', \IntlDateFormatter::SHORT, \IntlDateFormatter::SHORT);

      $isAllDay = $event["allDay"];
      $eventTitle = $event["title"];
      $summary = $event["summary"];
      $description = $event["description"];
      $description = str_replace("<p>", "", $description);
      $description = str_replace("</p>", "<br>", $description);
      $locationObj = $event["locationObj"];
      $location = $event["locationName"];
      // if ($locationObj) {
      //   $location .= "<br>{$locationObj["address"]}, {$locationObj["zipcode"]} {$locationObj["city"]}";
      // }
      $formatter->setPattern('EEEEEE d. MMMM');
      $startDate = $formatter->format($rawStartDate);
      if ($startDate == $formatter->format($now)) {
        $startDate = "Heute";
      } elseif ($startDate == $formatter->format($tomorrow)) {
        $startDate = "Morgen";
      }
      $endDate = $formatter->format($rawEndDate);
      if ($endDate == $formatter->format($now)) {
        $endDate = "Heute";
      } elseif ($endDate == $formatter->format($tomorrow)) {
        $endDate = "Morgen";
      }

      $date = $startDate;
      if (!$isAllDay) {
        $formatter->setPattern('H.mm');
        $date .= "<br>{$formatter->format($rawStartDate)} Uhr";
      }
      if($startDate != $endDate) {
        $date .= "&nbsp;–<br>$endDate";
        if (!$isAllDay) {
          $date .= "<br>{$formatter->format($rawEndDate)} Uhr";
        }
      }
      $formatter->setPattern('M');
      $monthNumber = $formatter->format($rawStartDate);
      $formatter->setPattern('MMMM');
      $monthName = $formatter->format($rawStartDate);

      $result .= "<tr>";
      $result .= "<td class=\"month-$monthNumber\" title=\"$monthName\"> </td>";
      $result .= "<td class=\"date\">$date</td>";

      $result .= "<td>";
      $result .= "<strong>$eventTitle</strong>";
      if ($summary) {
        $result .= "<br>$summary";
      }
      if ($description) {
        $result .= "<br>$description";
      }
      $result .= "</td>";

      $result .= "<td class=\"location\">$location</td>";
      $result .= "</tr>";
    }
    echo $result;
    ?>
        </tbody>
      </table>
    </div>
  </div>
  <? if ($page->template == "events"): ?>
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
