//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestpolyfilefrompolygonsmaindialog.h"

#include <fstream>
#include <stdexcept>

#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include <QDesktopWidget>
#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "fileio.h"
#include "geometry.h"
#include "polyfilefrompolygons.h"
#include "qtnavigationablegraphicsview.h"
#include "trace.h"
#include "testpolyfilefrompolygonsmaindialog.h"
#include "ui_qttestpolyfilefrompolygonsmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTestPolyFileFromPolygonsMainDialog::QtTestPolyFileFromPolygonsMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPolyFileFromPolygonsMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    //Put this dialog in the screen center
    const QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
  }

  on_edit_shapes_textChanged();
}

ribi::QtTestPolyFileFromPolygonsMainDialog::~QtTestPolyFileFromPolygonsMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPolyFileFromPolygonsMainDialog::DisplayPolyFile() noexcept
{
  const auto polygons = GetShapes();

  const std::string filename = fileio::FileIo().GetTempFileName(".poly");
  {
    PolyFileFromPolygons polyfile(polygons);
    std::ofstream f(filename.c_str());
    f << polyfile;
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
  const std::string text = ui->edit_shapes->toPlainText().toStdString();
  const std::vector<std::string> lines = SeperateString(text);

  std::vector<Polygon> polygons = GetShapes();

  const std::string svg_filename = fileio::FileIo().GetTempFileName(".svg");
  {
    std::ofstream f(svg_filename.c_str());
    f << Geometry().ToSvgStr(polygons,0.1);
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(svg_filename.c_str());
    item->setScale(10.0);
    assert(ui->view->scene());
    ui->view->scene()->clear();
    ui->view->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(svg_filename);
}



std::vector<ribi::QtTestPolyFileFromPolygonsMainDialog::Polygon>
  ribi::QtTestPolyFileFromPolygonsMainDialog::GetShapes() const noexcept
{
  std::vector<Polygon> polygons;
  const std::string text = ui->edit_shapes->toPlainText().toStdString();
  const std::vector<std::string> lines = SeperateString(text);
  for (const std::string line: lines)
  {
    Polygon polygon;
    try
    {
      boost::geometry::read_wkt(line,polygon);
      polygons.push_back(polygon);
    }
    catch (boost::geometry::read_wkt_exception& e)
    {
      //No problem
    }
  }
  return polygons;
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

std::vector<std::string> ribi::QtTestPolyFileFromPolygonsMainDialog::SeperateString(
  const std::string& input) noexcept
{
  const char seperator  = '\n';
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}


#ifndef NDEBUG
void ribi::QtTestPolyFileFromPolygonsMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtTestPolyFileFromPolygonsMainDialog::Test");
  QtTestPolyFileFromPolygonsMainDialog d;
  d.on_edit_shapes_textChanged();
  TRACE("Finished QtTestPolyFileFromPolygonsMainDialog::Test successfully");
}
#endif



