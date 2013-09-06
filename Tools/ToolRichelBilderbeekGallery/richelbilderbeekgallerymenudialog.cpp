//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012 Richel Bilderbeek

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


#include "richelbilderbeekgallerymenudialog.h"

#include <cassert>

#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlpagetype.h"
#include "qtrichelbilderbeekgalleryresources.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"

namespace RichelBilderbeek {

const std::vector<std::string> GalleryMenuDialog::CreateHtmlClassGallery()
{
  std::vector<std::string> v;

  const c2h::Header h(c2h::PageType::cpp,"CppClassGallery.htm");
  const c2h::Footer f(h.GetPageType());

  //Copy the header
  v = h.ToHtml();

  v.push_back("<p>My <a href=\"CppClassGallery.htm\">class gallery</a> shows the <a href=\"CppClass.htm\">classes</a> I've made.");
  v.push_back("I also have a <a href=\"GameGallery.htm\">game gallery</a>, <a href=\"ProjectGallery.htm\">project gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v](const boost::shared_ptr<RichelBilderbeek::Program>& p)
    {
      if (dynamic_cast<RichelBilderbeek::ProgramClass*>(p.get()))
      {
        //Add HTML
        std::vector<std::string> w = ToHtml(*p.get());
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    }
  );

  v.push_back("</div>");

  //Add footer
  {
    std::vector<std::string> w = f.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

const std::vector<std::string> GalleryMenuDialog::CreateHtmlGameGallery()
{
  std::vector<std::string> v;

  const c2h::Header h(c2h::PageType::cpp,"GameGallery.htm");
  const c2h::Footer f(h.GetPageType());

  //Copy the header
  v = h.ToHtml();

  v.push_back("<p>My <a href=\"GameGallery.htm\">game gallery</a> shows the <a href=\"Games.htm\">games</a> I've made.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"ProjectGallery.htm\">project gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v](const boost::shared_ptr<RichelBilderbeek::Program>& p)
    {
      if (dynamic_cast<RichelBilderbeek::ProgramGame*>(p.get()))
      {
        //Add HTML
        std::vector<std::string> w = ToHtml(*p.get());
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    }
  );

  v.push_back("</div>");

  //Add footer
  {
    std::vector<std::string> w = f.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

const std::vector<std::string> GalleryMenuDialog::CreateHtmlProjectGallery()
{
  std::vector<std::string> v;

  const c2h::Header h(c2h::PageType::cpp,"ProjectGallery.htm");
  const c2h::Footer f(h.GetPageType());

  //Copy the header
  v = h.ToHtml();

  v.push_back("<p>My <a href=\"ProjectGallery.htm\">project gallery</a> shows the <a href=\"Projects.htm\">projects</a> I've worked on.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"GameGallery.htm\">game gallery</a> and <a href=\"ToolGallery.htm\">tool gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v](const boost::shared_ptr<RichelBilderbeek::Program>& p)
    {
      if (dynamic_cast<RichelBilderbeek::ProgramProject*>(p.get()))
      {
        //Add HTML
        std::vector<std::string> w = ToHtml(*p.get());
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    }
  );

  v.push_back("</div>");

  //Add footer
  {
    std::vector<std::string> w = f.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

const std::vector<std::string> GalleryMenuDialog::CreateHtmlStatus()
{
  std::vector<std::string> v;

  const c2h::Header h(c2h::PageType::cpp,"CppRichelBilderbeekStatus.htm");
  const c2h::Footer f(h.GetPageType());

  //Copy the header
  v = h.ToHtml();

  RichelBilderbeek::QtResources r;

  v.push_back("<table border=\"1\">");
  v.push_back(
    "<tr>"
      "<th>Name</th>"
      "<th><img src=\"" +  r.GetCl() +"\" alt=\"Console application\"/></th>"
      "<th><img src=\"" +  r.GetWindows() +"\" alt=\"Desktop (Windows only) application\"/></th>"
      "<th><img src=\"" +  r.GetDesktop() +"\" alt=\"Desktop application\"/></th>"
      "<th><img src=\"" +  r.GetWeb() +"\" alt=\"Web application\"/></th>"
    "</tr>");

  const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v,r](const boost::shared_ptr<RichelBilderbeek::Program>& p)
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
    std::vector<std::string> w = f.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

const std::vector<std::string> GalleryMenuDialog::CreateHtmlToolGallery()
{
  std::vector<std::string> v;

  const c2h::Header h(c2h::PageType::cpp,"ToolGallery.htm");
  const c2h::Footer f(h.GetPageType());

  //Copy the header
  v = h.ToHtml();

  v.push_back("<p>My <a href=\"ToolGallery.htm\">tool gallery</a> shows the <a href=\"Tools.htm\">tools</a> I've made.");
  v.push_back("I also have a <a href=\"CppClassGallery.htm\">class gallery</a>, <a href=\"GameGallery.htm\">game gallery</a> and <a href=\"ProjectGallery.htm\">project gallery</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<div style=\"text-align:center;\">");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");

  const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

  std::for_each(ps.begin(),ps.end(),
    [&v](const boost::shared_ptr<RichelBilderbeek::Program>& p)
    {
      if (dynamic_cast<RichelBilderbeek::ProgramTool*>(p.get()))
      {
        //Add HTML
        std::vector<std::string> w = ToHtml(*p.get());
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    }
  );

  v.push_back("</div>");

  //Add footer
  {
    std::vector<std::string> w = f.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  return v;
}

const About GalleryMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "RichelBilderbeekGallery",
    "gallery of Richel Bilderbeek's work",
    "the 20st of February 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("RichelBilderbeek::Program version: " + RichelBilderbeek::Program::GetVersion());
  a.AddLibrary("RichelBilderbeek::ProgramStatus version: " + RichelBilderbeek::ProgramStatusVersion::GetVersion());
  return a;
}

const std::string GalleryMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> GalleryMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-02-20: Version 1.0: initial version");
  return v;
}

void GalleryMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Just do everything
  {
    CreateHtmlClassGallery();
    CreateHtmlGameGallery();
    CreateHtmlProjectGallery();
    CreateHtmlStatus();
    CreateHtmlToolGallery();
  }
}

const std::vector<std::string> GalleryMenuDialog::ToHtml(const RichelBilderbeek::Program& p)
{
  std::vector<std::string> v;
  {
    const std::string s
      = "<h2 style=\"border:5px solid;background-color:#BBBBBB\">&nbsp;<br/><a href=\""
      + p.GetUrl()
      + "\">"
      + p.GetName()
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
      + p.GetName()
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
      + p.GetName()
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
      + p.GetName()
      + "\"/></p>";
      //+ "\" width=\"383\" height=\"400\"/></p>"
    v.push_back(s);
  }
  for (int i=0; i!=5; ++i) v.push_back("<p>&nbsp;</p>");
  return v;
}

} //~namespace RichelBilderbeek

