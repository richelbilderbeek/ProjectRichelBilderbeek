//---------------------------------------------------------------------------
/*
ImageCanvas, class to convert an image to ASCII art
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppImageCanvas.htm
//---------------------------------------------------------------------------
#ifndef NDEBUG

#include "imagecanvas.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
#include <boost/math/constants/constants.hpp>

#include <QFile>
#include <QImage>

#include "canvascolorsystems.h"
#include "canvascoordinatsystems.h"
#include "fileio.h"
#include "trace.h"
#include "testtimer.h"
#include "imagecanvas.h"

void ribi::ImageCanvas::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    CanvasColorSystems();
    CanvasCoordinatSystems();

  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string temp_filename { fileio::FileIo().GetTempFileName() };
  {
    const std::string resource_filename { ":/CppImageCanvas/images/R.png" };
    QFile qfile(resource_filename.c_str());
    qfile.copy(temp_filename.c_str());
    if (!fileio::FileIo().IsRegularFile(temp_filename))
    {
      TRACE("ERROR");
      TRACE(resource_filename);
      TRACE("Resource filename must exist");
    }
  }
  assert(fileio::FileIo().IsRegularFile(temp_filename));
  const int n
    = static_cast<int>(CanvasColorSystems().GetAll().size())
    * static_cast<int>(CanvasCoordinatSystems().GetAll().size());
  for (int i=0; i!=n; ++i)
  {
    const int ncs = static_cast<int>(CanvasColorSystems().GetAll().size());
    const int a = i % ncs;
    const CanvasColorSystem color_system = CanvasColorSystems().GetAll()[a];
    const int b = i / ncs;
    const CanvasCoordinatSystem coordinat_system
      = CanvasCoordinatSystems().GetAll()[b];
    const ImageCanvas c(temp_filename,20,color_system,coordinat_system);
    std::stringstream s;
    s << c;
    assert(!s.str().empty());
    //TRACE(c);
  }
  {
    const ImageCanvas a(temp_filename,60);
    const ImageCanvas b(temp_filename,60);
    assert(a == b);
  }
  {
    const ImageCanvas a(temp_filename,60);
    ImageCanvas b(temp_filename,50);
    assert(a != b);
    b = a;
    assert(a == b);
  }

  fileio::FileIo().DeleteFile(temp_filename);
}
#endif

