//---------------------------------------------------------------------------
/*
WktToSvg, tool to convert WKT to SVG
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolWktToSvg.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtwkttosvgmaindialog.h"

#include <fstream>
#include <stdexcept>

#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "fileio.h"
#include "qtnavigationablegraphicsview.h"
#include "testtimer.h"
#include "trace.h"
#include "wkttosvgmaindialog.h"
#include "ui_qtwkttosvgmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtWktToSvgMainDialog::QtWktToSvgMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtWktToSvgMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  QObject::connect(
    ui->edit,
    static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
    this,
    &ribi::QtWktToSvgMainDialog::OnInputChanged
  );
  QObject::connect(
    ui->box_stroke_width,
    static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
    this,
    &ribi::QtWktToSvgMainDialog::OnInputChanged
  );

  OnInputChanged();
}

ribi::QtWktToSvgMainDialog::~QtWktToSvgMainDialog() noexcept
{
  delete ui;
}

void ribi::QtWktToSvgMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::QtWktToSvgMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  WktToSvgMainDialog("POLYGON((0 0,0 1,1 1))",1.0);
  QtWktToSvgMainDialog();
}
#endif

void ribi::QtWktToSvgMainDialog::OnInputChanged()
{
  const std::string wkt_text = ui->edit->text().toStdString();
  const double stroke_width = ui->box_stroke_width->value();
  const WktToSvgMainDialog d(
    wkt_text,
    stroke_width
  );

  const std::string svg_text = d.GetSvg();

  ui->text_svg->setPlainText(svg_text.c_str()); //Calls on_text_svg_textChanged
}

void ribi::QtWktToSvgMainDialog::on_text_svg_textChanged()
{
  assert(ui->view->scene());
  ui->view->scene()->clear();


  const std::string svg_text = ui->text_svg->toPlainText().toStdString();


  const std::string filename = fileio::FileIo().GetTempFileName(".svg");
  //if (verbose) { std::clog << "Write SVG to file '" << filename << "'" << std::endl; }
  {
    std::ofstream f(filename.c_str());
    f << svg_text;
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(filename.c_str());
    assert(item);
    item->setScale(10.0);
    ui->view->scene()->addItem(item);
    assert(!ui->view->scene()->items().empty());
  }
  fileio::FileIo().DeleteFile(filename);
}
