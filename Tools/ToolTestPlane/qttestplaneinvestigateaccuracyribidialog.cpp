#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestplaneinvestigateaccuracyribidialog.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "fparser.hh"

#include "geometry.h"
#include "plane.h"

#include "qtsurfaceplotwidget.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestplaneinvestigateaccuracyribidialog.h"

#pragma GCC diagnostic pop

ribi::QtTestPlaneInvestigateAccuracyRibiDialog::QtTestPlaneInvestigateAccuracyRibiDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPlaneInvestigateAccuracyRibiDialog),
    m_widget_x(new QtSurfacePlotWidget),
    m_widget_y(new QtSurfacePlotWidget),
    m_widget_z(new QtSurfacePlotWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    assert(!ui->widget_plane_x->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_x->setLayout(my_layout);
    assert(ui->widget_plane_x->layout());
    my_layout->addWidget(m_widget_x.get());
  }

  {
    assert(!ui->widget_plane_y->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_y->setLayout(my_layout);
    assert(ui->widget_plane_y->layout());
    my_layout->addWidget(m_widget_y.get());
  }

  {
    assert(!ui->widget_plane_z->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_z->setLayout(my_layout);
    assert(ui->widget_plane_z->layout());
    my_layout->addWidget(m_widget_z.get());
  }

  ui->edit_minx->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_miny->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_maxx->setText(boost::lexical_cast<std::string>( 1.0).c_str());
  ui->edit_maxy->setText(boost::lexical_cast<std::string>( 1.0).c_str());

  QObject::connect(this->ui->edit_minx,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_miny,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxx,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxy,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);

  QObject::connect(this->ui->box_x1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_y1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_z1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_x2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_y2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_z2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_x3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_y3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);
  QObject::connect(this->ui->box_z3,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange);

  OnAnyChange();
}

ribi::QtTestPlaneInvestigateAccuracyRibiDialog::~QtTestPlaneInvestigateAccuracyRibiDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::Plane> ribi::QtTestPlaneInvestigateAccuracyRibiDialog::CreatePlane() const noexcept
{
  const Plane::Coordinat3D p1(
    ui->box_x1->value(),
    ui->box_y1->value(),
    ui->box_z1->value()
  );
  const Plane::Coordinat3D p2(
    ui->box_x2->value(),
    ui->box_y2->value(),
    ui->box_z2->value()
  );
  const Plane::Coordinat3D p3(
    ui->box_x3->value(),
    ui->box_y3->value(),
    ui->box_z3->value()
  );
  const boost::shared_ptr<Plane> plane(
    new Plane(p1,p2,p3)
  );
  assert(plane);
  return plane;
}
void ribi::QtTestPlaneInvestigateAccuracyRibiDialog::keyPressEvent(QKeyEvent *event)
{
 switch (event->key())
  {
    case Qt::Key_Escape: close(); return;
  }
}

void ribi::QtTestPlaneInvestigateAccuracyRibiDialog::OnAnyChange()
{
  try { boost::lexical_cast<double>(ui->edit_minx->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of x_min is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_miny->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of y_min is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_maxx->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of x_max is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_maxy->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of y_max is not a valid double"); return;
  }

  const double x_min = boost::lexical_cast<double>(ui->edit_minx->text().toStdString());
  const double y_min = boost::lexical_cast<double>(ui->edit_miny->text().toStdString());
  const double x_max = boost::lexical_cast<double>(ui->edit_maxx->text().toStdString());
  const double y_max = boost::lexical_cast<double>(ui->edit_maxy->text().toStdString());

  if (x_min >= x_max)
  {
    this->setWindowTitle("Value of x_min must be smaller than x_max"); return;
  }

  if (y_min >= y_max)
  {
    this->setWindowTitle("Value of y_min must be smaller than y_max"); return;
  }

  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  const boost::shared_ptr<Plane> plane(
    CreatePlane()
  );
  assert(plane);

  struct MyFunction : public QtSurfacePlotWidget::Function
  {
    typedef std::function<Coordinat3D(const double x, const double y)> ConvertFunction;

    MyFunction(
      const Plane& plane,
      const ConvertFunction& f
      ) : m_f(f), m_plane(plane) {}
    double operator()(const double x, const double y) const noexcept
    {
      const auto co_double = m_f(x,y);
      const Plane::Coordinat3D co_apfloat(
        apfloat(boost::geometry::get<0>(co_double)),
        apfloat(boost::geometry::get<1>(co_double)),
        apfloat(boost::geometry::get<2>(co_double))
      );
      const auto error_apfloat = m_plane.CalcError(co_apfloat);
      return Geometry().ToDoubleSafe(error_apfloat);
      //return m_plane.CalcError(m_f(x,y));
    }
    private:
    const ConvertFunction m_f;
    const Plane& m_plane;
  };

  m_widget_x->Plot(
    MyFunction(*plane,[](const double x, const double y) { return Coordinat3D(0.0,x,y); }),
    x_min, x_max,
    y_min, y_max
  );

  m_widget_y->Plot(
    MyFunction(*plane,[](const double x, const double y) { return Coordinat3D(x,0.0,y); }),
    x_min, x_max,
    y_min, y_max
  );

  m_widget_z->Plot(
    MyFunction(*plane,[](const double x, const double y) { return Coordinat3D(x,y,0.0); }),
    x_min, x_max,
    y_min, y_max
  );

  this->setWindowTitle("Function plotted successfully");

}

void ribi::QtTestPlaneInvestigateAccuracyRibiDialog::resizeEvent(QResizeEvent *)
{
  OnAnyChange();
}

#ifndef NDEBUG
void ribi::QtTestPlaneInvestigateAccuracyRibiDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
