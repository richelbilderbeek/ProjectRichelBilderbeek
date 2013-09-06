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


#include "sitemapgeneratormenudialog.h"

const ribi::About ribi::SitemapGeneratorMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "RichelbilderbeekNlSitemapGenerator",
    "generates the richelbilderbeek.nl sitemap",
    "the 15th of December 2012",
    "2010-2012",
    "http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const std::string ribi::SitemapGeneratorMenuDialog::GetVersion()
{
  return "1.3";
}

const std::vector<std::string> ribi::SitemapGeneratorMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-08-08: version 1.0: initial version");
  v.push_back("2011-09-15: version 1.1: improved code");
  v.push_back("2012-06-20: version 1.2: improved code");
  v.push_back("2012-12-15: version 1.3: made global functions static member functions, use of QtHideAndShowDialog, added some graphics to menu");
  return v;
}




