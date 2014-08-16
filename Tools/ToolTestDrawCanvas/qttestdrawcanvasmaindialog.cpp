#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestdrawcanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "drawcanvas.h"
#include "qtcanvas.h"
#include "qtsurfaceplotwidget.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestdrawcanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestDrawCanvasMainDialog::QtTestDrawCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestDrawCanvasMainDialog),
  m_canvas(CreateCanvas()),
  m_surface_plot(new ribi::QtSurfacePlotWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    assert(ui->verticalLayout);
    QtCanvas * const qtcanvas {
      new QtCanvas(m_canvas)
    };
    ui->verticalLayout->addWidget(qtcanvas);
    ui->verticalLayout->addWidget(m_surface_plot);
  }

  {
    const double w = m_canvas->GetWidth();
    const double h = m_canvas->GetHeight();
    ui->box_circle_x->setValue(0.5 * w);
    ui->box_circle_y->setValue(0.5 * h);
    ui->box_circle_r->setValue(0.4 * h);
    ui->box_dot_x->setValue(0.5 * w);
    ui->box_dot_y->setValue(0.5 * h);
    ui->box_line_x1->setValue(0.25 * w);
    ui->box_line_y1->setValue(0.25 * h);
    ui->box_line_x2->setValue(0.75 * w);
    ui->box_line_y2->setValue(0.75 * h);
  }

  m_canvas->m_signal_changed.connect(
    boost::bind(&ribi::QtTestDrawCanvasMainDialog::OnChanged,this)
  );
  OnChanged();
}

ribi::QtTestDrawCanvasMainDialog::~QtTestDrawCanvasMainDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::DrawCanvas> ribi::QtTestDrawCanvasMainDialog::CreateCanvas()
{
  const int maxx = 79;
  const int maxy = 23;
  boost::shared_ptr<ribi::DrawCanvas> canvas(new DrawCanvas(maxx,maxy));
  //Determine and calculate dimensions and coordinats of smiley
  const double maxxD = static_cast<double>(maxx);
  const double maxyD = static_cast<double>(maxy);
  const double midX        = 0.50 * maxxD;
  const double midY        = 0.50 * maxyD;
  const double headRay     = 0.50 * maxyD;
  const double eyeLeftX    = 0.50 * maxxD - (0.35 * headRay) ;
  const double eyeLeftY    = 0.50 * maxyD - (0.25 * headRay) ;
  const double eyeRightX   = 0.50 * maxxD + (0.35 * headRay) ;
  const double eyeRightY   = 0.50 * maxyD - (0.25 * headRay) ;
  const double eyeRay      = 0.30 * headRay;
  const double mouthLeftX  = 0.50 * maxxD - (0.7 * headRay) ;
  const double mouthMidX   = 0.50 * maxxD;
  const double mouthRightX = 0.50 * maxxD + (0.7 * headRay) ;
  const double mouthLeftY  = 0.50 * maxyD + (0.2 * headRay) ;
  const double mouthMidY   = 0.50 * maxyD + (0.7 * headRay) ;
  const double mouthRightY = 0.50 * maxyD + (0.2 * headRay) ;
  //Draw the image on Canvas
  canvas->DrawCircle(midX, midY, headRay);
  canvas->DrawCircle(eyeLeftX, eyeLeftY, eyeRay);
  canvas->DrawDot(eyeLeftX, eyeLeftY);
  canvas->DrawCircle(eyeRightX, eyeRightY, eyeRay);
  canvas->DrawDot(eyeRightX, eyeRightY);
  canvas->DrawLine(mouthLeftX, mouthLeftY, mouthMidX, mouthMidY);
  canvas->DrawLine(mouthMidX, mouthMidY, mouthRightX, mouthRightY);
  canvas->DrawLine(mouthRightX, mouthRightY, mouthLeftX, mouthLeftY);
  return canvas;
}


