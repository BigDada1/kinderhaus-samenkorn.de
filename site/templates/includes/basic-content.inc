<header>
  <h1><?
echo $page->title;
if ($page->editable())
{
  echo " <a href='{$page->editUrl}' title='\"{$page->title}\" bearbeiten'>✎</a>";
}
?></h1>
<?
$width = 1200;
$height = 440;
if ($page->template == "parish" || $page->template == "kindergarden")
{
  $imageUrl = "/assets/img/churches/default.png";
  if(count($page->image))
  {
    $imageUrl = $page->image->first()->size($width, $height)->HTTPURL;
  }
  echo "<span class=\"image main\"><img src=\"$imageUrl\" alt=\"{$page->title}\"></span>";
}

echo $page->body;

if ($page->template == "parish" || $page->template == "kindergarden")
{
  echo "<hr>";
}

if ($page->template == "parish" || $page->template == "kindergarden")
{
  $address = $page->address;
  $phone = $page->phone;
  $fax = $page->fax;
  $email = $page->email;
  $externalUrl = $page->external_url;
  echo "<p>";
  echo "<strong>{$page->title_long}</strong><br>";
  if($address) {
    echo "$address<br>";
  }
  if($phone) {
    $internationalNumber = $phone;
    if(substr($internationalNumber, 0, 1) === "0") {
      $internationalNumber = substr_replace($internationalNumber, "+49", 0, 1);
      $internationalNumber = str_replace(' ', '', $internationalNumber);
    }
    echo "Telefon: <a href=\"tel:$internationalNumber\">$phone</a>";
    if($fax) {
      echo " · Fax: $fax";
    }
    echo "<br>";
  }
  if($email) {
    echo "<a href=\"mailto:$email\">$email</a><br>";
  }
  if($externalUrl) {
     // in case scheme relative URI is passed, e.g., //www.google.com/
     $input = trim($externalUrl, '/');

     // If scheme not included, prepend it
     if (!preg_match('#^http(s)?://#', $input)) {
         $input = 'http://' . $input;
     }

     $urlParts = parse_url($input);

     // remove www
     $domain = preg_replace('/^www\./', '', $urlParts['host']);
     echo "<a href=\"$externalUrl\" target=\"_blank\">$domain</a><br>";
  }
  echo "</p>";
}
?>
</header>
<hr>

