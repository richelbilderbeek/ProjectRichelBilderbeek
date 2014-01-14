#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmulticanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>


#include "drawcanvas.h"
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


void ribi::QtTestMultiCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  const CanvasColorSystem color_system
    = ui->box_color_system->currentIndex() == 0
    ? CanvasColorSystem::normal
    : CanvasColorSystem::invert;
  this->m_canvas->SetColorSystem(color_system);
  //Should redraw automatically
}

void ribi::QtTestMultiCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas->SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}

void ribi::QtTestMultiCanvasMainDialog::ShowCanvas(const ribi::DrawCanvas * const)
{
  //Display the image
  std::stringstream s;
  s << (*m_canvas);
  ui->text->setPlainText(s.str().c_str());

}

void ribi::QtTestMultiCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas->Clear();
  //Should redraw automatically
}

void ribi::QtTestMultiCanvasMainDialog::on_button_circle_clicked()
{
  m_canvas->DrawCircle(
    ui->box_circle_x->value(),
    ui->box_circle_y->value(),
    ui->box_circle_r->value()
  );
}

void ribi::QtTestMultiCanvasMainDialog::on_button_dot_clicked()
{
   m_canvas->DrawDot(
     ui->box_dot_x->value(),
     ui->box_dot_y->value()
   );
}

void ribi::QtTestMultiCanvasMainDialog::on_button_line_clicked()
{
  m_canvas->DrawLine(
    ui->box_line_x1->value(),
    ui->box_line_y1->value(),
    ui->box_line_x2->value(),
    ui->box_line_y2->value()
  );
}

#ifndef NDEBUG
void ribi::QtTestMultiCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestMultiCanvasMainDialog::Test");
  const boost::shared_ptr<const DrawCanvas> canvas(new DrawCanvas(78,23));
  assert(canvas);
  TRACE("Finished ribi::QtTestMultiCanvasMainDialog::Test successfully");
}
#endif
