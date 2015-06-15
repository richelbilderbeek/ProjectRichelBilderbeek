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
#include "wtasciiartermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wcomment"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WFileUpload>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>

#include <QFile> //Must be #included after Wt
#include <QtGui/QImage>

#include "about.h"
//#include "asciiarter.h"
#include "asciiartermaindialog.h"
#include "asciiartermenudialog.h"
#include "fileio.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#pragma GCC diagnostic pop

ribi::WtAsciiArterMainDialog::Ui::Ui()
  : m_edit_width(new Wt::WLineEdit),
    m_fileupload(new Wt::WFileUpload),
    m_text(new Wt::WTextArea)
{

}

ribi::WtAsciiArterMainDialog::WtAsciiArterMainDialog()
  : m_dialog{},
    m_filename{},
    m_n_cols{0},
    ui{}
{
  //Create resources
  {
    std::vector<std::string> image_names;
    image_names.push_back("ToolAsciiArterWelcome.png");

    for(const std::string& filename: image_names)
    {
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        QFile f( (std::string(":/ToolAsciiArter/images/") + filename).c_str() );
        f.copy(filename.c_str());
      }
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        std::cerr << "File not found: " + filename + '\n';
      }
      assert(fileio::FileIo().IsRegularFile(filename));
    }
  }

  this->setContentAlignment(Wt::AlignCenter);
  //if (m_dialog)
  //{
  //  m_dialog->SetWidth(79);
  //}

  this->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("AsciiArter");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  this->addWidget(new Wt::WBreak);
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Welcome",
        CreateNewWelcomeDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Start",
        CreateNewMainDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About",
        CreateNewAboutDialog());
      menu->addItem(item);
    }
    //Display menu on top
    this->addWidget(menu);
    this->addWidget(new Wt::WBreak);
    //Display contents below menu
    this->addWidget(contents);
  }

  this->addWidget(new Wt::WBreak);

  assert(ui.m_edit_width);
  assert(ui.m_text);
}

Wt::WWidget * ribi::WtAsciiArterMainDialog::CreateNewAboutDialog() const
{
  About a = AsciiArterMenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  return d;
}

Wt::WWidget * ribi::WtAsciiArterMainDialog::CreateNewMainDialog()
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  //File upload
  {
    assert(ui.m_fileupload);

    //Upload automatically when the user entered a file
    ui.m_fileupload->changed().connect(
      ui.m_fileupload,
      &Wt::WFileUpload::upload);

    //Call WtTextUploadDialog::on_upload_done when file is uploaded
    ui.m_fileupload->uploaded().connect(
      this,
      &ribi::WtAsciiArterMainDialog::OnUploadDone);
    dialog->addWidget(ui.m_fileupload);
  }
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  //Width edit
  {
    assert(ui.m_edit_width);
    //if (m_dialog)
    //{
    //  ui.m_edit_width->setText(
    //    boost::lexical_cast<std::string>(m_dialog->GetWidth()));
    //}
    //Respond to if user presses enter
    ui.m_edit_width->enterPressed().connect(
      this, &ribi::WtAsciiArterMainDialog::OnEditWidthChange);
    dialog->addWidget(ui.m_edit_width);
  }
  //Convert button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Convert");
    button->clicked().connect(
      this, &ribi::WtAsciiArterMainDialog::OnConvertClick);
    dialog->addWidget(button);
  }
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  //text
  {
    assert(ui.m_text);
    ui.m_text->setMinimumSize(600,600);
    dialog->addWidget(ui.m_text);
  }
  return dialog;
}

Wt::WWidget * ribi::WtAsciiArterMainDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to AsciiArter",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("AsciiArter is a tool to convert images to ascii art.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolAsciiArterWelcome.png"));
  return dialog;
}

void ribi::WtAsciiArterMainDialog::OnAnyChange()
{
  if (!m_filename.empty()
    && fileio::FileIo().IsRegularFile(m_filename)
    && m_n_cols > 5)
  {
    m_dialog.reset(new AsciiArterMainDialog(m_filename,m_n_cols));
    //m_dialog->Convert();
    const std::vector<std::string> v { m_dialog->GetAsciiArt() };
    Wt::WString ws;
    for(const std::string& s: v)
    {
      ws += s.c_str();
      ws += "\n";
    }
    ui.m_text->setText(ws);
  }
}

void ribi::WtAsciiArterMainDialog::OnConvertClick()
{
  OnEditWidthChange();
}

void ribi::WtAsciiArterMainDialog::OnEditWidthChange()
{
  try
  {
    const std::string s = ui.m_edit_width->text().toUTF8();
    m_n_cols = boost::lexical_cast<int>(s);
  }
  catch(boost::bad_lexical_cast&)
  {
    //No problem
  }

  OnAnyChange();
}

void ribi::WtAsciiArterMainDialog::OnUploadDone()
{
  const std::string filename = ui.m_fileupload->spoolFileName();
  m_filename = filename;
  OnAnyChange();
}

//Returns a Y-X-ordered std::vector of greynesses.
const std::vector<std::vector<double> >
  ribi::WtAsciiArterMainDialog::ConvertToGreyYx(const std::string& filename)
{
  assert(fileio::FileIo().IsRegularFile(filename));
  const QImage * const i = new QImage(filename.c_str());
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

