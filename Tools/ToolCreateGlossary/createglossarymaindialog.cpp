
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

//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "createglossarymaindialog.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/regex.hpp>

#include "htmlpage.h"

CreateGlossaryMainDialog::CreateGlossaryMainDialog()
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

const std::vector<std::string> CreateGlossaryMainDialog::GetFilesInFolder(const std::string& folder)
{
  std::vector<std::string> v;

  const boost::filesystem::path my_folder
    = boost::filesystem::system_complete(
        boost::filesystem::path(folder));

  if (!boost::filesystem::is_directory(my_folder)) return v;

  const boost::filesystem::directory_iterator j;
  for ( boost::filesystem::directory_iterator i(my_folder);
        i != j;
        ++i)
  {
    if ( boost::filesystem::is_regular_file( i->status() ) )
    {
      const std::string filename = i->path().filename().string();
      //const std::string full_filename = folder + "/" + filename;
      v.push_back(filename);
    }
  }
  return v;
}

const std::vector<std::string> CreateGlossaryMainDialog::GetFilesInFolder(
  const std::string& folder,
  const std::string& regex_str)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a correct C++ filename
  const boost::regex regex(regex_str);

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  std::for_each(v.begin(), v.end(),
    [&w,regex](const std::string& s)
    {
      if (boost::regex_match(s,regex)) w.push_back(s);
    }
  );

  return w;
}

void CreateGlossaryMainDialog::CreatePage(
  const std::string& page_name,
  const std::string& page_url,
  const std::string& regex)
{
  const std::vector<std::string> pagenames
    = GetFilesInFolder("/home/richel/Projects/Projects/RichelbilderbeekNl",regex);

  std::vector<HtmlPage> pages;
  std::for_each(pagenames.begin(),pagenames.end(),
    [&pages](const std::string& s)
    {
      pages.push_back(HtmlPage("/home/richel/Projects/Projects/RichelbilderbeekNl/" + s));
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
          + boost::filesystem::path(p.GetFilename()).filename().string()
          + "\">"
          + p.GetTitle()
          + "</a></li>";

        s = HtmlPage::ReplaceAll(s,"&","[AMPERSAND]");
        s = HtmlPage::ReplaceAll(s,"[AMPERSAND]","&amp;");

        f << s << '\n';
      }
    }
  );

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

