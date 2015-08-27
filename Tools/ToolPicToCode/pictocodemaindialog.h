//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#ifndef PICTOCODEMAINDIALOG_H
#define PICTOCODEMAINDIALOG_H

#include <string>
#include <vector>

#include "about.h"

#include "pictocodegraphicslibrary.h"
#include "pictocodeyximage.h"

struct QImage;

namespace ribi {
namespace p2c {

struct MainDialog
{
  MainDialog();

  void SetClassName(const std::string& class_name) noexcept { m_class_name = class_name; }
  void SetHeaderFileName(const std::string& header_filename) noexcept { m_header_filename = header_filename; }
  void SetInputFile(const std::string& filename);
  void SetInputImage(const QImage& image);
  void SetGraphicsLibrary(const GraphicsLibrary graphics_library) noexcept { m_graphics_library = graphics_library; }

  std::vector<std::string> ToHeaderFile() const;
  std::vector<std::string> ToImplementationFile() const;


  private:
  std::string m_class_name;
  GraphicsLibrary m_graphics_library;
  std::string m_header_filename;
  YxImage m_image;


  std::vector<std::string> ToNdsHeaderFile() const;
  std::vector<std::string> ToNdsImplementationFile() const;
  std::vector<std::string> ToQtHeaderFile() const;
  std::vector<std::string> ToQtImplementationFile() const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


} //~namespace p2c
} //~namespace ribi

#endif // PICTOCODEMAINDIALOG_H
