#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestplaneinvestigateaccuracydialog.h"

#include <cassert>

#include <boost/geometry/geometries/point_xy.hpp>

#include "geometry.h"
#include "plane.h"
#include "trace.h"
#include "qwttestplaneplot.h"
#include "ui_qttestplaneinvestigateaccuracydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestPlaneInvestigateAccuracyDialog::QtTestPlaneInvestigateAccuracyDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPlaneInvestigateAccuracyDialog),
    m_plot_x(),
    m_plot_y(),
    m_plot_z()
{
  ui->setupUi(this);

  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  const Geometry::Coordinat3D p1(0.1,0.0,0.0);
  const Geometry::Coordinat3D p2(0.0,0.2,0.0);
  const Geometry::Coordinat3D p3(0.0,0.0,0.3);
  const boost::shared_ptr<Plane> plane(new Plane(p1,p2,p3));
  assert(plane);

  {
    const boost::shared_ptr<QwtTestPlanePlot> p(
      new QwtTestPlanePlot(
        plane,[](const double x,const double y) { return Coordinat3D(0.0,x,y); }
      )
    );
    m_plot_x = p;

  }
  {
    const boost::shared_ptr<QwtTestPlanePlot> p(
      new QwtTestPlanePlot(
        plane,[](const double x,const double y) { return Coordinat3D(x,0.0,y); }
      )
    );
    m_plot_y = p;
  }

  {
    const boost::shared_ptr<QwtTestPlanePlot> p(
      new QwtTestPlanePlot(
        plane,[](const double x,const double y) { return Coordinat3D(x,y,0.0); }
      )
    );
    m_plot_z = p;
  }


  {
    assert(!ui->widget_plane_x->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_x->setLayout(my_layout);
    assert(ui->widget_plane_x->layout());
    my_layout->addWidget(m_plot_x.get());
  }

  {
    assert(!ui->widget_plane_y->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_y->setLayout(my_layout);
    assert(ui->widget_plane_y->layout());
    my_layout->addWidget(m_plot_y.get());
  }

  {
    assert(!ui->widget_plane_z->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget_plane_z->setLayout(my_layout);
    assert(ui->widget_plane_z->layout());
    my_layout->addWidget(m_plot_z.get());
  }



  QObject::connect(this->ui->box_x1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z1,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_x2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z2,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_x3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_y3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_z3,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));

  OnAnyChange();
}

ribi::QtTestPlaneInvestigateAccuracyDialog::~QtTestPlaneInvestigateAccuracyDialog()
{
  delete ui;
}

boost::shared_ptr<ribi::Plane> ribi::QtTestPlaneInvestigateAccuracyDialog::CreatePlane() const noexcept
{
  const Geometry::Coordinat3D p1(
    ui->box_x1->value(),
    ui->box_y1->value(),
    ui->box_z1->value()
  );
  const Geometry::Coordinat3D p2(
    ui->box_x2->value(),
    ui->box_y2->value(),
    ui->box_z2->value()
  );
  const Geometry::Coordinat3D p3(
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

void ribi::QtTestPlaneInvestigateAccuracyDialog::OnAnyChange()
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  const boost::shared_ptr<ribi::Plane> plane(
    CreatePlane()
  );
  assert(plane);
  m_plot_x->SetData(
    plane,[](const double x,const double y) { return Coordinat3D(0.0,x,y); },-1.0,1.0,-1.0,1.0
  );
  m_plot_y->SetData(
    plane,[](const double x,const double y) { return Coordinat3D(x,0.0,y); },-1.0,1.0,-1.0,1.0
  );
  m_plot_z->SetData(
    plane,[](const double x,const double y) { return Coordinat3D(x,y,0.0); },-1.0,1.0,-1.0,1.0
  );
}

#ifndef NDEBUG
void ribi::QtTestPlaneInvestigateAccuracyDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestPlaneInvestigateAccuracyDialog::Test");
  QtTestPlaneInvestigateAccuracyDialog d;
  assert(!d.GetVersion().empty());
  TRACE("Finished ribi::QtTestPlaneInvestigateAccuracyDialog::Test successfully");
}
#endif
