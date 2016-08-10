<?php
  header("Content-type: text/css");
?>
@media print {
  * {
    max-width: 100% !important;
  }

  html {
    width: 100%;
  }

  h1 {
    font-size: 30pt !important;
  }
  h2 {
    font-size: 24pt !important;
  }
  h1, h2 {
    color: #000;
    background: none;
    width: 100% !important;
    display: block;
  }
  h2, h3 {
    page-break-after: avoid;
  }

  .contextual-links-wrapper,
  .tabs,
  .language,
  .wrapper > header nav,
  .wrapper > footer,
  #admin-menu,
  #slider,
  #sidebar-right,
  #sidebar-left {
    display: none;
  }

  body,
  article {
    width: 100%;
    margin: 0;
    padding: 0;
  }

  article {
    page-break-before: always;
  }

  ul,
  img,
  li {
    page-break-inside: avoid;
  }

  @page {
    margin: 2cm;
  }

  a {
    font-weight: bolder;
    text-decoration: none;
  }
  a[href^=http]:after {
    content:" <" attr(href) "> ";
    font-size: 10pt;
  }
  a[href^="#"]:after {
    content: "";
  }
  $a:after > img {
    content: "";
  }
  a:not(:local-link):after {
    content:" <" attr(href) "> ";
    font-size: 10pt;
  }

  .wrapper:after {
    content: url(https://chart.googleapis.com/chart?cht=qr&chs=150x150&chl=<?php print $_SERVER["HTTP_REFERER"]; ?>&choe=UTF-8);
    position: absolute;
    right: 0;
    top: 0;
  }

  #logo {
    margin: 0;
    float: left;
  }

  #content {
    width: 100%;
    float: left;
  }
}

@media print and (color) {
  * {
    -webkit-print-color-adjust: exact;
    print-color-adjust: exact;
  }
}
