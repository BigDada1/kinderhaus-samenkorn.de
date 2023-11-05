<?

include("./includes/init.inc");

$items = $pages->find("template=article");

header('Content-type: application/xml; charset=utf-8;');
echo '<?xml version="1.0" encoding="utf-8" ?>';
?>

<rss version="2.0" xmlns:atom="http://www.w3.org/2005/Atom" xmlns:dc="http://purl.org/dc/elements/1.1/">
<channel>
  <title><? echo $settings->site_title . " " . $articles->title ?></title>
  <link><? echo $page->httpUrl() ?></link>
  <description><? echo $articles->abstract ?></description>
  <copyright>Copyright © <? echo date("Y") ?> <? echo $settings->copyright ?></copyright>
  <language>de</language>
  <atom:link href="<? echo $page->httpUrl() ?>" rel="self" type="application/rss+xml" />
<? foreach($items as $article): ?>
  <item>
    <title><? echo $article->title ?></title>
    <link><? echo $article->httpUrl() ?></link>
    <description>
<? if ($article->abstract): ?>
  <? echo htmlspecialchars("<p>{$article->abstract}</p>", ENT_QUOTES) ?>
<? endif; ?>
<? foreach($article->content as $content): ?>
  <? if ($content->image): ?>
    <? echo htmlspecialchars("<img src=\"{$content->image->size(550)->httpUrl()}\" alt=\"{$content->image->image_description}\">", ENT_QUOTES) ?>
  <? endif; ?>
  <? echo htmlspecialchars("{$content->body}", ENT_QUOTES) ?>
<? endforeach; ?>

    </description>
    <pubDate><? echo \DateTime::createFromFormat('d.m.Y', $article->date)->format(\DateTime::RFC822) ?></pubDate>
    <dc:creator><? echo $article->author ?></dc:creator>
    <guid><? echo $article->httpUrl() ?></guid>
  </item>
<? endforeach; ?>
</channel>
</rss>
