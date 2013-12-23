//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2013 Richel Bilderbeek

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

#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include <QImage>
#include <QFile>

#include "asciiarter.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::AsciiArterMainDialog::AsciiArterMainDialog(
  const std::string& filename,
  const int n_cols)
  : m_asciiart{ CreateAsciiArt(filename,n_cols) }
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::vector<std::vector<double> >
  ribi::AsciiArterMainDialog::ConvertToGreyYx(const QImage * const i)
{
  const int maxy = i->height();
  const int maxx = i->width();
  const int n_bytes = i->bytesPerLine() / maxx;

  std::vector<std::vector<double> > v;
  for (int y=0; y!=maxy; ++y)
  {
    v.push_back(std::vector<double>());
    const unsigned char * const line = i->scanLine(y);
    for (int x=0; x!=maxx; ++x)
    {
      int sum = 0;
      for (int byte=0; byte!=n_bytes; ++byte)
      {
        sum += line[(x * n_bytes) + byte];
      }
      const double greyness
        = (boost::numeric_cast<double>(sum)
        / boost::numeric_cast<double>(n_bytes))
        / 256.0;
      assert(greyness >= 0.0);
      assert(greyness <= 1.0);
      v.back().push_back(greyness);
    }
  }
  return v;
}

const std::vector<std::string> ribi::AsciiArterMainDialog::CreateAsciiArt(
  const std::string& filename,
  const int n_cols)
{
  if (!fileio::IsRegularFile(filename))
  {
    const std::string s = "AsciiArterMainDialog: file '"+ filename + "' not found";
    throw std::logic_error(s.c_str());
  }
  if (n_cols < 5)
  {
    throw std::logic_error("AsciiArterMainDialog: n_cols < 5");
  }

  const boost::scoped_ptr<QImage> qimage{
    new QImage(filename.c_str())
  };
  const std::vector<std::vector<double> > image { ConvertToGreyYx(qimage.get()) };

  return AsciiArter::ImageToAscii(image,n_cols);
}

#ifndef NDEBUG
void ribi::AsciiArterMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::AsciiArterMainDialog::Test()");
  const std::string temp_filename = fileio::GetTempFileName();
  assert(!fileio::IsRegularFile(temp_filename));
  {
    QFile qfile(":/ToolAsciiArter/images/R.png");
    qfile.copy(temp_filename.c_str());
  }
  assert(fileio::IsRegularFile(temp_filename)
    && "Resource file must exist");

  const AsciiArterMainDialog d(temp_filename,20);
  assert(!d.GetAsciiArt().empty());

  fileio::DeleteFile(temp_filename);
  assert(!fileio::IsRegularFile(temp_filename));
  TRACE("Finished ribi::AsciiArterMainDialog::Test()");
}
#endif
