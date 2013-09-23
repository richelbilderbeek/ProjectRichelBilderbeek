


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>ProjectRichelBilderbeek/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp at develop · richelbilderbeek/ProjectRichelBilderbeek · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="https://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <meta property="og:image" content="https://github.global.ssl.fastly.net/images/modules/logos_page/Octocat.png">
    <meta name="hostname" content="github-fe111-cp1-prd.iad.github.net">
    <meta name="ruby" content="ruby 1.9.3p194-tcs-github-tcmalloc (2012-05-25, TCS patched 2012-05-27, GitHub v1.0.36) [x86_64-linux]">
    <link rel="assets" href="https://github.global.ssl.fastly.net/">
    <link rel="xhr-socket" href="/_sockets" />
    
    


    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" /><meta content="59BC19D3:4E88:10A44E1:523FFC19" name="octolytics-dimension-request_id" />
    

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="JQM6xwVmhImc1mGv6Rq6C3yhy3/pKlQTUyHq7BYoXv8=" name="csrf-token" />

    <link href="https://github.global.ssl.fastly.net/assets/github-4d622651f87d0cfd8c33f1c020455121d2af0be0.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://github.global.ssl.fastly.net/assets/github2-2c867c2081830b4a942703b9d3d565bf90f6046d.css" media="all" rel="stylesheet" type="text/css" />
    

    

      <script src="https://github.global.ssl.fastly.net/assets/frameworks-8db79d6d3d61c3bdec72ede901c2b6dbd4a79dad.js" type="text/javascript"></script>
      <script src="https://github.global.ssl.fastly.net/assets/github-0053cb56d6961482e50d72f8e19dc915009ce6b7.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="b5479068af2118811ca4dcd8c0c29e66">

        <link data-pjax-transient rel='permalink' href='/richelbilderbeek/ProjectRichelBilderbeek/blob/255fabeeb493ad41e1aa95597700a09d19eb3ff3/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp'>
  <meta property="og:title" content="ProjectRichelBilderbeek"/>
  <meta property="og:type" content="githubog:gitrepository"/>
  <meta property="og:url" content="https://github.com/richelbilderbeek/ProjectRichelBilderbeek"/>
  <meta property="og:image" content="https://github.global.ssl.fastly.net/images/gravatars/gravatar-user-420.png"/>
  <meta property="og:site_name" content="GitHub"/>
  <meta property="og:description" content="ProjectRichelBilderbeek - Richel Bilderbeek&#39;s work"/>

  <meta name="description" content="ProjectRichelBilderbeek - Richel Bilderbeek&#39;s work" />

  <meta content="2098230" name="octolytics-dimension-user_id" /><meta content="richelbilderbeek" name="octolytics-dimension-user_login" /><meta content="10412386" name="octolytics-dimension-repository_id" /><meta content="richelbilderbeek/ProjectRichelBilderbeek" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="10412386" name="octolytics-dimension-repository_network_root_id" /><meta content="richelbilderbeek/ProjectRichelBilderbeek" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/richelbilderbeek/ProjectRichelBilderbeek/commits/develop.atom" rel="alternate" title="Recent Commits to ProjectRichelBilderbeek:develop" type="application/atom+xml" />

  </head>


  <body class="logged_out  env-production windows vis-public page-blob">
    <div class="wrapper">
      
      
      


      
      <div class="header header-logged-out">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/">
      <span class="mega-octicon octicon-logo-github"></span>
    </a>

    <div class="header-actions">
        <a class="button primary" href="/signup">Sign up</a>
      <a class="button signin" href="/login?return_to=%2Frichelbilderbeek%2FProjectRichelBilderbeek%2Fblob%2Fdevelop%2FGames%2FGameEverythingToPiecesShooter%2FUnitSpriteIndexChanger.cpp">Sign in</a>
    </div>

    <div class="command-bar js-command-bar  in-repository">

      <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
        <li class="features"><a href="/features">Features</a></li>
          <li class="enterprise"><a href="https://enterprise.github.com/">Enterprise</a></li>
          <li class="blog"><a href="/blog">Blog</a></li>
      </ul>
        <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<input type="text" data-hotkey=" s" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    
      data-repo="richelbilderbeek/ProjectRichelBilderbeek"
      data-branch="develop"
      data-sha="8df384fdff462b4e45a5b8dc6931acaddf0fc73a"
  >

    <input type="hidden" name="nwo" value="richelbilderbeek/ProjectRichelBilderbeek" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="octicon help tooltipped downwards" title="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
    </div>

  </div>
