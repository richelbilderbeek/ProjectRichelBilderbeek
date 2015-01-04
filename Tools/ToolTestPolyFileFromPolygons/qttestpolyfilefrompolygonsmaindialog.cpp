//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestpolyfilefrompolygonsmaindialog.h"

#include <fstream>
#include <stdexcept>

#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "polyfilefrompolygons.h"
#include "qtnavigationablegraphicsview.h"
#include "testtimer.h"
#include "testpolyfilefrompolygonsmaindialog.h"
#include "trace.h"
#include "ui_qttestpolyfilefrompolygonsmaindialog.h"
#include "wkttosvgmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTestPolyFileFromPolygonsMainDialog::QtTestPolyFileFromPolygonsMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPolyFileFromPolygonsMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  on_edit_shapes_textChanged();
}

ribi::QtTestPolyFileFromPolygonsMainDialog::~QtTestPolyFileFromPolygonsMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPolyFileFromPolygonsMainDialog::DisplayPolyFile() noexcept
{
  const auto shapes = GetShapes();

  const std::string filename = fileio::FileIo().GetTempFileName(".poly");
  {
    PolyFileFromPolygons polyfile(shapes.first,shapes.second);
    std::ofstream f(filename.c_str());
    f << polyfile.ToStr();
  }
  const auto text = fileio::FileIo().FileToVector(filename);
  std::string s;
  for (const auto line: text) { s += line + '\n'; }
  s.pop_back();
  ui->text_file->setPlainText(s.c_str());

  fileio::FileIo().DeleteFile(filename);
}

void ribi::QtTestPolyFileFromPolygonsMainDialog::DisplayPolygons() noexcept
{
  assert(ui->view->scene());
  ui->view->scene()->clear();
  const std::string svg_filename = fileio::FileIo().GetTempFileName(".svg");
  {
    const std::string text_with_comments = ui->edit_shapes->toPlainText().toStdString();
    const auto v = Container().SeperateString(text_with_comments,'\n');
    std::string text;
    for (const auto s: v)
    {
      std::string t = boost::algorithm::trim_copy(s);
      if (!t.empty() && t[0] != '#') text += t + '\n';
    }
    const double stroke_width = 1.0;
    const WktToSvgMainDialog d(text,stroke_width);
    std::ofstream f(svg_filename.c_str());
    f << d.GetSvg();
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(svg_filename.c_str());
    item->setScale(1.0);
    ui->view->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(svg_filename);
}



ribi::QtTestPolyFileFromPolygonsMainDialog::Shapes
  ribi::QtTestPolyFileFromPolygonsMainDialog::GetShapes() const noexcept
{
  Shapes shapes;
  const std::string text = ui->edit_shapes->toPlainText().toStdString();
  const std::vector<std::string> lines = Container().SeperateString(text,'\n');
  for (const std::string line: lines)
  {
    try
    {
      Polygon polygon;
      boost::geometry::read_wkt(line,polygon);
      shapes.first.push_back(polygon);
    }
    catch (boost::geometry::read_wkt_exception&)
    {
      //No problem
    }
    try
    {
      Linestring linestring;
      boost::geometry::read_wkt(line,linestring);
      shapes.second.push_back(linestring);
    }
    catch (boost::geometry::read_wkt_exception&)
    {
      //No problem
    }
  }
  return shapes;
}

void ribi::QtTestPolyFileFromPolygonsMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestPolyFileFromPolygonsMainDialog::on_edit_shapes_textChanged()
{
  DisplayPolyFile();
  DisplayPolygons();
}

#ifndef NDEBUG
void ribi::QtTestPolyFileFromPolygonsMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtTestPolyFileFromPolygonsMainDialog d;
  const TestTimer test_timer(__func__,__FILE__,1.0);
  d.on_edit_shapes_textChanged();
}
#endif



