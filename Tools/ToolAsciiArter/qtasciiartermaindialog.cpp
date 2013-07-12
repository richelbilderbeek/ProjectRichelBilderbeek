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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtasciiartermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>
#include <QImage>
#include <QPixmap>

#include "asciiarter.h"
#include "asciiartermaindialog.h"
#include "qtaboutdialog.h"
#include "ui_qtasciiartermaindialog.h"

QtAsciiArterMainDialog::QtAsciiArterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAsciiArterMainDialog),
    m_dialog(new AsciiArterMainDialog)
{
  ui->setupUi(this);
  ui->edit_width->setText("80");
  on_edit_width_textChanged("80");


  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

QtAsciiArterMainDialog::~QtAsciiArterMainDialog()
{
  delete ui;
}

void QtAsciiArterMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtAsciiArterMainDialog::DrawAsciiArt()
{
  if (!m_dialog->CanConvert()) return;

  m_dialog->Convert();

  const std::vector<std::string>& v = m_dialog->GetAsciiArt();
  ui->text->clear();

  BOOST_FOREACH(const std::string& s,v)
  {
    ui->text->appendPlainText(s.c_str());
  }
}

void QtAsciiArterMainDialog::on_button_load_clicked()
{
  QFileDialog d;
  const QString filename = d.getOpenFileName();

  if (!QFile::exists(filename))
  {
    return;
  }

  QImage p(filename);
  const std::vector<std::vector<double> > v
    = ConvertToGreyYx(&p);

  m_dialog->SetImage(v);
  DrawAsciiArt();
}

//Returns a Y-X-ordered std::vector of greynesses.
const std::vector<std::vector<double> >
  QtAsciiArterMainDialog::ConvertToGreyYx(const QImage * const i)
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

void QtAsciiArterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void QtAsciiArterMainDialog::on_edit_width_textChanged(QString q)
{
  const std::string s = q.toStdString();
  try
  {
    boost::lexical_cast<int>(s);
  }
  catch (boost::bad_lexical_cast&)
  {
    return;
  }
  const int width = boost::lexical_cast<int>(s);
  if (width <= 5) return;
  this->m_dialog->SetWidth(width);
  DrawAsciiArt();

}

