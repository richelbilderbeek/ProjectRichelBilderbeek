#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmulticanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "drawcanvas.h"
#include "imagecanvas.h"
#include "textcanvas.h"
#include "testtimer.h"
#include "multicanvas.h"
#include "trace.h"
#include "ui_qttestmulticanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestMultiCanvasMainDialog::QtTestMultiCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestMultiCanvasMainDialog),
  m_canvas(CreateCanvas())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  m_canvas->m_signal_changed.connect(
    boost::bind(
      &ribi::QtTestMultiCanvasMainDialog::ShowCanvas,this,
      boost::lambda::_1)
    );

  {
    const double w = m_canvas->GetWidth();
    const double h = m_canvas->GetHeight();
    ui->box_circle_x_draw->setValue(0.5 * w);
    ui->box_circle_y_draw->setValue(0.5 * h);
    ui->box_circle_r_draw->setValue(0.4 * h);
    ui->box_dot_x_draw->setValue(0.5 * w);
    ui->box_dot_y_draw->setValue(0.5 * h);
    ui->box_line_x1_draw->setValue(0.25 * w);
    ui->box_line_y1_draw->setValue(0.25 * h);
    ui->box_line_x2_draw->setValue(0.75 * w);
    ui->box_line_y2_draw->setValue(0.75 * h);
  }

  ShowCanvas(0);
}

ribi::QtTestMultiCanvasMainDialog::~QtTestMultiCanvasMainDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::DrawCanvas> ribi::QtTestMultiCanvasMainDialog::CreateCanvas()
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


/*
void ribi::QtTestMultiCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  const CanvasColorSystem color_system
    = ui->box_color_system_draw->currentIndex() == 0
    ? CanvasColorSystem::normal
    : CanvasColorSystem::invert;
  this->m_canvas->SetColorSystem(color_system);
  //Should redraw automatically
}

void ribi::QtTestMultiCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system_draw->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas->SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}
*/

void ribi::QtTestMultiCanvasMainDialog::ShowCanvas(const ribi::Canvas * const)
{
  //Display the image
  std::stringstream s;
  s << (*m_canvas);
  ui->text->setPlainText(s.str().c_str());

}

/*
void ribi::QtTestMultiCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas->Clear();
  //Should redraw automatically
}

void ribi::QtTestMultiCanvasMainDialog::on_button_circle_clicked()
{
  m_canvas->DrawCircle(
    ui->box_circle_x_draw->value(),
    ui->box_circle_y_draw->value(),
    ui->box_circle_r_draw->value()
  );
}

void ribi::QtTestMultiCanvasMainDialog::on_button_dot_clicked()
{
   m_canvas->DrawDot(
     ui->box_dot_x_draw->value(),
     ui->box_dot_y_draw->value()
   );
}

void ribi::QtTestMultiCanvasMainDialog::on_button_line_clicked()
{
  m_canvas->DrawLine(
    ui->box_line_x1_draw->value(),
    ui->box_line_y1_draw->value(),
    ui->box_line_x2_draw->value(),
    ui->box_line_y2_draw->value()
  );
}
*/

#ifndef NDEBUG
void ribi::QtTestMultiCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //MultiCanvas is tested in TestMultiCanvasMenuDialog
}
#endif
