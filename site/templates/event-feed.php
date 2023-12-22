<?
//
// See iCalendar specification RFC 5545
// https://datatracker.ietf.org/doc/html/rfc5545
//
// And validate the results
// https://icalendar.org/validator.html
//
include("./includes/init.inc");

header('Content-type: text/calendar');

$churchDeskApiVersion = $settings->churchdesk_api_version;
$partnerToken = $settings->churchdesk_api_key;
$organizationId = $settings->churchdesk_organization_id;
$parishId = $settings->churchdesk_parish_id;
$resourceId = $settings->churchdesk_resource_id;

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
      $parishes = $event["parishes"];
      foreach ($parishes as $parish)
      {
        if ($parish["id"] == $parishId)
        {
            array_push($mergedEvents, $event);
        }
      }
    }
  }
}
?>
BEGIN:VCALENDAR
VERSION:2.0
CALSCALE:GREGORIAN
X-WR-CALNAME:<? echo $page->title ?>

PRODID:-//henker.it//ProcessWire//Churchdesk//iCal Feed//EN
X-WR-TIMEZONE:Europe/Berlin
BEGIN:VTIMEZONE
TZID:Europe/Berlin
X-LIC-LOCATION:Europe/Berlin
BEGIN:DAYLIGHT
TZOFFSETFROM:+0100
TZOFFSETTO:+0200
TZNAME:CEST
DTSTART:19700329T020000
RRULE:FREQ=YEARLY;BYMONTH=3;BYDAY=-1SU
END:DAYLIGHT
BEGIN:STANDARD
TZOFFSETFROM:+0200
TZOFFSETTO:+0100
TZNAME:CET
DTSTART:19701025T030000
RRULE:FREQ=YEARLY;BYMONTH=10;BYDAY=-1SU
END:STANDARD
END:VTIMEZONE
<?
foreach ($mergedEvents as $event)
{
  $eventId = $event["id"];
  $isAllDay = $event["allDay"];
  $startDate = str_replace("-", "", $event["startDate"]);
  $startDate = str_replace(".", "", $startDate);
  $startDate = str_replace(":", "", $startDate);
  $startDate = str_replace("000Z", "Z", $startDate);
  $endDate = str_replace("-", "", $event["endDate"]);
  $endDate = str_replace(".", "", $endDate);
  $endDate = str_replace(":", "", $endDate);
  $endDate = str_replace("000Z", "Z", $endDate);
  if ($isAllDay) {
    $startDate = substr($startDate, 0, 8);
    $endDate = substr($endDate, 0, 8);
    if ($startDate == $endDate) {
      $startDate = "DTSTART;VALUE=DATE:$startDate";
      $endDate = "";
    } else {
      $startDate = "DTSTART;VALUE=DATE:$startDate";
      $endDate = "DTEND;VALUE=DATE:$endDate";
    }
  } else {
    $startDate = "DTSTART:$startDate";
    $endDate = "DTEND:$endDate";
  }
  $createdDate = str_replace("-", "", $event["createdAt"]);
  $createdDate = str_replace(".", "", $createdDate);
  $createdDate = str_replace(":", "", $createdDate);
  $createdDate = str_replace("000Z", "Z", $createdDate);
  $updatedDate = str_replace("-", "", $event["updatedAt"]);
  $updatedDate = str_replace(".", "", $updatedDate);
  $updatedDate = str_replace(":", "", $updatedDate);
  $updatedDate = str_replace("000Z", "", $updatedDate);
  $updatedDate = str_replace("T", "", $updatedDate);

  $eventTitle = $event["title"];
  $summary = $event["summary"];
  $locationObj = $event["locationObj"];
  $location = $event["locationName"];
  if ($locationObj) {
    $location .= "\, {$locationObj["address"]}\, {$locationObj["zipcode"]} {$locationObj["city"]}";
  }

  echo "BEGIN:VEVENT\r\n";
  echo "UID:$eventId\r\n";
  echo "DTSTAMP:$createdDate\r\n";
  echo "$startDate\r\n";
  if ($endDate != "") {
    echo "$endDate\r\n";
  }
  echo "SUMMARY:$eventTitle\r\n";
  echo "SEQUENCE:$updatedDate\r\n";
  echo "LOCATION:$location\r\n";
  echo "DESCRIPTION:$summary\r\n";
  echo "URL;VALUE=URI:{$home->httpUrl()}\r\n";
  echo "STATUS:CONFIRMED\r\n";
  echo "END:VEVENT\r\n";
}
?>
END:VCALENDAR
