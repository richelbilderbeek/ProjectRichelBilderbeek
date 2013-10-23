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

#include <boost/numeric/conversion/cast.hpp>

#include <QImage>
#include "asciiarter.h"
#include "fileio.h"
#pragma GCC diagnostic pop

ribi::AsciiArterMainDialog::AsciiArterMainDialog(
  const std::string& filename,
  const int n_cols)
  : m_asciiart{},
    m_asciiarter(new AsciiArter),
    m_image{},
    m_width{n_cols}
{
  SetImage(filename);
}

bool ribi::AsciiArterMainDialog::CanConvert() const
{
  return !m_image.empty() && m_width > 5;
}

void ribi::AsciiArterMainDialog::Convert()
{
  m_asciiart = m_asciiarter->ImageToAscii(m_image,m_width);
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

void ribi::AsciiArterMainDialog::SetImage(const std::string& filename)
{
  if (!fileio::IsRegularFile(filename))
  {
    const std::vector<std::vector<double> > v;
    SetImage(v);
    return;
  }

  const boost::scoped_ptr<QImage> image{
    new QImage(filename.c_str())
  };
  const std::vector<std::vector<double> > v { ConvertToGreyYx(image.get()) };
  SetImage(v);
}


void ribi::AsciiArterMainDialog::SetImage(const std::vector<std::vector<double> >& image)
{
  m_image = image;

  //Update ascii art
  if (CanConvert())
  {
    m_asciiart = m_asciiarter->ImageToAscii(m_image,m_width);
  }
}

void ribi::AsciiArterMainDialog::SetWidth(const int width)
{
  assert(width > 5);
  m_width = width;

  //Update ascii art
  if (CanConvert())
  {
    m_asciiart = m_asciiarter->ImageToAscii(m_image,m_width);
  }
}