</div>


      


          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">


  <li>
  <a href="/login?return_to=%2Frichelbilderbeek%2FProjectRichelBilderbeek"
  class="minibutton with-count js-toggler-target star-button entice tooltipped upwards"
  title="You must be signed in to use this feature" rel="nofollow">
  <span class="octicon octicon-star"></span>Star
</a>
<a class="social-count js-social-count" href="/richelbilderbeek/ProjectRichelBilderbeek/stargazers">
  1
</a>

  </li>

    <li>
      <a href="/login?return_to=%2Frichelbilderbeek%2FProjectRichelBilderbeek"
        class="minibutton with-count js-toggler-target fork-button entice tooltipped upwards"
        title="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-git-branch"></span>Fork
      </a>
      <a href="/richelbilderbeek/ProjectRichelBilderbeek/network" class="social-count">
        1
      </a>
    </li>
</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author">
            <a href="/richelbilderbeek" class="url fn" itemprop="url" rel="author"><span itemprop="title">richelbilderbeek</span></a></span
          ><span class="repohead-name-divider">/</span><strong
          ><a href="/richelbilderbeek/ProjectRichelBilderbeek" class="js-current-repository js-repo-home-link">ProjectRichelBilderbeek</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">

      <div class="repository-with-sidebar repo-container ">

        <div class="repository-sidebar">
            

<div class="repo-nav repo-nav-full js-repository-container-pjax js-octicon-loaders">
  <div class="repo-nav-contents">
    <ul class="repo-menu">
      <li class="tooltipped leftwards" title="Code">
        <a href="/richelbilderbeek/ProjectRichelBilderbeek" aria-label="Code" class="js-selected-navigation-item selected" data-gotokey="c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_tags repo_branches /richelbilderbeek/ProjectRichelBilderbeek">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped leftwards" title="Issues">
          <a href="/richelbilderbeek/ProjectRichelBilderbeek/issues" aria-label="Issues" class="js-selected-navigation-item js-disable-pjax" data-gotokey="i" data-selected-links="repo_issues /richelbilderbeek/ProjectRichelBilderbeek/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>17</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped leftwards" title="Pull Requests"><a href="/richelbilderbeek/ProjectRichelBilderbeek/pulls" aria-label="Pull Requests" class="js-selected-navigation-item js-disable-pjax" data-gotokey="p" data-selected-links="repo_pulls /richelbilderbeek/ProjectRichelBilderbeek/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


    </ul>
    <div class="repo-menu-separator"></div>
    <ul class="repo-menu">

      <li class="tooltipped leftwards" title="Pulse">
        <a href="/richelbilderbeek/ProjectRichelBilderbeek/pulse" aria-label="Pulse" class="js-selected-navigation-item " data-pjax="true" data-selected-links="pulse /richelbilderbeek/ProjectRichelBilderbeek/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Graphs">
        <a href="/richelbilderbeek/ProjectRichelBilderbeek/graphs" aria-label="Graphs" class="js-selected-navigation-item " data-pjax="true" data-selected-links="repo_graphs repo_contributors /richelbilderbeek/ProjectRichelBilderbeek/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Network">
        <a href="/richelbilderbeek/ProjectRichelBilderbeek/network" aria-label="Network" class="js-selected-navigation-item js-disable-pjax" data-selected-links="repo_network /richelbilderbeek/ProjectRichelBilderbeek/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

            <div class="only-with-full-nav">
              

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/richelbilderbeek/ProjectRichelBilderbeek.git" readonly="readonly">

    <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/richelbilderbeek/ProjectRichelBilderbeek.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/richelbilderbeek/ProjectRichelBilderbeek" readonly="readonly">

    <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/richelbilderbeek/ProjectRichelBilderbeek" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <span class="octicon help tooltipped upwards" title="Get help on which URL is right for you.">
    <a href="https://help.github.com/articles/which-remote-url-should-i-use">
    <span class="octicon octicon-question"></span>
    </a>
  </span>
</p>


  <a href="http://windows.github.com" class="minibutton sidebar-button">
    <span class="octicon octicon-device-desktop"></span>
    Clone in Desktop
  </a>

                <a href="/richelbilderbeek/ProjectRichelBilderbeek/archive/develop.zip"
                   class="minibutton sidebar-button"
                   title="Download this repository as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
            </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:3849a711192624ff9b9250659dd5ed30 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:3849a711192624ff9b9250659dd5ed30 -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/richelbilderbeek/ProjectRichelBilderbeek/find/develop" data-pjax data-hotkey="t" class="js-show-file-finder" style="display:none">Show File Finder</a>

