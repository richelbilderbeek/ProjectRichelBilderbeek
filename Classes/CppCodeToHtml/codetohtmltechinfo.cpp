//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "codetohtmltechinfo.h"

#include <cassert>

#include "codetohtmlversion.h"
#include "fileio.h"
#include "qtcreatorprofile.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::c2h::TechInfo::TechInfo(const std::vector<std::string>& profile_filenames)
  :
    m_application_types{},
    m_compilers{},
    m_ides{},
    m_libraries{},
    m_operating_systems{},
    m_project_types{},
    m_standards{}
{
  //Obtain the QtCreatorProFile
  std::vector<boost::shared_ptr<const ribi::QtCreatorProFile> > profiles;
  std::transform(profile_filenames.begin(),profile_filenames.end(),
    std::back_inserter(profiles),
    [](const std::string& s)
    {
      assert(ribi::fileio::FileIo().IsRegularFile(s));
      boost::shared_ptr<const ribi::QtCreatorProFile> p(new ribi::QtCreatorProFile(s));
      return p;
    }
  );
  for (const boost::shared_ptr<const ribi::QtCreatorProFile>& profile: profiles)
  {
    if (profile->GetQt().count("gui"))
    {
      m_application_types.insert(TechInfo::ApplicationType::desktop);
    }
    if (profile->GetLibs().count("-lwt"))
    {
      m_application_types.insert(TechInfo::ApplicationType::web);
      m_libraries.insert(TechInfo::Library::wt);
    }
    //Compilers
    m_compilers.insert(TechInfo::Compiler::gpp);

    //IDE's
    m_ides.insert(TechInfo::Ide::qt_creator);

    //Libraries
    //Boost is only added when a Boost library is linked
    if (
      std::count_if(profile->GetLibs().begin(),profile->GetLibs().end(),
        [](const std::string& s)
          {
            return s.size() > 7 && s.substr(0,7) == "-lboost";
          }
        )
      )
    {
      m_libraries.insert(TechInfo::Library::boost);
    }

    if (profile->GetQt().count("core"))
    {
      m_libraries.insert(TechInfo::Library::qt);
    }

    //STL is always used
    m_libraries.insert(TechInfo::Library::stl);

    //Operating system
    m_operating_systems.insert(TechInfo::OperatingSystem::lubuntu);

    //Project type
    if (profile->GetQt().count("-gui"))
    {
      m_project_types.insert(TechInfo::ProjectType::console);
    }
    if (profile->GetQt().count("gui"))
    {
      m_project_types.insert(TechInfo::ProjectType::gui);
    }
    if (!profile->GetQt().count("-gui") && !profile->GetQt().count("gui"))
    {
      m_project_types.insert(TechInfo::ProjectType::console);
    }

    //C++ standard
    if (profile->GetQmakeCxxflags().count("-std=c++0x")
      || profile->GetQmakeCxxflags().count("-std=c++11"))
    {
      m_standards.insert(TechInfo::Standard::cpp11);
    }
    else
    {
      m_standards.insert(TechInfo::Standard::cpp98);
    }
  }

}

