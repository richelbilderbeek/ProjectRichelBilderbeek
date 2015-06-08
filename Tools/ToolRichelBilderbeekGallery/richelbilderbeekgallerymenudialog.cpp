//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "richelbilderbeekgallerymenudialog.h"

#include <cassert>
#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlfile.h"
#include "qtrichelbilderbeekgalleryresources.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"
#pragma GCC diagnostic pop

ribi::GalleryMenuDialog::GalleryMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::GalleryMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateHtmlClassGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToHtml(c2h::HeaderType::cpp,"CppClassGallery.htm");
  }

  v.push_back("<p>My <a href=\"CppClassGallery.htm\">class gallery</a> shows the <a href=\"CppClass.htm\">classes</a> I've made.");
  v.push_back("I also have a <a href=\"GameGallery.htm\">game gallery</a>, <a href=\"ProjectGallery.htm\">project gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<Program>> ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program>& p: ps)
  {
    if (dynamic_cast<ProgramClass*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToHtml(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  v.push_back("</div>");

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToHtml(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}



std::vector<std::string> ribi::GalleryMenuDialog::CreateHtmlGameGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToHtml(c2h::HeaderType::cpp,"GameGallery.htm");
  }
  v.push_back("<p>My <a href=\"GameGallery.htm\">game gallery</a> shows the <a href=\"Games.htm\">games</a> I've made.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"ProjectGallery.htm\">project gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for(const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramGame*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToHtml(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  v.push_back("</div>");

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToHtml(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}



std::vector<std::string> ribi::GalleryMenuDialog::CreateHtmlProjectGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToHtml(c2h::HeaderType::cpp,"ProjectGallery.htm");
  }

  v.push_back("<p>My <a href=\"ProjectGallery.htm\">project gallery</a> shows the <a href=\"Projects.htm\">projects</a> I've worked on.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"GameGallery.htm\">game gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for(const boost::shared_ptr<Program>& p: ps)
  {
    if (dynamic_cast<ProgramProject*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToHtml(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  v.push_back("</div>");

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToHtml(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateHtmlStatus() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToHtml(c2h::HeaderType::cpp,"CppRichelBilderbeekStatus.htm");
  }

  QtResources r;

  v.push_back("<table border=\"1\">");
  v.push_back(
    "<tr>"
      "<th>Name</th>"
      "<th><img src=\"" +  r.GetCl() +"\" alt=\"Console application\"/></th>"
      "<th><img src=\"" +  r.GetWindows() +"\" alt=\"Desktop (Windows only) application\"/></th>"
      "<th><img src=\"" +  r.GetDesktop() +"\" alt=\"Desktop application\"/></th>"
      "<th><img src=\"" +  r.GetWeb() +"\" alt=\"Web application\"/></th>"
    "</tr>");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v,r](const boost::shared_ptr<Program>& p)
    {
      std::string s
        = "<tr>"
          "<td><a href=\""+p->GetUrl()+"\">" + p->GetName() + "</a></td>";
      for (int j=0; j!=4; ++j)
      {
        ProgramStatus status =  ProgramStatus::unk;
        switch (j)
        {
          case 0: status = p->GetStatusConsole(); break;
          case 1: status = p->GetStatusDesktopWindowsOnly(); break;
          case 2: status = p->GetStatusDesktop(); break;
          case 3: status = p->GetStatusWebApplication(); break;
        }
        std::string filename;
        switch (status)
        {
          case ProgramStatus::yes: filename = r.GetGreen(); break;
          case ProgramStatus::no: filename = r.GetRed(); break;
          case ProgramStatus::nvr: filename = r.GetBlack(); break;
          case ProgramStatus::n_a: filename = r.GetBlack(); break;
          case ProgramStatus::wip: filename = r.GetYellow(); break;
          case ProgramStatus::tbd: filename = r.GetOrange(); break;
          case ProgramStatus::unk: filename = r.GetBlack(); break;
        }
        s += "<td><img src=\"" + filename +"\" alt=\""+ filename +"\"/></td>";
      }
      s+="</tr>";
      v.push_back(s);
    }
  );

  v.push_back("</table>");

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToHtml(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateHtmlToolGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToHtml(c2h::HeaderType::cpp,"ToolGallery.htm");
  }

  v.push_back("<p>My <a href=\"ToolGallery.htm\">tool gallery</a> shows the <a href=\"Tools.htm\">tools</a> I've made.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"GameGallery.htm\">game gallery</a> and <a href=\"ProjectGallery.htm\">project gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramTool*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToHtml(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  v.push_back("</div>");

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToHtml(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateMarkdownClassGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToMarkdown(c2h::HeaderType::cpp,"CppClassGallery.md");
  }

  v.push_back("My class gallery shows the classes I've made.");
  v.push_back(
    "I also have a [game gallery](http://richelbilderbeek.nl/GameGallery.htm), "
    "[project gallery](http://richelbilderbeek.nl/ProjectGallery.htm) "
    "and [tool gallery](http://richelbilderbeek.nl/ToolGallery.htm)"
  );
  v.push_back(" ");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramClass*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToMarkdown(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToMarkdown(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateMarkdownGameGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToMarkdown(c2h::HeaderType::cpp,"GameGallery.md");
  }

  v.push_back("My game gallery shows the games I've made.");
  v.push_back(
    "I also have a [class gallery](http://richelbilderbeek.nl/CppClassGallery.htm), "
    "[project gallery](http://richelbilderbeek.nl/ProjectGallery.htm) "
    "and [tool gallery](http://richelbilderbeek.nl/ToolGallery.htm)"
  );
  v.push_back(" ");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramGame*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToMarkdown(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToMarkdown(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateMarkdownProjectGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToMarkdown(c2h::HeaderType::cpp,"ProjectGallery.md");
  }

  v.push_back("My project gallery shows the projects I've made.");
  v.push_back(
    "I also have a [class gallery](http://richelbilderbeek.nl/CppClassGallery.htm), "
    "[game gallery](http://richelbilderbeek.nl/GameGallery.htm) "
    "and [tool gallery](http://richelbilderbeek.nl/ToolGallery.htm)"
  );
  v.push_back(" ");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramProject*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToMarkdown(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToMarkdown(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::CreateMarkdownToolGallery() const noexcept
{
  std::vector<std::string> v;

  //Add header
  {
    v = c2h::Header::ToMarkdown(c2h::HeaderType::cpp,"ToolGallery.md");
  }

  v.push_back("My tool gallery shows the tools I've made.");
  v.push_back(
    "I also have a [class gallery](http://richelbilderbeek.nl/CppClassGallery.htm), "
    "[game gallery](http://richelbilderbeek.nl/GameGallery.htm) "
    "and [project gallery](http://richelbilderbeek.nl/ProjectGallery.htm)"
  );
  v.push_back(" ");

  const std::vector<boost::shared_ptr<Program> > ps = Program::GetAllPrograms();

  for (const boost::shared_ptr<Program> p: ps)
  {
    if (dynamic_cast<ProgramProject*>(p.get()))
    {
      //Add HTML
      std::vector<std::string> w = ToMarkdown(*p.get());
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  //Add footer
  {
    const std::vector<std::string> w { c2h::Footer::ToMarkdown(c2h::FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

ribi::About ribi::GalleryMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RichelBilderbeekGallery",
    "gallery of Richel Bilderbeek's work",
    "the 20st of February 2012",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Program version: " + Program::GetVersion());
  a.AddLibrary("ProgramStatus version: " + ProgramStatusVersion::GetVersion());
  return a;
}

ribi::Help ribi::GalleryMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('g',"gallery","creates the Richel Bilderbeek's gallery web pages")
    },
    {
      "GalleryConsole -g",
      "GalleryConsole --gallery"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::GalleryMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramRichelBilderbeekGallery
  };
  assert(p);
  return p;
}

std::string ribi::GalleryMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::GalleryMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-02-20: Version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::GalleryMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //Just do everything
  {
    GalleryMenuDialog().CreateHtmlClassGallery();
    GalleryMenuDialog().CreateHtmlGameGallery();
    GalleryMenuDialog().CreateHtmlProjectGallery();
    GalleryMenuDialog().CreateHtmlStatus();
    GalleryMenuDialog().CreateHtmlToolGallery();
    GalleryMenuDialog().CreateMarkdownClassGallery();
    //GalleryMenuDialog().CreateMarkdownGameGallery();
    //GalleryMenuDialog().CreateMarkdownProjectGallery();
    //GalleryMenuDialog().CreateMarkdownStatus();
    //GalleryMenuDialog().CreateMarkdownToolGallery();
  }
}
#endif

std::vector<std::string> ribi::GalleryMenuDialog::ToHtml(const Program& p) const noexcept
{
  std::vector<std::string> v;
  {
    const std::string s
      = "<h2 style=\"border:5px solid;background-color:#BBBBBB\">&nbsp;<br/><a href=\""
      + p.GetUrl()
      + "\">"
      + p.GetScreenName()
      + "</a><br/>&nbsp;</h2>";
    v.push_back(s);
  }
  if (!p.GetFilenameDesktopWindowsOnly().empty())
  {
    v.push_back("<p>&nbsp;</p>");
    const std::string s
      = "<p><img src=\""
      + p.GetFilenameDesktopWindowsOnly()
      + "\" alt=\""
      + p.GetScreenName()
      + "\"/></p>";
      //+ "\" width=\"383\" height=\"400\"/></p>"
    v.push_back(s);
  }
  if (!p.GetFilenameDesktop().empty())
  {
    v.push_back("<p>&nbsp;</p>");
    const std::string s
      = "<p><img src=\""
      + p.GetFilenameDesktop()
      + "\" alt=\""
      + p.GetScreenName()
      + "\"/></p>";
      //+ "\" width=\"383\" height=\"400\"/></p>"
    v.push_back(s);
  }
  if (!p.GetFilenameWeb().empty())
  {
    v.push_back("<p>&nbsp;</p>");
    const std::string s
      = "<p><img src=\""
      + p.GetFilenameWeb()
      + "\" alt=\""
      + p.GetScreenName()
      + "\"/></p>";
      //+ "\" width=\"383\" height=\"400\"/></p>"
    v.push_back(s);
  }
  for (int i=0; i!=5; ++i) v.push_back("<p>&nbsp;</p>");
  return v;
}

std::vector<std::string> ribi::GalleryMenuDialog::ToMarkdown(const Program& p) const noexcept
{
  std::vector<std::string> v;
  {
    const std::string s = p.GetScreenName();
    v.push_back(s);
    v.push_back(std::string(s.size(),'-'));
    v.push_back(" ");
  }
  if (!p.GetFilenameDesktopWindowsOnly().empty())
  {
    const std::string s = "![" + p.GetScreenName() + "](" + p.GetFilenameDesktopWindowsOnly() + ")";
    v.push_back(s);
    v.push_back(" ");
  }
  if (!p.GetFilenameDesktop().empty())
  {
    const std::string s = "![" + p.GetScreenName() + "](" + p.GetFilenameDesktop() + ")";
    v.push_back(s);
    v.push_back(" ");
  }
  if (!p.GetFilenameWeb().empty())
  {
    const std::string s = "![" + p.GetScreenName() + "](" + p.GetFilenameWeb() + ")";
    v.push_back(s);
    v.push_back(" ");
  }
  return v;
}
