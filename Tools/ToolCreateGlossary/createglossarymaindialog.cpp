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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "createglossarymaindialog.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/xpressive/xpressive.hpp>

//#include <QDir>

#include "fileio.h"
#include "htmlpage.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::CreateGlossaryMainDialog::CreateGlossaryMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
  TRACE("Start of CreateGlossaryMainDialog");

  CreatePage("Command-line glossary","ClGlossary.htm","Cl.*\\.htm\\>");
  CreatePage("C++ glossary","CppGlossary.htm","Cpp.*\\.htm\\>");
  CreatePage("Game glossary","GameGlossary.htm","Game.*\\.htm\\>");
  CreatePage("Levend Cluedo glossary","LevendCluedoGlossary.htm","LevendCluedo.*\\.htm\\>");
  CreatePage("Tool glossary","ToolGlossary.htm","Tool.*\\.htm\\>");
  CreatePage("Music glossary","MusicGlossary.htm","(Music|Song|Cd).*\\.htm\\>");
  CreatePage("Sitemap","Sitemap.htm",".*\\.htm\\>");

  TRACE("Finished CreateGlossaryMainDialog successfully");
}

void ribi::CreateGlossaryMainDialog::CreatePage(
  const std::string& page_name,
  const std::string& page_url,
  const std::string& regex)
{
  const std::vector<std::string> pagenames {
    ribi::fileio::GetFilesInFolderByRegex(
      "/home/richel/ProjectRichelBilderbeek/Projects/RichelbilderbeekNl",
      regex)
  };

  std::vector<boost::shared_ptr<const HtmlPage> > pages;
  for (const std::string& s: pagenames)
  {
    const std::string full_path
      = std::string("/home/richel/ProjectRichelBilderbeek/")
      + std::string("Projects/RichelbilderbeekNl/")
      + s;
    assert(ribi::fileio::IsRegularFile(full_path));
    boost::shared_ptr<const HtmlPage> page {
      new HtmlPage(full_path)
    };
    pages.push_back(page);
  }

  std::sort(pages.begin(),pages.end(),
    [](const boost::shared_ptr<const HtmlPage> lhs,const boost::shared_ptr<const HtmlPage> rhs)
    {
     return *lhs < *rhs;
    }
  );

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

  for(const boost::shared_ptr<const HtmlPage> page: pages)
  {
    if (page->GetTitle() == "Redirection page"
      || page->GetTitle().empty()
      || page->GetFilename().find("_old.htm") != std::string::npos)
    {
      //continue;
    }
    else
    {
      std::string s
        = "  <li><a href=\""
        + ribi::fileio::RemovePath(page->GetFilename())
        + "\">"
        + page->GetTitle()
        + "</a></li>";

      s = HtmlPage::ReplaceAll(s,"&","[AMPERSAND]");
      s = HtmlPage::ReplaceAll(s,"[AMPERSAND]","&amp;");

      f << s << '\n';
    }
  }

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

#ifndef NDEBUG
void ribi::CreateGlossaryMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
}
#endif
