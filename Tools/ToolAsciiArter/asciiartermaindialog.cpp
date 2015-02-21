//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "asciiartermaindialog.h"

#include <ostream>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QImage>
#include <QFile>

#include "canvas.h"
#include "imagecanvas.h"
#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::AsciiArterMainDialog::AsciiArterMainDialog(
  const std::string& filename,
  const int n_cols)
  : m_filename(filename),
    m_n_cols(n_cols)
{
  #ifndef NDEBUG
  Test();
  #endif
}



std::vector<std::string> ribi::AsciiArterMainDialog::GetAsciiArt() const noexcept
{
  const boost::shared_ptr<ribi::ImageCanvas> canvas { GetImageCanvas() };
  return canvas->ToStrings();
}

const boost::shared_ptr<ribi::ImageCanvas> ribi::AsciiArterMainDialog::GetImageCanvas() const noexcept
{
  if (!fileio::FileIo().IsRegularFile(m_filename))
  {
    const std::string s = "AsciiArterMainDialog: file '"+ m_filename + "' not found";
    throw std::logic_error(s.c_str());
  }
  if (m_n_cols < 5)
  {
    throw std::logic_error("AsciiArterMainDialog: n_cols < 5");
  }
  const boost::shared_ptr<ribi::ImageCanvas> canvas {
    new ImageCanvas(m_filename,m_n_cols)
  };
  assert(canvas);
  return canvas;
}

#ifndef NDEBUG
void ribi::AsciiArterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    boost::shared_ptr<ImageCanvas> canvas{new ImageCanvas("",1)};
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string temp_filename = fileio::FileIo().GetTempFileName();
  assert(!fileio::FileIo().IsRegularFile(temp_filename));
  {
    QFile qfile(":/ToolAsciiArter/images/R.png");
    qfile.copy(temp_filename.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(temp_filename)
    && "Resource file must exist");

  const AsciiArterMainDialog d(temp_filename,20);
  assert(!d.GetAsciiArt().empty());
  std::stringstream s;
  s << d;
  assert(!s.str().empty());
  //TRACE(d);

  fileio::FileIo().DeleteFile(temp_filename);
  assert(!fileio::FileIo().IsRegularFile(temp_filename));
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const AsciiArterMainDialog& d)
{
  os << (*d.GetImageCanvas());
  return os;
}
