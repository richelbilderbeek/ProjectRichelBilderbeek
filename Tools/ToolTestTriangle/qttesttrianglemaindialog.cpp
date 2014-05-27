//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
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
//From http://www.richelbilderbeek.nl/ToolTestTriangle.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesttrianglemaindialog.h"

#include <fstream>
#include <stdexcept>

#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include <QDesktopWidget>
#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "fileio.h"
#include "geometry.h"
#include "qtnavigationablegraphicsview.h"
#include "trace.h"
#include "trianglemeshface.h"
#include "trianglemeshpoint.h"
#include "trianglefile.h"
#include "testtrianglemaindialog.h"
#include "trianglemeshtemplate.h"
#include "ui_qttesttrianglemaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTestTriangleMainDialog::QtTestTriangleMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTriangleMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  connect(ui->box_triangle_max_area,SIGNAL(valueChanged(double)),this,SLOT(DisplayTriangleMesh()));
  connect(ui->box_triangle_min_angle,SIGNAL(valueChanged(double)),this,SLOT(DisplayTriangleMesh()));


  {
    //Put this dialog in the screen center
    const QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
  }

  on_edit_shapes_textChanged();
}

ribi::QtTestTriangleMainDialog::~QtTestTriangleMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTriangleMainDialog::DisplayPolygons() noexcept
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

  DisplayTriangleMesh();
}

void ribi::QtTestTriangleMainDialog::DisplayTriangleMesh() noexcept
{
  const bool verbose = GetVerbose();

  for (int i=0; i!=
  //#define TODO_ISSUE_207
  #ifndef TODO_ISSUE_207
    1
  #else
    2
  #endif // TODO_ISSUE_207
  ; ++i)
  {
    std::function<
      void(const ribi::TriangleFile *,std::string&,std::string&,std::string&,const Angle,const Area,const bool)
    > triangle_function;
    QGraphicsScene * scene = nullptr;

    switch (i)
    {
      case 0:
        triangle_function = &ribi::TriangleFile::ExecuteTriangleExe;
        scene = ui->view_triangle_mesh_exe->scene();
      break;
      //case 1:
      //  triangle_function = &ribi::TriangleFile::ExecuteTriangleCppExe;
      //scene = ui->view_trianglecpp_mesh_exe->scene();
      //break;
      //case 2:
      //  triangle_function = &ribi::TriangleFile::ExecuteTriangle;
      //scene = ui->view_triangle_mesh->scene();
      //break;
      //case 3:
      //  triangle_function = &ribi::TriangleFile::ExecuteTriangleCpp;
      //scene = ui->view_trianglecpp_mesh->scene();
      //break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("Unknown i");
    }
    assert(scene);
    scene->clear();

    const auto shapes = GetShapes();
    if (shapes.empty()) continue;

    const ribi::TriangleFile triangle_file(shapes);

    std::string filename_node;
    std::string filename_ele;
    std::string filename_poly;

    try
    {
      triangle_function(
        &triangle_file,
        filename_node,
        filename_ele,
        filename_poly,
        GetTriangleMinAngle(),
        GetTriangleMaxArea(),
        verbose
      );
    }
    catch (std::runtime_error& e)
    {
      continue;
    }

    if (verbose) { std::clog << "Read data from Triangle.exe output" << std::endl; }

    const boost::shared_ptr<const ribi::trim::Template> t
      = boost::make_shared<ribi::trim::Template>(
        filename_node,
        filename_ele
    );
    assert(t);

    if (verbose) { std::clog << "Convert Triangle.exe output to polygons" << std::endl; }
    std::vector<Polygon> polygons;
    for (const boost::shared_ptr<trim::Face> face: t->GetFaces())
    {
      std::vector<Coordinat2D> coordinats;
      for (const boost::shared_ptr<trim::Point> point: face->GetPoints())
      {
        coordinats.push_back(*point->GetCoordinat());
      }
      Polygon polygon;
      boost::geometry::append(polygon, coordinats);
      polygons.push_back(polygon);
    }

    if (verbose) { std::clog << "Convert to polygons to SVG" << std::endl; }
    const std::string svg_text = Geometry().ToSvgStr(polygons,0.1);

    const std::string filename = fileio::FileIo().GetTempFileName(".svg");
    if (verbose) { std::clog << "Write SVG to file '" << filename << "'" << std::endl; }
    {
      std::ofstream f(filename.c_str());
      f << svg_text;
    }
    {
      QGraphicsSvgItem * const item = new QGraphicsSvgItem(filename.c_str());
      item->setScale(10.0);
      scene->addItem(item);
    }
    fileio::FileIo().DeleteFile(filename);
  }
}

std::vector<ribi::QtTestTriangleMainDialog::Polygon>
  ribi::QtTestTriangleMainDialog::GetShapes() const noexcept
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

ribi::QtTestTriangleMainDialog::Area ribi::QtTestTriangleMainDialog::GetTriangleMaxArea() const noexcept
{
  return ui->box_triangle_max_area->value()
    * boost::units::si::square_meter;
}


ribi::QtTestTriangleMainDialog::Angle ribi::QtTestTriangleMainDialog::GetTriangleMinAngle() const noexcept
{
  return ui->box_triangle_min_angle->value() //Degrees
    * (boost::math::constants::two_pi<double>() / 360.0) //Convert to radians
    * boost::units::si::radians;
    ;
}

bool ribi::QtTestTriangleMainDialog::GetVerbose() const noexcept
{
  return ui->check_verbose->isChecked();
}

void ribi::QtTestTriangleMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestTriangleMainDialog::on_edit_shapes_textChanged()
{
  DisplayPolygons();
}

std::vector<std::string> ribi::QtTestTriangleMainDialog::SeperateString(
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
void ribi::QtTestTriangleMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtTestTriangleMainDialog::Test");
  QtTestTriangleMainDialog d;
  d.on_edit_shapes_textChanged();
  TRACE("Finished QtTestTriangleMainDialog::Test successfully");
}
#endif



