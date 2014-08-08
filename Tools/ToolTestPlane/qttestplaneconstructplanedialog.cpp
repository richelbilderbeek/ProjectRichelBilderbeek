#include "qttestplaneconstructplanedialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "apfloat.h"

#include "geometry.h"
#include "plane.h"
#include "trace.h"
#include "testtimer.h"
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

  QObject::connect(this->ui->box_x1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_y1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_z1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_x2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_y2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_z2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_x3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_y3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_z3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_x,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_y,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_z,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);
  QObject::connect(this->ui->box_precision,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange);

  OnAnyChange();
}

ribi::QtTestPlaneConstructPlaneDialog::~QtTestPlaneConstructPlaneDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPlaneConstructPlaneDialog::OnAnyChange() noexcept
{
  std::stringstream s;
  s << std::setprecision(ui->box_precision->value());

  const Plane::Coordinat3D p1(
    ui->box_x1->value(),
    ui->box_y1->value(),
    ui->box_z1->value()
  );
  s << "Point 1: " << Geometry().ToStr(p1) << '\n';

  const Plane::Coordinat3D p2(
    ui->box_x2->value(),
    ui->box_y2->value(),
    ui->box_z2->value()
  );
  s << "Point 2: " << Geometry().ToStr(p2) << '\n';

  const Plane::Coordinat3D p3(
    ui->box_x3->value(),
    ui->box_y3->value(),
    ui->box_z3->value()
  );
  s << "Point 3: " << Geometry().ToStr(p3) << '\n';

  const boost::shared_ptr<Plane> plane(
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


  const double x = ui->box_x->value();
  const double y = ui->box_y->value();
  const double z = ui->box_z->value();

  try
  {
    const auto x_on_plane = plane->CalcX(y,z);
    s << "X(Y,Z) = X(" << y << "," << z << ") = " << x_on_plane << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "X(Y,Z) = " << e.what() << '\n';
  }

  try
  {
    const auto y_on_plane = plane->CalcY(x,z);
    s << "Y(X,Z) = Y(" << x << "," << z << ") = " << y_on_plane << '\n';
  }
  catch (std::logic_error& e)
  {
    s << "Y(X,Z) = " << e.what() << '\n';
  }

  try
  {
    const auto z_on_plane = plane->CalcZ(x,y);
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestPlaneConstructPlaneDialog d;
  assert(!d.GetVersion().empty());
}
#endif
