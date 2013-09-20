//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2013 Richel Bilderbeek

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

namespace RichelBilderbeek {

struct QtResources
{
  ///Creates all resources needed
  ///Will throw a std::logic_error, as these must be supplied in the
  ///Qt resource file
  QtResources();
  const std::string GetBackground() const noexcept { return "RichelbilderbeekNlBackground.png"; }
  const std::string GetBep() const noexcept { return "ProjectWtWebsiteBep.png"; }
  const std::string GetBlack() const noexcept { return "PicBlack.png"; }
  const std::string GetCl() const noexcept { return "PicCl.png"; }
  //const std::string GetCppBuilder() const noexcept { return "PicCppBuilder.png"; }
  const std::string GetDesktop() const noexcept { return "PicDesktop.png"; }
  const std::string GetGreen() const noexcept { return "PicGreen.png"; }
  //const std::string GetLinux() const noexcept { return "PicLinux.png"; }
  //const std::string GetLinuxMacWindows() const noexcept { return "PicLinuxMacWindows.png"; }
  //const std::string GetMac() const noexcept { return "PicMac.png"; }
  const std::string GetOrange() const noexcept { return "PicOrange.png"; }
  //const std::string GetQt() const noexcept { return "PicQt.png"; }
  //const std::string GetR() const noexcept { return "PicR.png"; }
  const std::string GetRed() const noexcept { return "PicRed.png"; }
  const std::string GetYellow() const noexcept { return "PicYellow.png"; }

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  const std::string GetWeb() const noexcept { return "PicWeb.png"; }
  const std::string GetWindows() const noexcept { return "PicWindows.png"; }

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  static bool IsRegularFile(const std::string& filename) noexcept;

};


} //~namespace RichelBilderbeek

} //~namespace ribi

#endif // QTRICHELBILDERBEEKGALLERYRESOURCES_H
