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
#ifndef QTRICHELBILDERBEEKGALLERYRESOURCES_H
#define QTRICHELBILDERBEEKGALLERYRESOURCES_H

#include <string>
#include <vector>

namespace ribi {

struct QtResources
{
  ///Creates all resources needed
  ///Will throw a std::logic_error, as these must be supplied in the
  ///Qt resource file
  QtResources();
  std::string GetBackground() const noexcept { return "RichelbilderbeekNlBackground.png"; }
  std::string GetBep() const noexcept { return "ProjectWtWebsiteBep.png"; }
  std::string GetBlack() const noexcept { return "PicBlack.png"; }
  std::string GetCl() const noexcept { return "PicCl.png"; }
  //std::string GetCppBuilder() const noexcept { return "PicCppBuilder.png"; }
  std::string GetDesktop() const noexcept { return "PicDesktop.png"; }
  std::string GetGreen() const noexcept { return "PicGreen.png"; }
  //std::string GetLinux() const noexcept { return "PicLinux.png"; }
  //std::string GetLinuxMacWindows() const noexcept { return "PicLinuxMacWindows.png"; }
  //std::string GetMac() const noexcept { return "PicMac.png"; }
  std::string GetOrange() const noexcept { return "PicOrange.png"; }
  //std::string GetQt() const noexcept { return "PicQt.png"; }
  //std::string GetR() const noexcept { return "PicR.png"; }
  std::string GetRed() const noexcept { return "PicRed.png"; }
  std::string GetYellow() const noexcept { return "PicYellow.png"; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  std::string GetWeb() const noexcept { return "PicWeb.png"; }
  std::string GetWindows() const noexcept { return "PicWindows.png"; }
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKGALLERYRESOURCES_H
