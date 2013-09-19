//---------------------------------------------------------------------------
/*
RichelbilderbeekNlSitemapGenerator, generates the richelbilderbeek.nl sitemap
Copyright (C) 2010-2012 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsitemapgeneratormaindialog.h"

#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>
#include <QKeyEvent>

#include "ui_qtsitemapgeneratormaindialog.h"
#pragma GCC diagnostic pop

ribi::QtSitemapGeneratorMainDialog::QtSitemapGeneratorMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSitemapGeneratorMainDialog)
{
  ui->setupUi(this);
}

ribi::QtSitemapGeneratorMainDialog::~QtSitemapGeneratorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtSitemapGeneratorMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QtHideAndShowDialog::keyPressEvent(e);
}

const std::vector<std::string> ribi::QtSitemapGeneratorMainDialog::GetFilesInFolder(const std::string& folder)
{
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Files);
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    const std::string file_name = list.at(i).fileName().toStdString();
    v.push_back(file_name);
  }
  return v;
}

const std::vector<std::string> ribi::QtSitemapGeneratorMainDialog::GetHtmlFilesInFolder(const std::string& folder)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a correct HTML filename
  const boost::xpressive::sregex cpp_file_regex
    = boost::xpressive::sregex::compile(".*\\.(html|htm)\\>");

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  BOOST_FOREACH(const std::string& s, v)
  {
    if (boost::xpressive::regex_match(s,cpp_file_regex)) w.push_back(s);
  }
  return w;
}

const std::vector<std::string> ribi::QtSitemapGeneratorMainDialog::AddHeader(const std::vector<std::string>& files)
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

const std::string ribi::QtSitemapGeneratorMainDialog::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

const std::string ribi::QtSitemapGeneratorMainDialog::GetCurrentFolder(const std::string& s)
{
  return GetPath(s);
}

const std::string ribi::QtSitemapGeneratorMainDialog::GetCurrentFolder()
{
  QString s = QApplication::applicationDirPath();
  return s.toStdString();
}

const std::vector<std::string> ribi::QtSitemapGeneratorMainDialog::CreateConfigXml(
  const std::string& local_website_path,
  const std::string& urllist_path)
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

//v.push_back("     lastmod=\"2007-07-28T01:00:00-07:00\"");
//Returns date in YYYY-MM-DD format
//From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
const std::string ribi::QtSitemapGeneratorMainDialog::GetDateIso8601()
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
    if (month.size() == 1) month = std::string("0") + month;
  }
  assert(month.size() == 2);
  std::string day;
  {
    std::stringstream s;
    s << (now->tm_mday);
    day = s.str();
    if (day.size() == 1) day = std::string("0") + month;
  }
  assert(day.size() == 2);
  return year + "-" + month + "-" + day;
}

//From http://www.richelbilderbeek.nl/CppFileExists.htm
//bool FileExists(const std::string& filename)
//{
//  std::fstream f;
//  f.open(filename.c_str(),std::ios::in);
//  return f.is_open();
//}

//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> ribi::QtSitemapGeneratorMainDialog::FileToVector(const std::string& fileName)
{
  assert(QFile::exists(fileName.c_str()));
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}

void ribi::QtSitemapGeneratorMainDialog::on_button_start_clicked()
{
  const std::string page_location = ui->edit_website->text().toStdString();
  const std::string sitemapgen_location = GetCurrentFolder();

  ui->text_output->clear();

  ui->text_output->appendPlainText(
      QString("* This application runs in the folder \'")
    + QString(sitemapgen_location.c_str())
    + QString("'"));

  ui->text_output->appendPlainText(
      QString("* Searching for HTML files found in folder '")
    + QString(page_location.c_str())
    + QString("\'"));

  const std::vector<std::string> files_raw = GetHtmlFilesInFolder(page_location);


  if (files_raw.empty())
  {
    ui->text_output->appendPlainText(
        QString("* No HTML files found in folder '")
      + QString(page_location.c_str())
      + QString("\'"));
    ui->text_output->appendPlainText(
      "* Please select the correct folder with the websites' HTML files");
    return;
  }

  ui->text_output->appendPlainText(
      QString("* ")
    + QString(boost::lexical_cast<std::string>(files_raw.size()).c_str())
    + QString(" HTML files found in folder '")
    + QString(page_location.c_str())
    + QString("\'"));

  //BOOST_FOREACH(const std::string& s,files_raw) std::clog << s << '\n';

  //Save config.xml to file CreateConfigXml()
  {
    assert(!GetCurrentFolder().empty());
    assert(GetCurrentFolder().at(GetCurrentFolder().size() - 1));
    const std::string config_filename = GetCurrentFolder() + "/config.xml";

    ui->text_output->appendPlainText(
      (std::string("* Creating '")
      + config_filename +
      std::string("' in this app's folder")).c_str()
    );
    std::ofstream file(config_filename);
    std::vector<std::string> config_file(CreateConfigXml(page_location,sitemapgen_location));
    std::copy(config_file.begin(),config_file.end(),std::ostream_iterator<std::string>(file,"\n"));
    ui->text_output->appendPlainText(
      (std::string("'")
      + config_filename
      + std::string("' created successfully")).c_str()
    );
  }

  //Save urllist to file
  {
    //Convert short filenames to full filenames
    std::vector<std::string> files_full;
    BOOST_FOREACH(const std::string& line, files_raw)
    {
      files_full.push_back("http://www.richelbilderbeek.nl/" + line);
    }
    //Add header to full filenames
    const std::vector<std::string> full_files_with_header = AddHeader(files_full);
    ui->text_output->appendPlainText("* Saving urllist.txt in this app's folder");
    const std::string sitemapgen_url_list_filename = sitemapgen_location + "/urllist.txt";
    std::ofstream file(sitemapgen_url_list_filename.c_str());
    std::copy(full_files_with_header.begin(),full_files_with_header.end(),std::ostream_iterator<std::string>(file,"\n"));
  }

  //Check for sitemap_gen.py
  {
    ui->text_output->appendPlainText("* Check for sitemap_gen.py in this app's folder");
    const std::string sitemap_file
      = sitemapgen_location + std::string("/sitemap_gen.py");
    if (QFile::exists(sitemap_file.c_str()))
    {
      ui->text_output->appendPlainText("* sitemap_gen.py present");
    }
    else
    {
      ui->text_output->appendPlainText("* creating sitemap_py");
      QFile f_in(":/files/sitemap_gen.py");
      f_in.copy(sitemap_file.c_str());

      //std::ifstream f_in(":/files/sitemap_gen.py");

      //std::ofstream f_out(sitemap_file.c_str() );
      //f_out << f_in.rdbuf();

      //Assume file does exist now
      assert(QFile::exists(sitemap_file.c_str()));
      ui->text_output->appendPlainText("* sitemap_py created successfully");
    }
  }

  const std::string python_command
    = "python "
    + sitemapgen_location
    + "/sitemap_gen.py"
    + " --config="
    + sitemapgen_location
    + "/config.xml > output.txt";

  ui->text_output->appendPlainText("* Starting following command:");
  ui->text_output->appendPlainText(python_command.c_str());

  //#define DO_NOT_EXECUTE_COMMAND
  #ifdef DO_NOT_EXECUTE_COMMAND
    ui->text_output->appendPlainText("* DEBUG: COMMAND NOT EXECUTED ");
  #else
  const int system_return_code = std::system(python_command.c_str());
  ui->text_output->appendPlainText(
      QString("* System command finished with return code ")
    + QString(boost::lexical_cast<std::string>(system_return_code).c_str()));
  #endif

  ui->text_output->appendPlainText("* Program finished");

  {
    const std::vector<std::string> output(FileToVector("output.txt"));
    BOOST_FOREACH(const std::string& s,output)
    {
      ui->text_output->appendPlainText(
        QString(" ") + QString(s.c_str()));
    }
  }

  ui->text_output->appendPlainText("* Now copy sitemap.xml.gz to website manually");
}

