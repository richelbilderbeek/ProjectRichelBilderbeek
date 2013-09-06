//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "createglossarymaindialog.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/function.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QDir>

#include "htmlpage.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::CreateGlossaryMainDialog::CreateGlossaryMainDialog()
{
  //std::cout << "Starting CreateGlossary version 1.1...\n\n";

  CreatePage("Command-line glossary","ClGlossary.htm","Cl.*\\.htm\\z");
  CreatePage("C++ glossary","CppGlossary.htm","Cpp.*\\.htm\\z");
  CreatePage("Game glossary","GameGlossary.htm","Game.*\\.htm\\z");
  CreatePage("Levend Cluedo glossary","LevendCluedoGlossary.htm","LevendCluedo.*\\.htm\\z");
  CreatePage("Tool glossary","ToolGlossary.htm","Tool.*\\.htm\\z");
  CreatePage("Music glossary","MusicGlossary.htm","(Music|Song|Cd).*\\.htm\\z");
  CreatePage("Sitemap","Sitemap.htm",".*\\.htm\\z");

  //std::cout << "Successfully created glossaries in folder "
  //  << boost::filesystem::path(argv[0]).parent_path().string() << "\n";
}

const std::vector<std::string> ribi::CreateGlossaryMainDialog::GetFilesInFolder(const std::string& folder)
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

const std::vector<std::string> ribi::CreateGlossaryMainDialog::GetFilesInFolder(
  const std::string& folder,
  const std::string& regex_str)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a correct C++ filename
  const boost::xpressive::sregex regex
    = boost::xpressive::sregex::compile(regex_str);

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  std::for_each(v.begin(), v.end(),
    [&w,regex](const std::string& s)
    {
      if (boost::xpressive::regex_match(s,regex)) w.push_back(s);
    }
  );

  return w;
}

const std::string ribi::CreateGlossaryMainDialog::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

void ribi::CreateGlossaryMainDialog::CreatePage(
  const std::string& page_name,
  const std::string& page_url,
  const std::string& regex)
{
  const std::vector<std::string> pagenames
    = GetFilesInFolder("/home/richel/ProjectRichelBilderbeek/Projects/RichelbilderbeekNl",regex);

  std::vector<HtmlPage> pages;
  std::for_each(pagenames.begin(),pagenames.end(),
    [&pages](const std::string& s)
    {
      pages.push_back(HtmlPage("/home/richel/ProjectRichelBilderbeek/Projects/RichelbilderbeekNl/" + s));
    }
  );

  std::sort(pages.begin(),pages.end());

  std::ofstream f(page_url.c_str());

  f
    << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n"
    << "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
    << "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\n"
    << "<head>\n"
    << "  <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"/>\n"
    << "  <title>" << page_name << "</title>\n"
    << "  <meta name=\"description\" content=\"" << page_name << "\"/>\n"
    << "  <meta name=\"keywords\" content=\"" << page_name << " table of content index overview\"/>\n"
    << "  <link rel=\"stylesheet\" href=\"Richelbilderbeek.css\" type=\"text/css\"/>\n"
    << "</head>\n"
    << "<!-- End of head, start of body -->\n"
    << "<body>\n"
    << "<p><a href=\"index.htm\">Go back to Richel Bilderbeek's homepage</a>.</p>\n"
//    << "<p><a href=\"Cpp.htm\">Go back to Richel Bilderbeek's C++ page</a>.</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<!-- Page header -->\n"
    << "<h1><a href=\"" << page_url << "\">" << page_name << "</a></h1>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>This page is generated by the\n"
    << "<a href=\"CppTools.htm\">tool</a> <a href=\"ToolCreateGlossary.htm\">CreateGlossary</a>.</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<ul>\n";

  std::for_each(pages.begin(),pages.end(),
    [&f](const HtmlPage& p)
    {
      if (p.GetTitle() == "Redirection page"
        || p.GetTitle().empty()
        || p.GetFilename().find("_old.htm") != std::string::npos)
      {
        //continue;
      }
      else
      {
        std::string s
          = "  <li><a href=\""
          + GetPath(p.GetFilename())
          + "\">"
          + p.GetTitle()
          + "</a></li>";

        s = HtmlPage::ReplaceAll(s,"&","[AMPERSAND]");
        s = HtmlPage::ReplaceAll(s,"[AMPERSAND]","&amp;");

        f << s << '\n';
      }
    }
  );

  TRACE(pagenames.size());

  f
    << "</ul>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>Number of pages: " << pagenames.size() << "</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p>&nbsp;</p>\n"
//    << "<p><a href=\"Cpp.htm\">Go back to Richel Bilderbeek's C++ page</a>.</p>\n"
    << "<p><a href=\"index.htm\">Go back to Richel Bilderbeek's homepage</a>.</p>\n"
    << "<p>&nbsp;</p>\n"
    << "<p><a href=\"http://validator.w3.org/check?uri=referer\"><img src=\"valid-xhtml10.png\" alt=\"Valid XHTML 1.0 Strict\" height=\"31\" width=\"88\" /></a></p>\n"
    << "</body>\n"
    << "</html>\n";
}

