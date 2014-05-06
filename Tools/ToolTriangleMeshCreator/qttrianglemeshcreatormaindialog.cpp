//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
//From http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttrianglemeshcreatormaindialog.h"

#include <boost/math/constants/constants.hpp>

#include <QDesktopWidget>
#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "fileio.h"
#include "geometry.h"
#include "trace.h"
#include "trianglefile.h"
#include "qtnavigationablegraphicsview.h"
#include "ui_qttrianglemeshcreatormaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTriangleMeshCreatorMainDialog::QtTriangleMeshCreatorMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTriangleMeshCreatorMainDialog)
//    ,m_view(new QtNavigationableGraphicsView(this))
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
}

ribi::QtTriangleMeshCreatorMainDialog::~QtTriangleMeshCreatorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTriangleMeshCreatorMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTriangleMeshCreatorMainDialog::on_edit_shapes_textChanged()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  const std::string text = ui->edit_shapes->toPlainText().toStdString();
  const std::vector<std::string> lines = SeperateString(text);
  std::vector<Polygon> polygons;
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
      TRACE(e.what());
      continue;
    }
  }

  const std::string svg_filename = fileio::FileIo().GetTempFileName(".svg");
  {
    std::ofstream f(svg_filename.c_str());
    f << Geometry().ToSvgStr(polygons);
  }
  {
    QGraphicsSvgItem * const i = new QGraphicsSvgItem(svg_filename.c_str());
    assert(ui->view->scene());
    ui->view->scene()->clear();
    ui->view->scene()->addItem(i);
  }
  fileio::FileIo().DeleteFile(svg_filename);
}

std::vector<std::string> ribi::QtTriangleMeshCreatorMainDialog::SeperateString(
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
void ribi::QtTriangleMeshCreatorMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtTriangleMeshCreatorMainDialog::Test");
  TRACE("Finished QtTriangleMeshCreatorMainDialog::Test successfully");
}
#endif

