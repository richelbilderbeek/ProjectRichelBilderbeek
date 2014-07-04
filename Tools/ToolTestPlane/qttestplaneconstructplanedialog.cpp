#include "qttestplaneconstructplanedialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>
#include "geometry.h"
#include "plane.h"
#include "trace.h"
#include "ui_qttestplaneconstructplanedialog.h"
#pragma GCC diagnostic pop

ribi::QtTestPlaneConstructPlaneDialog::QtTestPlaneConstructPlaneDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPlaneConstructPlaneDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  QObject::connect(this->ui->box_x1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_x2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_x3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_x,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));

  QObject::connect(this->ui->box_precision,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));

  OnAnyChange();
}

ribi::QtTestPlaneConstructPlaneDialog::~QtTestPlaneConstructPlaneDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange()
{
  std::stringstream s;
  s << std::setprecision(ui->box_precision->value());

  const Geometry::Coordinat3D p1(
    static_cast<double>(ui->box_x1->value()),
    static_cast<double>(ui->box_y1->value()),
    static_cast<double>(ui->box_z1->value())
  );
  s << "Point 1: " << p1 << '\n';

  const Geometry::Coordinat3D p2(
    static_cast<double>(ui->box_x2->value()),
    static_cast<double>(ui->box_y2->value()),
    static_cast<double>(ui->box_z2->value())
  );
  s << "Point 2: " << p2 << '\n';

  const Geometry::Coordinat3D p3(
    static_cast<double>(ui->box_x3->value()),
    static_cast<double>(ui->box_y3->value()),
    static_cast<double>(ui->box_z3->value())
  );
  s << "Point 3: " << p3 << '\n';

  const boost::shared_ptr<ribi::Plane> plane(
    new Plane(p1,p2,p3)
  );
  assert(plane);

  try
  {
    s << "Function (X): " << '\n' //<< plane->ToFunctionX() << '\n'
      << "Coefficients (X): " << '\n'
      << " - A: " << plane->GetCoefficientsX()[0] << '\n'
      << " - B: " << plane->GetCoefficientsX()[1] << '\n'
      << " - C: " << plane->GetCoefficientsX()[2] << '\n'
      << " - D: " << plane->GetCoefficientsX()[3] << '\n'
    ;
  }
  catch (std::exception& e)
  {
    s << "Exception: " << e.what() << '\n';
  }

  try
  {
    s << "Function (Y): " << '\n' //plane->ToFunctionY() << '\n'
      << "Coefficients (Y): " << '\n'
      << " - A: " << plane->GetCoefficientsY()[0] << '\n'
      << " - B: " << plane->GetCoefficientsY()[1] << '\n'
      << " - C: " << plane->GetCoefficientsY()[2] << '\n'
      << " - D: " << plane->GetCoefficientsY()[3] << '\n'
    ;
  }
  catch (std::exception& e)
  {
    s << "Exception: " << e.what() << '\n';
  }

  try
  {
    s << "Function (Z): " << '\n' //plane->ToFunctionZ() << '\n'
      << "Coefficients (Z): " << '\n'
      << " - A: " << plane->GetCoefficientsZ()[0] << '\n'
      << " - B: " << plane->GetCoefficientsZ()[1] << '\n'
      << " - C: " << plane->GetCoefficientsZ()[2] << '\n'
      << " - D: " << plane->GetCoefficientsZ()[3] << '\n'
    ;
  }
  catch (std::exception& e)
  {
    s << "Exception: " << e.what() << '\n';
  }


  const double x = static_cast<double>(ui->box_x->value());
  const double y = static_cast<double>(ui->box_y->value());
  const double z = static_cast<double>(ui->box_z->value());

  try
  {
    const double x_on_plane = plane->CalcX(y,z);
    s << "X(Y,Z) = X(" << y << "," << z << ") = " << x_on_plane << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "X(Y,Z) = " << e.what() << '\n';
  }

  try
  {
    const double y_on_plane = plane->CalcY(x,z);
    s << "Y(X,Z) = Y(" << x << "," << z << ") = " << y_on_plane << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "Y(X,Z) = " << e.what() << '\n';
  }

  try
  {
    const double z_on_plane = plane->CalcZ(x,y);
    s << "Z(X,Y) = Z(" << x << "," << y << ") = " << z_on_plane << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "Z(X,Y) = " << e.what() << '\n';
  }

  try
  {
    s << "Plane: " << (*plane) << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "Plane: " << e.what() << '\n';
  }

  ui->text->setPlainText(s.str().c_str());
}

#ifndef NDEBUG
void ribi::QtTestPlaneConstructPlaneDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestPlaneConstructPlaneDialog::Test");
  QtTestPlaneConstructPlaneDialog d;
  assert(!d.GetVersion().empty());
  TRACE("Finished ribi::QtTestPlaneConstructPlaneDialog::Test successfully");
}
#endif

/*
std::ostream& ribi::operator<<(std::ostream& os, const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept
{
  os
    << "("
    << boost::geometry::get<0>(p)
    << ","
    << boost::geometry::get<1>(p)
    << ","
    << boost::geometry::get<2>(p)
    << ")"
  ;
  return os;
}
*/