std::vector<std::string> ribi::c2h::TechInfo::ToHtml() const
{
  std::vector<std::string> v;
  v.push_back("<h2>Technical facts</h2>");
  v.push_back("<p>&nbsp;</p>");
  //Application types
  if (!m_application_types.empty())
  {
    v.push_back("<p><a href=\"CppApplication.htm\">Application type(s)</a></p>");
    v.push_back("<ul>");
    if (m_application_types.count(TechInfo::ApplicationType::desktop))
    {
      v.push_back("  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"CppDesktopApplication.htm\">Desktop application</a></li>");
    }
    if (m_application_types.count(TechInfo::ApplicationType::mobile))
    {
      v.push_back("  <li><img src=\"PicMobile.png\" alt=\"Mobile\"/> <a href=\"CppMobileApplication.htm\">Mobile application</a></li>");
    }
    if (m_application_types.count(TechInfo::ApplicationType::web))
    {
      v.push_back("  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"CppWebApplication.htm\">Web application</a></li>");
    }
    v.push_back("</ul>");
  }
  //Operating systems
  if (!m_operating_systems.empty())
  {
    v.push_back("<p><a href=\"CppOs.htm\">Operating system(s) or programming environment(s)</a></p>");
    v.push_back("<ul>");
    if (m_operating_systems.count(TechInfo::OperatingSystem::android))
    {
      v.push_back("  <li><img src=\"PicAndroid.png\" alt=\"Android\"/> <a href=\"CppAndroid.htm\">Android</a></li>");
    }
    if (m_operating_systems.count(TechInfo::OperatingSystem::cygwin))
    {
      v.push_back("  <li><img src=\"PicCygwin.png\" alt=\"Cygwin\"/> <a href=\"CppCygwin.htm\">Cygwin</a> 1.7.7</li>");
    }
    #ifndef _WIN32
    if (m_operating_systems.count(TechInfo::OperatingSystem::lubuntu))
    {
      v.push_back("  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"CppLubuntu.htm\">Lubuntu</a> "+ Version::GetLubuntuVersion()+" ("+Version::GetLubuntuVersionCodename()+")</li>");
    }
    #endif
    if (m_operating_systems.count(TechInfo::OperatingSystem::maemo))
    {
      v.push_back("  <li><img src=\"PicMaemo.png\" alt=\"Maemo\"/> <a href=\"CppMaemo.htm\">Maemo</a></li>");
    }
    if (m_operating_systems.count(TechInfo::OperatingSystem::nds))
    {
      v.push_back("  <li><img src=\"PicNds.png\" alt=\"NDS\"/> <a href=\"CppNds.htm\">NDS</a></li>");
    }
    if (m_operating_systems.count(TechInfo::OperatingSystem::raspbian))
    {
      v.push_back("  <li><img src=\"PicRaspbian.png\" alt=\"Raspbian\"/> <a href=\"CppRaspbian.htm\">Raspbian</a></li>");
    }
    if (m_operating_systems.count(TechInfo::OperatingSystem::symbian))
    {
      v.push_back("  <li><img src=\"PicSymbian.png\" alt=\"Symbian\"/> <a href=\"CppSymbian.htm\">Symbian</a></li>");
    }
    #ifndef _WIN32
    if (m_operating_systems.count(TechInfo::OperatingSystem::ubuntu))
    {
      v.push_back("  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"CppUbuntu.htm\">Ubuntu</a> "+ Version::GetUbuntuVersion()+" ("+Version::GetUbuntuVersionCodename()+")</li>");
    }
    #endif
    if (m_operating_systems.count(TechInfo::OperatingSystem::virtualbox))
    {
      v.push_back("  <li><img src=\"PicVirtualBox.png\" alt=\"VirtualBox\"/> <a href=\"CppVirtualBox.htm\">VirtualBox</a> " + Version::GetVirtualBoxVersion() + "</li>");
    }
    #ifdef _WIN32
    if (m_operating_systems.count(TechInfo::OperatingSystem::windows))
    {
      v.push_back("  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"CppWindows.htm\">Windows</a> XP</li>");
    }
    #endif
    if (m_operating_systems.count(TechInfo::OperatingSystem::wine))
    {
      v.push_back("  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"CppWine.htm\">Wine</a> " + Version::GetWineVersion() + "</li>");
    }
    v.push_back("</ul>");
  }
  //IDE's
  if (!m_ides.empty())
  {
    v.push_back("<p><a href=\"CppIde.htm\">IDE(s)</a>:</p>");
    v.push_back("<ul>");
    if (m_ides.count(TechInfo::Ide::command_line))
    {
      v.push_back("  <li><img src=\"PicCl.png\" alt=\"Command line\"/> command line</li>");
    }
    if (m_ides.count(TechInfo::Ide::cpp_builder))
    {
      v.push_back("  <li><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/> <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0 Enterprise edition</li>");
    }
    #ifndef _WIN32
    if (m_ides.count(TechInfo::Ide::qt_creator))
    {
      v.push_back("  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"CppQtCreator.htm\">Qt Creator</a> " + Version::GetQtCreatorVersion() + "</li>");
    }
    #else
    if (m_ides.count(TechInfo::Ide::qt_creator))
    {
      v.push_back("  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"CppQtCreator.htm\">Qt Creator</a> 2.7.2</li>");
    }
    #endif
    v.push_back("</ul>");
  }
  //Project types
  if (!m_project_types.empty())
  {
    v.push_back("<p><a href=\"CppQtProjectType.htm\">Project type</a>:</p>");
    v.push_back("<ul>");
    if (m_project_types.count(TechInfo::ProjectType::console))
    {
      v.push_back("  <li><img src=\"PicConsole.png\" alt=\"console\"/> <a href=\"CppConsoleApplication.htm\">Console application</a></li>");
    }
    if (m_project_types.count(TechInfo::ProjectType::gui))
    {
      v.push_back("  <li><img src=\"PicGui.png\" alt=\"GUI\"/> <a href=\"CppGuiApplication.htm\">GUI application</a></li>");
    }
    v.push_back("</ul>");
  }
  //C++ standard
  if (!m_standards.empty())
  {
    v.push_back("<p><a href=\"CppStandard.htm\">C++ standard</a>:</p>");
    v.push_back("<ul>");
    if (m_standards.count(TechInfo::Standard::cpp98))
    {
      v.push_back("  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/> <a href=\"Cpp98.htm\">C++98</a></li>");
    }
    if (m_standards.count(TechInfo::Standard::cpp11))
    {
      v.push_back("  <li><img src=\"PicCpp11.png\" alt=\"C++11\"/> <a href=\"Cpp11.htm\">C++11</a></li>");
    }
    v.push_back("</ul>");
  }
  //Compiler
  if (!m_compilers.empty())
  {
    v.push_back("<p><a href=\"CppCompiler.htm\">Compiler(s)</a>:</p>");
    v.push_back("<ul>");
    if (m_compilers.count(TechInfo::Compiler::gpp))
    {
      v.push_back("  <li><a href=\"CppGpp.htm\">G++</a> "+Version::GetGccVersion()+"</li>");
    }
    if (m_compilers.count(TechInfo::Compiler::bcc32))
    {
      v.push_back("  <li>Borland <a href=\"CppBcc32Exe.htm\">BCC32.EXE</a> version 6.0.10.157</li>");
    }
    v.push_back("</ul>");
  }
  //Library
  if (!m_libraries.empty())
  {
    v.push_back("<p><a href=\"CppLibrary.htm\">Libraries</a> used:</p>");
    v.push_back("<ul>");
    if (m_libraries.count(TechInfo::Library::big_int))
    {
      v.push_back("  <li><img src=\"PicBigInt.png\" alt=\"BigInt\"/> <a href=\"CppBigInt.htm\">BigInteger</a>: version 2010.04.30</li>");
    }
    if (m_libraries.count(TechInfo::Library::boost))
    {
      v.push_back("  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"CppBoost.htm\">Boost</a>: version "+Version::GetBoostVersion()+"</li>");
    }
    if (m_libraries.count(TechInfo::Library::cln))
    {
      v.push_back("  <li><img src=\"PicCln.png\" alt=\"CLN\"/> <a href=\"CppCln.htm\">CLN</a>: version 1.3.1</li>");
    }
    if (m_libraries.count(TechInfo::Library::libnds))
    {
      v.push_back("  <li><img src=\"PicLibnds.png\" alt=\"libnds\"/> <a href=\"CppLibnds.htm\">libnds</a>: version 1.4.7</li>");
    }
    if (m_libraries.count(TechInfo::Library::qt))
    {
      v.push_back("  <li><img src=\"PicQt.png\" alt=\"Qt\"/> <a href=\"CppQt.htm\">Qt</a>: version "+Version::GetQtVersion()+" (32 bit)</li>");
    }
    if (m_libraries.count(TechInfo::Library::stl))
    {
      v.push_back("  <li><img src=\"PicStl.png\" alt=\"STL\"/> <a href=\"CppStl.htm\">STL</a>: GNU ISO C++ Library, version "+Version::GetStlVersion()+"</li>");
    }
    if (m_libraries.count(TechInfo::Library::vcl))
    {
      v.push_back("  <li><img src=\"PicVcl.png\" alt=\"VCL\"/> <a href=\"CppVcl.htm\">VCL</a>: supplied with <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0 Enterprise edition");
    }
    if (m_libraries.count(TechInfo::Library::wt))
    {
      v.push_back("  <li><img src=\"PicWt.png\" alt=\"Wt\"/> <a href=\"CppWt.htm\">Wt</a>: version "+Version::GetWtVersion()+"</li>");
    }
    v.push_back("</ul>");
  }
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  return v;
}
