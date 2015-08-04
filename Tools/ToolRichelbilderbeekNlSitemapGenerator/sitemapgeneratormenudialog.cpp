//---------------------------------------------------------------------------
/*
RichelbilderbeekNlSitemapGenerator, generates the richelbilderbeek.nl sitemap
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm
//---------------------------------------------------------------------------
#include "sitemapgeneratormenudialog.h"

#include <cassert>
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QFile>

#include "fileio.h"

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::SitemapGeneratorMenuDialog::SitemapGeneratorMenuDialog()
  : m_signal_log{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::string> ribi::SitemapGeneratorMenuDialog::AddHeader(const std::vector<std::string>& files) noexcept
{
  std::vector<std::string> v;
  v.push_back("# To add a list of URLs, make a space-delimited text file. The first");
  v.push_back("# column contains the URL; then you can specify various optional");
  v.push_back("# attributes in the form key=value:");
  v.push_back("#");
  v.push_back("# lastmod = modification time in ISO8601 (YYYY-MM-DDThh:mm:ss+00:00)");
  v.push_back("# changefreq = 'always' | 'hourly' | 'daily' | 'weekly' | 'monthly' |");
  v.push_back("# 'yearly' | 'never'");
  v.push_back("# priority = priority of the page relative to other pages on the same site;");
  v.push_back("# a number between 0.0 and 1.0, where 0.0 is the lowest priority");
  v.push_back("# and 1.0 is the highest priority");
  v.push_back("#");
  v.push_back("# Note that all URLs must be part of the site, and therefore must begin with");
  v.push_back("# the base_url (e.g., 'http://www.example.com/') as specified in config.xml.");
  v.push_back("#");
  v.push_back("# Any line beginning with a # is a comment.");
  std::copy(files.begin(),files.end(),std::back_inserter(v));
  return v;
}

std::vector<std::string> ribi::SitemapGeneratorMenuDialog::CreateConfigXml(
  const std::string& local_website_path,
  const std::string& urllist_path) noexcept
{
  std::vector<std::string> v;

  v.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
  v.push_back("<!--");
  v.push_back("  sitemap_gen.py example configuration script");
  v.push_back("");
  v.push_back("  This file specifies a set of sample input parameters for the");
  v.push_back("  sitemap_gen.py client.");
  v.push_back("");
  v.push_back("  You should copy this file into \"config.xml\" and modify it for");
  v.push_back("  your server.");
  v.push_back("");
  v.push_back("");
  v.push_back("  ********************************************************* -->");
  v.push_back("");
  v.push_back("");
  v.push_back("<!-- ** MODIFY **");
  v.push_back("  The \"site\" node describes your basic web site.");
  v.push_back("  ");
  v.push_back("  Required attributes:");
  v.push_back("    base_url   - the top-level URL of the site being mapped");
  v.push_back("    store_into - the webserver path to the desired output file.");
  v.push_back("                 This should end in '.xml' or '.xml.gz'");
  v.push_back("                 (the script will create this file)");
  v.push_back("");
  v.push_back("  Optional attributes:");
  v.push_back("    verbose    - an integer from 0 (quiet) to 3 (noisy) for");
  v.push_back("                 how much diagnostic output the script gives");
  v.push_back("    suppress_search_engine_notify=\"1\"");
  v.push_back("               - disables notifying search engines about the new map");
  v.push_back("                 (same as the \"testing\" command-line argument.)");
  v.push_back("    default_encoding");
  v.push_back("               - names a character encoding to use for URLs and");
  v.push_back("                 file paths.  (Example: \"UTF-8\")");
  v.push_back("-->");
  v.push_back("<site");
  v.push_back("  base_url=\"http://www.richelbilderbeek.nl\"");
  v.push_back("  store_into=\""+urllist_path+"/sitemap.xml.gz\"");
  v.push_back("  verbose=\"1\"");
  v.push_back("  >");
  v.push_back("");
  v.push_back("  <!-- ********************************************************");
  v.push_back("          INPUTS");
  v.push_back("");
  v.push_back("  All the various nodes in this section control where the script");
  v.push_back("  looks to find URLs.");
  v.push_back("");
  v.push_back("  MODIFY or DELETE these entries as appropriate for your server.");
  v.push_back("  ********************************************************* -->");
  v.push_back("  <!-- ** MODIFY or DELETE **");
  v.push_back("    \"url\" nodes specify individual URLs to include in the map.");
  v.push_back("");
  v.push_back("    Required attributes:");
  v.push_back("      href       - the URL");
  v.push_back("");
  v.push_back("    Optional attributes:");
  v.push_back("      lastmod    - timestamp of last modification (ISO8601 format)");
  v.push_back("      changefreq - how often content at this URL is usually updated");
  v.push_back("      priority   - value 0.0 to 1.0 of relative importance in your site");
  v.push_back("  -->");
  v.push_back("  <url");
  //v.push_back("     href=\"http://www.richelbilderbeek.nl/stats?q=name\""); //new
  v.push_back("     href=\"http://www.richelbilderbeek.nl/stats?q=age\"");
  v.push_back("     lastmod=\"" + GetDateIso8601() +"T01:00:00-07:00\"");
  //v.push_back("     changefreq=\"weekly\"");
  v.push_back("     priority=\"0.5\"");
  v.push_back("  />");
  v.push_back("");
  v.push_back("  <!-- ** MODIFY or DELETE **");
  v.push_back("    \"urllist\" nodes name text files with lists of URLs.");
  v.push_back("    An example file \"example_urllist.txt\" is provided.");
  v.push_back("");
  v.push_back("    Required attributes:");
  v.push_back("      path       - path to the file");
  v.push_back("");
  v.push_back("    Optional attributes:");
  v.push_back("      encoding   - encoding of the file if not US-ASCII");
  v.push_back("  -->");
  //v.push_back("  <urllist path=\"c:\\Progra~1\\Richel~1\\urllist.txt\"  encoding=\"UTF-8\"  />");
  v.push_back("  <urllist path=\"" + urllist_path +  "/urllist.txt\"  encoding=\"UTF-8\"  />");
  v.push_back("");
  v.push_back("  <!-- ** MODIFY or DELETE **");
  v.push_back("    \"directory\" nodes tell the script to walk the file system");
  v.push_back("    and include all files and directories in the Sitemap.");
  v.push_back("");
  v.push_back("    Required attributes:");
  v.push_back("      path       - path to begin walking from");
  v.push_back("      url        - URL equivalent of that path");
  v.push_back("");
  v.push_back("    Optional attributes:");
  v.push_back("      default_file - name of the index or default file for directory URLs");
  v.push_back("  -->");
  v.push_back("  <directory");
  //v.push_back("     path=\"C:\\docume~1\\richel~1\\mydocu~1\\richel~1\"");
  v.push_back("     path=\"" + local_website_path + "\"");
  v.push_back("     url=\"http://www.richelbilderbeek.nl\"");
  v.push_back("     default_file=\"index.html\"");
  v.push_back("  />");
  v.push_back("");
  v.push_back("  <!-- ** MODIFY or DELETE **");
  v.push_back("    \"accesslog\" nodes tell the script to scan webserver log files to");
  v.push_back("    extract URLs on your site.  Both Common Logfile Format (Apache's default");
  v.push_back("    logfile) and Extended Logfile Format (IIS's default logfile) can be read.");
  v.push_back("");
  v.push_back("    Required attributes:");
  v.push_back("      path       - path to the file");
  v.push_back("");
  v.push_back("    Optional attributes:");
  v.push_back("      encoding   - encoding of the file if not US-ASCII");
  v.push_back("  -->");
  v.push_back("");
  v.push_back("  <!-- ** MODIFY or DELETE **");
  v.push_back("    \"sitemap\" nodes tell the script to scan other Sitemap files.  This can");
  v.push_back("    be useful to aggregate the results of multiple runs of this script into");
  v.push_back("    a single Sitemap.");
  v.push_back("");
  v.push_back("    Required attributes:");
  v.push_back("      path       - path to the file");
  v.push_back("  -->");
  v.push_back("");
  v.push_back("  <!-- ********************************************************");
  v.push_back("          FILTERS");
  v.push_back("");
  v.push_back("  Filters specify wild-card patterns that the script compares");
  v.push_back("  against all URLs it finds.  Filters can be used to exclude");
  v.push_back("  certain URLs from your Sitemap, for instance if you have");
  v.push_back("  hidden content that you hope the search engines don't find.");
  v.push_back("");
  v.push_back("  Filters can be either type=\"wildcard\", which means standard");
  v.push_back("  path wildcards (* and ?) are used to compare against URLs,");
  v.push_back("  or type=\"regexp\", which means regular expressions are used");
  v.push_back("  to compare.");
  v.push_back("");
  v.push_back("  Filters are applied in the order specified in this file.");
  v.push_back("");
  v.push_back("  An action=\"drop\" filter causes exclusion of matching URLs.");
  v.push_back("  An action=\"pass\" filter causes inclusion of matching URLs,");
  v.push_back("  shortcutting any other later filters that might also match.");
  v.push_back("  If no filter at all matches a URL, the URL will be included.");
  v.push_back("  Together you can build up fairly complex rules.");
  v.push_back("");
  v.push_back("  The default action is \"drop\".");
  v.push_back("  The default type is \"wildcard\".");
  v.push_back("");
  v.push_back("  You can MODIFY or DELETE these entries as appropriate for");
  v.push_back("  your site.  However, unlike above, the example entries in");
  v.push_back("  this section are not contrived and may be useful to you as");
  v.push_back("  they are.");
  v.push_back("  ********************************************************* -->");
  v.push_back("");
  v.push_back("  <!-- Exclude URLs that end with a '~'   (IE: emacs backup files)      -->");
  v.push_back("  <filter  action=\"drop\"  type=\"wildcard\"  pattern=\"*~\"           />");
  v.push_back("");
  v.push_back("  <!-- Exclude URLs within UNIX-style hidden files or directories       -->");
  v.push_back("  <filter  action=\"drop\"  type=\"regexp\"    pattern=\"/\\.[^/]*\"     />");
  v.push_back("");
  v.push_back("</site>");
  return v;
}

int ribi::SitemapGeneratorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  ///Find page location
  std::string page_location;
  if (std::count(argv.begin(),argv.end(),"--page"))
  {
    const int index
      = std::distance(argv.begin(),std::find(argv.begin(),argv.end(),"--page"));
    assert(index < static_cast<int>(argv.size()));
    if (index == static_cast<int>(argv.size() - 1))
    {
      m_signal_log(
          "Please supply an argument after --page.\n"
          "\n"
          "For example:\n"
          "  RichelbilderbeekNlSitemapGenerator --page myhome/myhomepagefolder --exe myhome/mybin"
      );
      return 1;
    }
    page_location = argv[index + 1];
  }

  ///Find page location
  std::string sitemapgen_location;
  if (std::count(argv.begin(),argv.end(),"--exe"))
  {
    const int index
      = std::distance(argv.begin(),std::find(argv.begin(),argv.end(),"--exe"));
    assert(index < static_cast<int>(argv.size()));
    if (index == static_cast<int>(argv.size() - 1))
    {
      m_signal_log(
          "Please supply an argument after --exe.\n"
          "\n"
          "For example:\n"
          "  RichelbilderbeekNlSitemapGenerator --page myhome/myhomepagefolder --exe myhome/mybin\n"
      );
      return 1;
    }
    sitemapgen_location = argv[index + 1];
  }

  m_signal_log(
      "* This application runs in the folder \'"
    + sitemapgen_location
    + "'"
  );

  m_signal_log(
      "* Searching for HTML files found in folder '"
    + std::string(page_location)
    + "\'"
  );

  const std::vector<std::string> files_raw = GetHtmlFilesInFolder(page_location);


  if (files_raw.empty())
  {
    m_signal_log(
        "* No HTML files found in folder '"
      + std::string(page_location.c_str())
      + "\'"
    );
    m_signal_log(
      "* Please select the correct folder with the websites' HTML files"
    );
    return 1;
  }

  m_signal_log(
      "* "
    + boost::lexical_cast<std::string>(files_raw.size())
    + " HTML files found in folder '"
    + page_location
    + "\'"
  );

  //Save config.xml to file CreateConfigXml()
  {
    const std::string config_filename = "config.xml";
    //const std::string config_filename = GetCurrentFolder() + "/config.xml";

    m_signal_log(
        "* Creating '"
      + config_filename
      + "' in this app's folder"
    );
    std::ofstream file(config_filename);
    std::vector<std::string> config_file(CreateConfigXml(page_location,sitemapgen_location));
    std::copy(config_file.begin(),config_file.end(),std::ostream_iterator<std::string>(file,"\n"));
    m_signal_log(
        "'"
      + config_filename
      + "' created successfully"
    );
  }

  //Save urllist to file
  {
    //Convert short filenames to full filenames
    std::vector<std::string> files_full;
    for(const std::string& line: files_raw)
    {
      files_full.push_back("http://www.richelbilderbeek.nl/" + line);
    }
    //Add header to full filenames
    const std::vector<std::string> full_files_with_header = AddHeader(files_full);
    m_signal_log("* Saving urllist.txt in this app's folder");
    const std::string sitemapgen_url_list_filename = sitemapgen_location + "/urllist.txt";
    std::ofstream file(sitemapgen_url_list_filename.c_str());
    std::copy(full_files_with_header.begin(),full_files_with_header.end(),std::ostream_iterator<std::string>(file,"\n"));
  }

  //Check for sitemap_gen.py
  {
    m_signal_log("* Check for sitemap_gen.py in this app's folder");
    const std::string sitemap_file
      = sitemapgen_location + "/sitemap_gen.py";
    if (QFile::exists(sitemap_file.c_str()))
    {
      m_signal_log("* sitemap_gen.py present");
    }
    else
    {
      m_signal_log("* creating sitemap_py");
      QFile f_in(":/files/sitemap_gen.py");
      f_in.copy(sitemap_file.c_str());

      //Assume file does exist now
      assert(ribi::fileio::FileIo().IsRegularFile(sitemap_file));
      m_signal_log("* sitemap_py created successfully");
    }
  }

  const std::string python_command
    = "python "
    + sitemapgen_location
    + "/sitemap_gen.py"
    + " --config="
    + sitemapgen_location
    + "/config.xml > output.txt";

  m_signal_log("* Starting following command:");
  m_signal_log(python_command);

  //#define DO_NOT_EXECUTE_COMMAND
  #ifdef DO_NOT_EXECUTE_COMMAND
    m_signal_log("* DEBUG: COMMAND NOT EXECUTED ");
  #else
  const int system_return_code = std::system(python_command.c_str());
  m_signal_log(
      "* System command finished with return code "
    + boost::lexical_cast<std::string>(system_return_code)
  );
  #endif

  m_signal_log("* Program finished");

  {
    const std::vector<std::string> output(ribi::fileio::FileIo().FileToVector("output.txt"));
    for(const std::string& s: output)
    {
      m_signal_log(" " + s);
    }
  }

  m_signal_log("* Now copy sitemap.xml.gz to website manually");
  return 0;
}

ribi::About ribi::SitemapGeneratorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RichelbilderbeekNlSitemapGenerator",
    "generates the richelbilderbeek.nl sitemap",
    "the 15th of December 2012",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

std::string ribi::SitemapGeneratorMenuDialog::GetDateIso8601() noexcept
{
  const std::time_t t = std::time(0);
  const std::tm * const now = std::localtime( &t );
  std::string year;
  {
    std::stringstream s;
    s << (now->tm_year + 1900);
    year = s.str();
  }
  assert(year.size() == 4);
  std::string month;
  {
    std::stringstream s;
    s << (now->tm_mon + 1);
    month = s.str();
    if (month.size() == 1) month = "0" + month;
  }
  assert(month.size() == 2);
  std::string day;
  {
    std::stringstream s;
    s << (now->tm_mday);
    day = s.str();
    if (day.size() == 1) day = "0" + day;
  }
  assert(day.size() == 2);
  const std::string date{
    year + "-" + month + "-" + day
  };
  assert(date.size()==10);
  assert(date[4]=='-');
  assert(date[7]=='-');
  return date;
}

ribi::Help ribi::SitemapGeneratorMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}




std::vector<std::string> ribi::SitemapGeneratorMenuDialog::GetHtmlFilesInFolder(
  const std::string& folder) noexcept
{
  //Get all filenames
  const std::vector<std::string> v = ribi::fileio::FileIo().GetFilesInFolder(folder);

  //Create the regex for a correct HTML filename
  const boost::xpressive::sregex cpp_file_regex
    = boost::xpressive::sregex::compile(".*\\.(html|htm)\\>");

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  for(const std::string& s: v)
  {
    if (boost::xpressive::regex_match(s,cpp_file_regex)) w.push_back(s);
  }
  return w;
}

boost::shared_ptr<const ribi::Program> ribi::SitemapGeneratorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramRichelBilderbeekNlSitemapGenerator
  };
  assert(p);
  return p;
}

std::string ribi::SitemapGeneratorMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::SitemapGeneratorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-08: version 1.0: initial version",
    "2011-09-15: version 1.1: improved code",
    "2012-06-20: version 1.2: improved code",
    "2012-12-15: version 1.3: made global functions static member functions, use of QtHideAndShowDialog, added some graphics to menu"
  };
}

#ifndef NDEBUG
void ribi::SitemapGeneratorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  SitemapGeneratorMenuDialog d;
  assert(!d.GetDateIso8601().empty());
}
#endif
