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
#ifndef SITEMAPGENERATORMENUDIALOG_H
#define SITEMAPGENERATORMENUDIALOG_H


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct SitemapGeneratorMenuDialog final : public MenuDialog
{
  SitemapGeneratorMenuDialog();
  ~SitemapGeneratorMenuDialog() noexcept {}

  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  boost::signals2::signal<void(const std::string)> m_signal_log;

  private:

  static std::vector<std::string> AddHeader(const std::vector<std::string>& files) noexcept;

  static std::vector<std::string> CreateConfigXml(
    const std::string& local_website_path,
    const std::string& urllist_path) noexcept;

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  //Returns date in YYYY-MM-DD format
  //From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
  static std::string GetDateIso8601() noexcept;

  static std::vector<std::string> GetHtmlFilesInFolder(const std::string& folder) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // SITEMAPGENERATORMENUDIALOG_H
