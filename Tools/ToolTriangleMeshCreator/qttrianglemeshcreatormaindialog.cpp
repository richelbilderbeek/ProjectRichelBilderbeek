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

#include <fstream>

#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <QDesktopWidget>
#include <QGraphicsSvgItem>
#include <QKeyEvent>

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "qtnavigationablegraphicsview.h"
#include "trace.h"
#include "trianglemeshface.h"
#include "trianglemeshpoint.h"
#include "trianglefile.h"
#include "trianglemeshdialog.h"
#include "trianglemeshtemplate.h"
#include "ui_qttrianglemeshcreatormaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTriangleMeshCreatorMainDialog::QtTriangleMeshCreatorMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTriangleMeshCreatorMainDialog),
    m_dialog{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  connect(ui->edit_wkt,SIGNAL(textChanged()),this,SLOT(DisplayPolygons()));
  connect(ui->box_triangle_max_area,SIGNAL(valueChanged(double)),this,SLOT(DisplayTriangleMesh()));
  connect(ui->box_triangle_min_angle,SIGNAL(valueChanged(double)),this,SLOT(DisplayTriangleMesh()));
  on_edit_shapes_textChanged();
}

ribi::QtTriangleMeshCreatorMainDialog::~QtTriangleMeshCreatorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTriangleMeshCreatorMainDialog::CreateMesh() noexcept
{
  try
  {
    m_dialog = boost::make_shared<ribi::trim::Dialog>(
    //const ribi::trim::Dialog d(
      GetShapes(),
      GetNumberOfCellLayers(),
      GetLayerHeight(),
      GetCreateVerticalFacesStrategy(),
      GetTriangleMinAngle(),
      GetTriangleMaxArea(),
      ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(GetFraction()),
      ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction(),
      ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      GetVerbose()
    );
    if (GetShowMesh())
    {
      assert(ribi::fileio::FileIo().IsRegularFile(m_dialog->GetFilename()));
      std::stringstream s;
      s
        #ifdef _WIN32
        << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
        #else
        << "meshlab "
        #endif
        << m_dialog->GetFilename()
      ;
      const int error = std::system(s.str().c_str());
      if (error) std::cout << "WARNING: cannot display mesh" << '\n';
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: Exception caught: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception caught!" << std::endl;
  }
}

void ribi::QtTriangleMeshCreatorMainDialog::DisplayPolygons() noexcept
{
  assert(ui->view->scene());
  ui->view->scene()->clear();
  //const std::string text = ui->edit_wkt->toPlainText().toStdString();
  //const std::vector<std::string> lines = Container().SeperateString(text,'\n');

  const auto shapes = GetShapes();

  const std::string svg_filename = fileio::FileIo().GetTempFileName(".svg");
  {
    std::ofstream f(svg_filename.c_str());
    f << Geometry().ToSvg(shapes,0.1);
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(svg_filename.c_str());
    item->setScale(10.0);
    ui->view->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(svg_filename);

  DisplayTriangleMesh();
}

void ribi::QtTriangleMeshCreatorMainDialog::DisplayTriangleMesh() noexcept
{
  /*
  const bool verbose = GetVerbose();
  if (verbose) { std::clog << "Write some geometries, let Triangle.exe work on it" << std::endl; }

  assert(ui->view_triangle_mesh->scene());
  ui->view_triangle_mesh->scene()->clear();


  std::string filename_node;
  std::string filename_ele;
  std::string filename_poly;
  try
  {
    ribi::TriangleFile f(GetShapes());
    f.ExecuteTriangleExe(
      filename_node,
      filename_ele,
      filename_poly,
      GetTriangleMinAngle(),
      GetTriangleMaxArea()
    );
  }
  catch (std::exception& e)
  {
    std::clog
      << "QtTriangleMeshCreatorMainDialog::DisplayTriangleMesh: "
      << "Triangle.exe failed: " << e.what()
    ;
    return;
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

  if (verbose) { std::clog << "Convert polygons to SVG" << std::endl; }
  const std::string svg_text = Geometry().ToSvg(polygons,0.1);

  const std::string filename = fileio::FileIo().GetTempFileName(".svg");
  if (verbose) { std::clog << "Write SVG to file '" << filename << "'" << std::endl; }
  {
    std::ofstream f(filename.c_str());
    f << svg_text;
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(filename.c_str());
    item->setScale(10.0);
    ui->view_triangle_mesh->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(filename);
  */
}

double ribi::QtTriangleMeshCreatorMainDialog::GetFraction() const noexcept
{
  return ui->box_fraction->value();
}

boost::units::quantity<boost::units::si::length>
  ribi::QtTriangleMeshCreatorMainDialog::GetLayerHeight() const noexcept
{
  return boost::units::quantity<boost::units::si::length>(
    ui->box_layer_height->value() * boost::units::si::meter
  );
}

int ribi::QtTriangleMeshCreatorMainDialog::GetNumberOfCellLayers() const noexcept
{
  return ui->box_n_cell_layers->value();
}

ribi::QtTriangleMeshCreatorMainDialog::Shapes
  ribi::QtTriangleMeshCreatorMainDialog::GetShapes() const noexcept
{
  const std::string text = ui->edit_wkt->toPlainText().toStdString();
  const auto shapes = Geometry().WktToShapes(text);
  return shapes;
}

bool ribi::QtTriangleMeshCreatorMainDialog::GetShowMesh() const noexcept
{
  return ui->check_show_mesh->isChecked();
}

ribi::QtTriangleMeshCreatorMainDialog::Area ribi::QtTriangleMeshCreatorMainDialog::GetTriangleMaxArea() const noexcept
{
  return ui->box_triangle_max_area->value() * boost::units::si::square_meter;
}


ribi::QtTriangleMeshCreatorMainDialog::Angle ribi::QtTriangleMeshCreatorMainDialog::GetTriangleMinAngle() const noexcept
{
  return ui->box_triangle_min_angle->value() //Degrees
    * (boost::math::constants::two_pi<double>() / 360.0) //Degrees -> radians
    * boost::units::si::radians
  ;
}

bool ribi::QtTriangleMeshCreatorMainDialog::GetVerbose() const noexcept
{
  return ui->check_verbose->isChecked();
}

ribi::trim::CreateVerticalFacesStrategy
  ribi::QtTriangleMeshCreatorMainDialog::GetCreateVerticalFacesStrategy() const noexcept
{
  assert(ui->box_vertical_faces_strategy->currentText() == "One square"
    || ui->box_vertical_faces_strategy->currentText() == "Two triangles"
  );

  const ribi::trim::CreateVerticalFacesStrategy create_vertical_faces_strategy
    = ui->box_vertical_faces_strategy->currentText() == "One square"
    ? ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
    : ribi::trim::CreateVerticalFacesStrategy::two_faces_per_square
  ;

  return create_vertical_faces_strategy;
}

void ribi::QtTriangleMeshCreatorMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTriangleMeshCreatorMainDialog::on_button_create_clicked()
{
  CreateMesh();
}

void ribi::QtTriangleMeshCreatorMainDialog::on_edit_shapes_textChanged()
{
  DisplayPolygons();
}

void ribi::QtTriangleMeshCreatorMainDialog::SetShowMesh(const bool show_mesh) noexcept
{
  ui->check_show_mesh->setChecked(show_mesh);
}

void ribi::QtTriangleMeshCreatorMainDialog::SetWkt(const std::string& wkt) noexcept
{
  ui->edit_wkt->setPlainText(wkt.c_str());
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
  QtTriangleMeshCreatorMainDialog d;
  d.SetShowMesh(false);
  d.on_edit_shapes_textChanged();
  d.on_button_create_clicked();

  //Set a WKT that does not have any closed surfaces
  d.SetWkt("LINESTRING(0 0 0 1 1 1 1 0)");
  d.on_button_create_clicked();
  TRACE("Finished QtTriangleMeshCreatorMainDialog::Test successfully");
}
#endif