<div class="file-navigation">
  


<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="develop"
    data-ref="develop"
    role="button" aria-label="Switch branches or tags" tabindex="0">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">develop</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax>

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/richelbilderbeek/ProjectRichelBilderbeek/blob/develop/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="develop" data-skip-pjax="true" rel="nofollow" title="develop">develop</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/richelbilderbeek/ProjectRichelBilderbeek/blob/master/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" data-skip-pjax="true" rel="nofollow" title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/richelbilderbeek/ProjectRichelBilderbeek" data-branch="develop" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">ProjectRichelBilderbeek</span></a></span></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/richelbilderbeek/ProjectRichelBilderbeek/tree/develop/Games" data-branch="develop" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">Games</span></a></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/richelbilderbeek/ProjectRichelBilderbeek/tree/develop/Games/GameEverythingToPiecesShooter" data-branch="develop" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">GameEverythingToPiecesShooter</span></a></span><span class="separator"> / </span><strong class="final-path">UnitSpriteIndexChanger.cpp</strong> <span class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


  <div class="commit commit-loader file-history-tease js-deferred-content" data-url="/richelbilderbeek/ProjectRichelBilderbeek/contributors/develop/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp">
    Fetching contributors…

    <div class="participation">
      <p class="loader-loading"><img alt="Octocat-spinner-32-eaf2f5" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32-EAF2F5.gif" width="16" /></p>
      <p class="loader-error">Cannot retrieve contributors at this time</p>
    </div>
  </div>

