<?php

// Set variables
$home = $pages->get("/");
$settings = $pages->findOne("template=settings, include=hidden");
$siteTitle = $settings->site_title;
if ($page->parent() == $home)
{
  $siteTitle .= " · {$page->title}";
}
$siteDescription = $settings->site_description;
$siteImage = $settings->site_image;
$siteLogo = $settings->site_logo;
$siteLogo = str_replace("%site_name%", $settings->site_title, $siteLogo);
$navMobileLogo = str_replace("%fill%", "#000000", $siteLogo);
$navMobileLogo = str_replace("st0", "st1", $navMobileLogo);
$siteLogo = str_replace("%fill%", "#FFFFFF", $siteLogo);
$articles = $home->findOne("template=article-list");
$events = $home->findOne("template=events");
?>
<!DOCTYPE html>
<html lang="de">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title><?php echo $siteTitle ?></title>
  <meta name="description" content="<?php echo $siteDescription ?>">
  <meta property="og:title" content="<?php echo $siteTitle ?>">
  <meta property="og:description" content="<?php echo $siteDescription ?>">
  <meta property="og:image" content="<?php echo $siteImage->size(1200, 630)->HTTPURL ?>">
  <link href="/css/materialize.min.css" type="text/css" rel="stylesheet" media="screen">
  <link href="/css/style.css" type="text/css" rel="stylesheet" media="screen">
  <link href="/css/prism.css" type="text/css" rel="stylesheet" media="screen">
  <script src="/js/spotlight.bundle.js"></script>
  <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png">
  <link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png">
  <link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png">
  <link rel="manifest" href="/site.webmanifest">
  <link rel="mask-icon" href="/safari-pinned-tab.svg" color="#006eb7">
  <meta name="msapplication-TileColor" content="#006eb7">
  <meta name="theme-color" content="#ffffff">
</head>
<body>
