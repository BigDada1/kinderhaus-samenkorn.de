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