<div id="files" class="bubble">
  <div class="file">
    <div class="meta">
      <div class="info">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
          <span>146 lines (141 sloc)</span>
        <span>6.963 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
              <a class="minibutton disabled js-entice" href=""
                 data-entice="You must be signed in to make or propose changes">Edit</a>
          <a href="/richelbilderbeek/ProjectRichelBilderbeek/raw/develop/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" class="button minibutton " id="raw-url">Raw</a>
            <a href="/richelbilderbeek/ProjectRichelBilderbeek/blame/develop/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" class="button minibutton ">Blame</a>
          <a href="/richelbilderbeek/ProjectRichelBilderbeek/commits/develop/Games/GameEverythingToPiecesShooter/UnitSpriteIndexChanger.cpp" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
            <a class="minibutton danger empty-icon js-entice" href=""
               data-entice="You must be signed in and on a branch to make or propose changes">
            Delete
          </a>
      </div><!-- /.actions -->

    </div>
        <div class="blob-wrapper data type-c js-blob-data">
        <table class="file-code file-diff">
          <tr class="file-code-line">
            <td class="blob-line-nums">
              <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>

            </td>
            <td class="blob-line-code">
                    <div class="highlight"><pre><div class='line' id='LC1'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC2'><br/></div><div class='line' id='LC3'><br/></div><div class='line' id='LC4'><span class="cp">#pragma hdrstop</span></div><div class='line' id='LC5'><br/></div><div class='line' id='LC6'><span class="cp">#include &quot;UnitSpriteIndexChanger.h&quot;</span></div><div class='line' id='LC7'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC8'><span class="cp">#include &quot;UnitConstants.h&quot;</span></div><div class='line' id='LC9'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC10'><span class="kt">int</span> <span class="n">SpriteIndexChanger</span><span class="o">::</span><span class="n">Move</span><span class="p">(</span><span class="k">const</span> <span class="n">EnumKey</span><span class="o">&amp;</span> <span class="n">key</span><span class="p">,</span> <span class="k">const</span> <span class="kt">int</span><span class="o">&amp;</span> <span class="n">index</span><span class="p">)</span> <span class="k">const</span></div><div class='line' id='LC11'><span class="p">{</span></div><div class='line' id='LC12'>&nbsp;&nbsp;<span class="k">switch</span><span class="p">(</span><span class="n">key</span><span class="p">)</span></div><div class='line' id='LC13'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC14'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">keyUp</span>   : <span class="k">return</span> <span class="n">MoveUp</span><span class="p">(</span><span class="n">index</span><span class="p">);</span></div><div class='line' id='LC15'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">keyRight</span>: <span class="k">return</span> <span class="n">MoveRight</span><span class="p">(</span><span class="n">index</span><span class="p">);</span></div><div class='line' id='LC16'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">keyDown</span> : <span class="k">return</span> <span class="n">MoveDown</span><span class="p">(</span><span class="n">index</span><span class="p">);</span></div><div class='line' id='LC17'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">keyLeft</span> : <span class="k">return</span> <span class="n">MoveLeft</span><span class="p">(</span><span class="n">index</span><span class="p">);</span></div><div class='line' id='LC18'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC19'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">index</span><span class="p">;</span></div><div class='line' id='LC20'><span class="p">}</span></div><div class='line' id='LC21'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC22'><span class="kt">int</span> <span class="n">SpriteIndexChanger</span><span class="o">::</span><span class="n">MoveUp</span><span class="p">(</span><span class="k">const</span> <span class="kt">int</span><span class="o">&amp;</span> <span class="n">index</span><span class="p">)</span> <span class="k">const</span></div><div class='line' id='LC23'><span class="p">{</span></div><div class='line' id='LC24'>&nbsp;&nbsp;<span class="k">switch</span><span class="p">(</span><span class="n">index</span><span class="p">)</span></div><div class='line' id='LC25'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC26'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, gun pointing down-right</span></div><div class='line' id='LC27'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC28'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC29'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, normal gun position</span></div><div class='line' id='LC30'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight1</span><span class="p">;</span></div><div class='line' id='LC31'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight2</span><span class="p">;</span></div><div class='line' id='LC32'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, gun pointing up-right</span></div><div class='line' id='LC33'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp1</span><span class="p">;</span></div><div class='line' id='LC34'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp2</span><span class="p">;</span></div><div class='line' id='LC35'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking down</span></div><div class='line' id='LC36'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp1</span><span class="p">;</span></div><div class='line' id='LC37'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp2</span><span class="p">;</span></div><div class='line' id='LC38'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, gun pointing down-left</span></div><div class='line' id='LC39'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC40'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC41'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, normal gun position</span></div><div class='line' id='LC42'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft1</span><span class="p">;</span></div><div class='line' id='LC43'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft2</span><span class="p">;</span></div><div class='line' id='LC44'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, gun pointing up-left</span></div><div class='line' id='LC45'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp1</span><span class="p">;</span></div><div class='line' id='LC46'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUp2</span><span class="p">;</span></div><div class='line' id='LC47'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC48'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">index</span><span class="p">;</span></div><div class='line' id='LC49'><span class="p">}</span></div><div class='line' id='LC50'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC51'><span class="kt">int</span> <span class="n">SpriteIndexChanger</span><span class="o">::</span><span class="n">MoveRight</span><span class="p">(</span><span class="k">const</span> <span class="kt">int</span><span class="o">&amp;</span> <span class="n">index</span><span class="p">)</span> <span class="k">const</span></div><div class='line' id='LC52'><span class="p">{</span></div><div class='line' id='LC53'>&nbsp;&nbsp;<span class="k">switch</span><span class="p">(</span><span class="n">index</span><span class="p">)</span></div><div class='line' id='LC54'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC55'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelerate right, normal gun position</span></div><div class='line' id='LC56'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC57'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC58'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelate right, gun pointing up-right</span></div><div class='line' id='LC59'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight2</span><span class="p">;</span></div><div class='line' id='LC60'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight1</span><span class="p">;</span></div><div class='line' id='LC61'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelate right, gun pointing down-right</span></div><div class='line' id='LC62'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight2</span><span class="p">;</span></div><div class='line' id='LC63'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight1</span><span class="p">;</span></div><div class='line' id='LC64'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking down</span></div><div class='line' id='LC65'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC66'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC67'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking up</span></div><div class='line' id='LC68'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC69'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC70'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn right, gun position up-right</span></div><div class='line' id='LC71'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight1</span><span class="p">;</span></div><div class='line' id='LC72'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpRight2</span><span class="p">;</span></div><div class='line' id='LC73'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn right, gun position horizontal</span></div><div class='line' id='LC74'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC75'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC76'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn right, gun position down-right</span></div><div class='line' id='LC77'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight1</span><span class="p">;</span></div><div class='line' id='LC78'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight2</span><span class="p">;</span></div><div class='line' id='LC79'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC80'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">index</span><span class="p">;</span></div><div class='line' id='LC81'><span class="p">}</span></div><div class='line' id='LC82'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC83'><span class="kt">int</span> <span class="n">SpriteIndexChanger</span><span class="o">::</span><span class="n">MoveDown</span><span class="p">(</span><span class="k">const</span> <span class="kt">int</span><span class="o">&amp;</span> <span class="n">index</span><span class="p">)</span> <span class="k">const</span></div><div class='line' id='LC84'><span class="p">{</span></div><div class='line' id='LC85'>&nbsp;&nbsp;<span class="k">switch</span><span class="p">(</span><span class="n">index</span><span class="p">)</span></div><div class='line' id='LC86'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC87'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, gun pointing down-right</span></div><div class='line' id='LC88'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown1</span><span class="p">;</span></div><div class='line' id='LC89'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown2</span><span class="p">;</span></div><div class='line' id='LC90'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, normal gun position</span></div><div class='line' id='LC91'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight1</span><span class="p">;</span></div><div class='line' id='LC92'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownRight2</span><span class="p">;</span></div><div class='line' id='LC93'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking right, gun pointing up-right</span></div><div class='line' id='LC94'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight1</span><span class="p">;</span></div><div class='line' id='LC95'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketRight2</span><span class="p">;</span></div><div class='line' id='LC96'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking up</span></div><div class='line' id='LC97'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown1</span><span class="p">;</span></div><div class='line' id='LC98'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown2</span><span class="p">;</span></div><div class='line' id='LC99'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, gun pointing down-left</span></div><div class='line' id='LC100'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown1</span><span class="p">;</span></div><div class='line' id='LC101'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDown2</span><span class="p">;</span></div><div class='line' id='LC102'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, normal gun position</span></div><div class='line' id='LC103'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft1</span><span class="p">;</span></div><div class='line' id='LC104'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft2</span><span class="p">;</span></div><div class='line' id='LC105'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking left, gun pointing up-left</span></div><div class='line' id='LC106'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC107'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC108'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC109'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">index</span><span class="p">;</span></div><div class='line' id='LC110'><span class="p">}</span></div><div class='line' id='LC111'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC112'><span class="kt">int</span> <span class="n">SpriteIndexChanger</span><span class="o">::</span><span class="n">MoveLeft</span><span class="p">(</span><span class="k">const</span> <span class="kt">int</span><span class="o">&amp;</span> <span class="n">index</span><span class="p">)</span> <span class="k">const</span></div><div class='line' id='LC113'><span class="p">{</span></div><div class='line' id='LC114'>&nbsp;&nbsp;<span class="k">switch</span><span class="p">(</span><span class="n">index</span><span class="p">)</span></div><div class='line' id='LC115'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC116'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelerate left, normal gun position</span></div><div class='line' id='LC117'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC118'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC119'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelate left, gun pointing up-left</span></div><div class='line' id='LC120'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft2</span><span class="p">;</span></div><div class='line' id='LC121'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft1</span><span class="p">;</span></div><div class='line' id='LC122'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Accelate left, gun pointing down-left</span></div><div class='line' id='LC123'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft2</span><span class="p">;</span></div><div class='line' id='LC124'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownLeft2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft1</span><span class="p">;</span></div><div class='line' id='LC125'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking down</span></div><div class='line' id='LC126'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC127'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDown2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC128'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Looking up</span></div><div class='line' id='LC129'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC130'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUp2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC131'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn left, gun position up-right</span></div><div class='line' id='LC132'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft1</span><span class="p">;</span></div><div class='line' id='LC133'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketUpRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketUpLeft2</span><span class="p">;</span></div><div class='line' id='LC134'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn left, gun position horizontal</span></div><div class='line' id='LC135'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft1</span><span class="p">;</span></div><div class='line' id='LC136'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketLeft2</span><span class="p">;</span></div><div class='line' id='LC137'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Turn left, gun position down-right</span></div><div class='line' id='LC138'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight1</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft1</span><span class="p">;</span></div><div class='line' id='LC139'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">TPS</span>:<span class="o">:</span><span class="n">mainCharRocketDownRight2</span><span class="o">:</span> <span class="k">return</span> <span class="n">TPS</span><span class="o">::</span><span class="n">mainCharRocketDownLeft2</span><span class="p">;</span></div><div class='line' id='LC140'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC141'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">index</span><span class="p">;</span></div><div class='line' id='LC142'><span class="p">}</span></div><div class='line' id='LC143'><span class="c1">//---------------------------------------------------------------------------</span></div><div class='line' id='LC144'><br/></div><div class='line' id='LC145'><span class="cp">#pragma package(smart_init)</span></div></pre></div>
            </td>
          </tr>
        </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2013 <span title="0.06677s from github-fe111-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/richelbilderbeek/ProjectRichelBilderbeek/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>

  </body>
</html>

