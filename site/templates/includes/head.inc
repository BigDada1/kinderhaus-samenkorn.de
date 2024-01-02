<? include("./init.inc") ?>
<!DOCTYPE html>
<html lang="de">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title><?php echo $siteTitle ?></title>
  <meta name="description" content="<?php echo $siteDescription ?>">
  <meta property="og:title" content="<?php echo $siteTitle ?>">
  <meta property="og:description" content="<?php echo $siteDescription ?>">
  <meta property="og:image:width" content="1200">
  <meta property="og:image:height" content="630">
  <meta property="og:image" content="<?php echo $siteImage->size(1200, 630)->HTTPURL ?>">
  <meta property="og:url" content="<?php echo $page->HTTPURL ?>">
  <link href="/css/materialize.min.css" type="text/css" rel="stylesheet" media="screen">
  <link href="/css/style.min.css" type="text/css" rel="stylesheet" media="screen">
  <link href="/css/prism.css" type="text/css" rel="stylesheet" media="screen">
  <script src="/js/spotlight.bundle.js"></script>
  <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png">
  <link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png">
  <link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png">
  <link rel="manifest" href="/site.webmanifest">
  <link rel="mask-icon" href="/safari-pinned-tab.svg" color="#789A01">
  <meta name="msapplication-TileColor" content="#789A01">
  <meta name="theme-color" content="#ffffff">

  <? if ($newsFeed): ?>
  <link rel="alternate" type="application/rss+xml" title="<?php echo $settings->site_title . " " . $articles->title ?>" href="<?php echo $newsFeed->url ?>" />
  <? endif; ?>

  <? if ($matomoUrl): ?>
  <script>
    var _paq = window._paq = window._paq || [];
    _paq.push(['disableCookies']);
    /* tracker methods like "setCustomDimension" should be called before "trackPageView" */
    _paq.push(['trackPageView']);
    _paq.push(['enableLinkTracking']);
    (function() {
      var u="<?php echo $matomoUrl ?>";
      _paq.push(['setTrackerUrl', u+'matomo.php']);
      _paq.push(['setSiteId', '<?php echo $matomoSiteId ?>']);
      var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0];
      g.async=true; g.src=u+'matomo.js'; s.parentNode.insertBefore(g,s);
    })();
  </script>
  <? endif; ?>
</head>
<body>