void ribi::QtTestDrawCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  const CanvasColorSystem color_system
    = ui->box_color_system->currentIndex() == 0
    ? CanvasColorSystem::normal
    : CanvasColorSystem::invert;
  this->m_canvas->SetColorSystem(color_system);
  //Should redraw automatically
}

void ribi::QtTestDrawCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas->SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}


void ribi::QtTestDrawCanvasMainDialog::on_button_arc_clicked()
{
  const double left  = std::min(ui->box_arc_x1->value(),ui->box_arc_x2->value());
  const double right = std::max(ui->box_arc_x1->value(),ui->box_arc_x2->value());
  const double top    = std::min(ui->box_arc_y1->value(),ui->box_arc_y2->value());
  const double bottom = std::max(ui->box_arc_y1->value(),ui->box_arc_y2->value());
  const boost::units::quantity<boost::units::si::plane_angle> start_arc {
    ui->box_arc_start_arc->value() * boost::units::si::radian
  };
  const boost::units::quantity<boost::units::si::plane_angle> arc_length {
    ui->box_arc_arc_length->value() * boost::units::si::radian
  };
  m_canvas->DrawArc(left,top,right,bottom,start_arc,arc_length);
}

void ribi::QtTestDrawCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas->Clear();
  //Should redraw automatically
}

void ribi::QtTestDrawCanvasMainDialog::on_button_circle_clicked()
{
  m_canvas->DrawCircle(
    ui->box_circle_x->value(),
    ui->box_circle_y->value(),
    ui->box_circle_r->value()
  );
}

void ribi::QtTestDrawCanvasMainDialog::on_button_dot_clicked()
{
   m_canvas->DrawDot(
     ui->box_dot_x->value(),
     ui->box_dot_y->value()
   );
}

void ribi::QtTestDrawCanvasMainDialog::on_button_ellipse_clicked()
{
  const double left  = std::min(ui->box_ellipse_x1->value(),ui->box_ellipse_x2->value());
  const double right = std::max(ui->box_ellipse_x1->value(),ui->box_ellipse_x2->value());
  const double top    = std::min(ui->box_ellipse_y1->value(),ui->box_ellipse_y2->value());
  const double bottom = std::max(ui->box_ellipse_y1->value(),ui->box_ellipse_y2->value());
  m_canvas->DrawEllipse(left,top,right,bottom);
}

void ribi::QtTestDrawCanvasMainDialog::on_button_line_clicked()
{
  m_canvas->DrawLine(
    ui->box_line_x1->value(),
    ui->box_line_y1->value(),
    ui->box_line_x2->value(),
    ui->box_line_y2->value()
  );
}

void ribi::QtTestDrawCanvasMainDialog::OnChanged() noexcept
{
  m_surface_plot->SetSurfaceGrey(m_canvas->GetGreynesses());
}

#ifndef NDEBUG
void ribi::QtTestDrawCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestDrawCanvasMainDialog d;
  d.on_button_clear_clicked();
  {
    for (const auto r: d.m_canvas->GetGreynesses())
    {
      assert(std::find_if(std::begin(r),std::end(r),[](const double x) { return x > 0.01; } ) == std::end(r)
        && "on_button_clear_clicked must clear the canvas");
    }
  }

  for (int i=0; i!=6; ++i)
  {
    switch (i)
    {
      case 0: d.on_button_arc_clicked(); break;
      case 1: d.on_button_circle_clicked(); break;
      case 2: d.on_button_clear_clicked(); break;
      case 3: d.on_button_dot_clicked(); break;
      case 4: d.on_button_ellipse_clicked(); break;
      case 5: d.on_button_line_clicked(); break;
    }
    const auto v = d.m_canvas->GetGreynesses();
    assert(
      std::count_if(std::begin(v),std::end(v),
        [](const std::vector<double>& r)
        {
          return std::find_if(std::begin(r),std::end(r),[](const double x) { return x > 0.01; } ) == std::end(r);
        }
      ) > 0
      && "At least one row must have some greynesses"
    );
  }
}
#endif
