//---------------------------------------------------------------------------
/*
WktToSvg, tool to convert WKT to SVG
Copyright (C) 2014-2014 Richel Bilderbeek

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


  on_edit_textChanged(ui->edit->text());
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
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtWktToSvgMainDialog::Test");
  WktToSvgMainDialog();
  QtWktToSvgMainDialog();
  TRACE("Finished QtWktToSvgMainDialog::Test successfully");
}
#endif

void ribi::QtWktToSvgMainDialog::on_edit_textChanged(const QString &arg1)
{
  WktToSvgMainDialog d(arg1.toStdString(),ui->box_verbose->isChecked());

  const std::string svg_text = d.GetSvg();

  ui->text_svg->setPlainText(svg_text.c_str());

  const std::string filename = fileio::FileIo().GetTempFileName(".svg");
  //if (verbose) { std::clog << "Write SVG to file '" << filename << "'" << std::endl; }
  {
    std::ofstream f(filename.c_str());
    f << svg_text;
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(filename.c_str());
    assert(item);
    item->setScale(1.0);
    assert(ui->view->scene());
    ui->view->scene()->clear();
    ui->view->scene()->addItem(item);
    assert(!ui->view->scene()->items().empty());
  }
  fileio::FileIo().DeleteFile(filename);
}
