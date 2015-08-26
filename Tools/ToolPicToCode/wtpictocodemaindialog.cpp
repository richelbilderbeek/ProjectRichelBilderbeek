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
#include "wtpictocodemaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wcomment"
#include <boost/lexical_cast.hpp>

#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WFileUpload>
#include <Wt/WGroupBox>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
#include <Wt/WTextArea>
#include <Wt/WImage>
#include <Wt/WResource>

#include <QFile>
#include <QImage>

#include "pictocodemaindialog.h"

#pragma GCC diagnostic pop

ribi::p2c::WtMainDialog::WtMainDialog()
  : m_button_convert(new Wt::WPushButton("Convert")),
    m_fileupload(new Wt::WFileUpload),
    m_group(new Wt::WButtonGroup),
    m_text(new Wt::WTextArea)

{
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(m_fileupload);

  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Target?",this);
    //this->addWidget(m_group);
    {
      {
        QFile f(":/p2c/images/PicNds14x14.png");
        f.copy("PicNds14x14.png");
      }
      new Wt::WImage("PicNds14x14.png",container);
      Wt::WRadioButton * const button = new Wt::WRadioButton("NDS", container);
      button->setEnabled(false);
      new Wt::WBreak(container);
      m_group->addButton(button,0);
    }
    {
      {
        QFile f(":/p2c/images/PicQt14x14.png");
        f.copy("PicQt14x14.png");
      }
      new Wt::WImage("PicQt14x14.png",container);
      Wt::WRadioButton * const button = new Wt::WRadioButton("Qt", container);
      new Wt::WBreak(container);
      m_group->addButton(button,1);
    }

    m_group->setSelectedButtonIndex(1);
  }
  //Convert
  {
    m_button_convert->clicked().connect(
      this,
      &ribi::p2c::WtMainDialog::on_convert
    );
    m_button_convert->setEnabled(false);
    this->addWidget(m_button_convert);
  }
  this->addWidget(new Wt::WBreak);
  m_text->setMinimumSize(600,300);
  this->addWidget(m_text);


  //Upload automatically when the user entered a file
  m_fileupload->changed().connect(
    m_fileupload,
    &Wt::WFileUpload::upload);

  m_fileupload->uploaded().connect(
    this,
    &ribi::p2c::WtMainDialog::on_upload_done);
}

/*
const ribi::PicToCodeMainDialog::YxImage ribi::p2c::WtPicToCodeMainDialog::QtImageToImage(const QImage& qt_image) const
{
  const int width  = qt_image.width();
  const int height = qt_image.height();

  PicToCodeMainDialog::YxImage image;
  image.m_v.resize(height,std::vector<PicToCodeMainDialog::Pixel>(width));

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const line
      = static_cast<const unsigned char *>(qt_image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      image.m_v[y][x].a = static_cast<int>(line[(x*4)+3]);
      image.m_v[y][x].r = static_cast<int>(line[(x*4)+2]);
      image.m_v[y][x].g = static_cast<int>(line[(x*4)+1]);
      image.m_v[y][x].b = static_cast<int>(line[(x*4)+0]);
    }
  }
  return image;
}
*/

void ribi::p2c::WtMainDialog::on_convert()
{
  QImage image(m_fileupload->spoolFileName().c_str());
  MainDialog d;
  d.SetInputImage(image);
  d.SetGraphicsLibrary(this->m_group->checkedId() == 0 ? GraphicsLibrary::nds : GraphicsLibrary::qt);

  //Concantenate texts
  std::vector<std::string> v = d.ToHeaderFile();
  v.push_back("");
  {
    const auto w = d.ToImplementationFile();
    std::copy(std::begin(w),std::end(w),std::back_inserter(v));
  }

  //Convert text to string
  std::string text;
  for(const auto s:v)
  {
    text += s;
    text += '\n';
  }
  text.resize(text.size() - 1);

  m_text->setText(text.c_str());
}

void ribi::p2c::WtMainDialog::on_upload_done()
{
  m_button_convert->setEnabled(true);
}
