//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
#include "testtimer.h"
#include "trianglemeshpoint.h"
#include "trianglefile.h"
#include "trianglemeshdialog.h"
#include "trianglemeshtemplate.h"
#include "ui_qttrianglemeshcreatormaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTriangleMeshCreatorMainDialog::QtTriangleMeshCreatorMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTriangleMeshCreatorMainDialog),
    m_dialog{new ribi::trim::Dialog}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    QGraphicsScene * const scene = new QGraphicsScene;
    ui->view_shapes_1->setScene(scene);
    ui->view_shapes_2->setScene(scene);
    assert(ui->view_shapes_1->scene());
    assert(ui->view_shapes_2->scene());
    assert(ui->view_shapes_1->scene() == ui->view_shapes_2->scene());
  }
  {
    QGraphicsScene * const scene = new QGraphicsScene;
    ui->view_triangle_mesh_1->setScene(scene);
    ui->view_triangle_mesh_2->setScene(scene);
    assert(ui->view_triangle_mesh_1->scene());
    assert(ui->view_triangle_mesh_2->scene());
    assert(ui->view_triangle_mesh_1->scene() == ui->view_triangle_mesh_2->scene());
  }


  QObject::connect(ui->edit_wkt,&QPlainTextEdit::textChanged,this,&ribi::QtTriangleMeshCreatorMainDialog::DisplayPolygons);
  QObject::connect(
    ui->box_triangle_max_area,
    static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
    this,
    &ribi::QtTriangleMeshCreatorMainDialog::on_button_create_2d_mesh_clicked
  );
  QObject::connect(
    ui->box_triangle_min_angle,
    static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
    this,
    &ribi::QtTriangleMeshCreatorMainDialog::on_button_create_2d_mesh_clicked
  );

  DisplayPolygons();
}

ribi::QtTriangleMeshCreatorMainDialog::~QtTriangleMeshCreatorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTriangleMeshCreatorMainDialog::Create3dMesh() noexcept
{

  try
  {
    assert(m_dialog);
    m_dialog->Set3dMeshParameters(
      GetNumberOfCellLayers(),
      GetLayerHeight(),
      GetCreateVerticalFacesStrategy(),
      ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(GetFraction()),
      ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction(),
      ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      GetVerbose3dMesh()
    );
    m_dialog->Create3dMesh();
    m_dialog->Check3dMesh( QApplication::arguments()[0].toStdString() );
    if (GetShowMesh())
    {
      m_dialog->Show3dMesh();

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

  assert(ui->view_shapes_1->scene());
  ui->view_shapes_1->scene()->clear();

  m_dialog->SetShapes(GetShapes());

  const std::string svg_filename = fileio::FileIo().GetTempFileName(".svg");
  {
    std::ofstream f(svg_filename.c_str());
    f << m_dialog->GetShapesAsSvg();
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(svg_filename.c_str());
    item->setScale(10.0);
    ui->view_shapes_1->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(svg_filename);
}

void ribi::QtTriangleMeshCreatorMainDialog::DisplayTriangleMesh() noexcept
{
  const auto verbose = GetVerboseTriangleMesh();

  ui->view_triangle_mesh_1->scene()->clear();

  const std::string filename = fileio::FileIo().GetTempFileName(".svg");
  if (verbose) { std::clog << "Write SVG to file '" << filename << "'" << std::endl; }
  {
    std::ofstream f(filename.c_str());
    f << m_dialog->GetTriangleMeshAsSvg();
  }
  {
    QGraphicsSvgItem * const item = new QGraphicsSvgItem(filename.c_str());
    item->setScale(10.0);
    ui->view_triangle_mesh_1->scene()->addItem(item);
  }
  fileio::FileIo().DeleteFile(filename);
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


bool ribi::QtTriangleMeshCreatorMainDialog::GetVerbose3dMesh() const noexcept
{
  return ui->check_verbose_3d_mesh->isChecked();
}

bool ribi::QtTriangleMeshCreatorMainDialog::GetVerboseTriangleMesh() const noexcept
{
  return ui->check_verbose_triangle_mesh->isChecked();
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
  Create3dMesh();
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  #ifdef FIX_ISSUE_233
  QtTriangleMeshCreatorMainDialog d;
  d.SetShowMesh(false);
  d.DisplayPolygons();
  d.on_button_create_2d_mesh_clicked();
  d.on_button_create_clicked();

  //Set a WKT that does not have any closed surfaces
  d.SetWkt("LINESTRING(0 0 0 1 1 1 1 0)");
  d.on_button_create_clicked();
  #endif // FIX_ISSUE_233

}
#endif

void ribi::QtTriangleMeshCreatorMainDialog::on_button_create_2d_mesh_clicked()
{
  m_dialog->SetTriangleParameters(
    GetTriangleMinAngle(),
    GetTriangleMaxArea(),
    GetVerboseTriangleMesh()
  );
  m_dialog->CreateTriangleMesh();
  DisplayTriangleMesh();
}
