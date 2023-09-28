  </div>
  <footer class="page-footer">
    <div class="row valign-wrapper">
      <div class="col s6 right-align"><?php echo $siteLogo ?></div>
      <div class="col s6">
      <ul>
      <?
        foreach ($settings->footer_sites as $item) {
          echo "<li><a href=\"{$item->url}\">{$item->get("title")}</a></li>";
        }
        if ($user->isLoggedin()) {
          echo "<li><a href=\"{$config->urls->admin}login/logout/\">Logout ({$user->name})</a></li>";
        }
      ?>
      </ul>
      </div>
    </div>
    <div class="footer-copyright">
      <div class="container">Copyright &copy; <?php echo date("Y") ?>
      <span class="hide-on-small-only"> · </span><br class="hide-on-med-and-up" />
      <? echo $settings->copyright ?>
      </div>
    </div>
  </footer>

  <script src="/js/materialize.min.js"></script>
  <script src="/js/init.js"></script>
</body>
</html>
