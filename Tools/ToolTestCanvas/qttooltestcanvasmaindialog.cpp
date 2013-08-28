#include "qttooltestcanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include "canvas.h"
#include "ui_qttooltestcanvasmaindialog.h"

QtToolTestCanvasMainDialog::QtToolTestCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestCanvasMainDialog)
{
  ui->setupUi(this);
  ShowCanvas();
}

QtToolTestCanvasMainDialog::~QtToolTestCanvasMainDialog()
{
  delete ui;
}

void QtToolTestCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  ShowCanvas();
}

void QtToolTestCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  ShowCanvas();
}

void QtToolTestCanvasMainDialog::ShowCanvas()
{
  const int maxx = 79; //Console is 80 chars wide
  const int maxy = 23; //Console is 80 chars high
  const Canvas::ColorSystem color_system
    = ui->box_color_system->currentIndex() == 0
    ? Canvas::ColorSystem::normal
    : Canvas::ColorSystem::invert;
  const Canvas::CoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? Canvas::CoordinatSystem::screen : Canvas::CoordinatSystem::graph;
  Canvas c( maxx, maxy, color_system, coordinat_system);

  //Draw smiley to Canvas

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
  c.DrawCircle(midX, midY, headRay);
  c.DrawCircle(eyeLeftX, eyeLeftY, eyeRay);
  c.DrawDot(eyeLeftX, eyeLeftY);
  c.DrawCircle(eyeRightX, eyeRightY, eyeRay);
  c.DrawDot(eyeRightX, eyeRightY);
  c.DrawLine(mouthLeftX, mouthLeftY, mouthMidX, mouthMidY);
  c.DrawLine(mouthMidX, mouthMidY, mouthRightX, mouthRightY);
  c.DrawLine(mouthRightX, mouthRightY, mouthLeftX, mouthLeftY);
  //Display the image
  std::stringstream s;
  s << c;
  ui->text->setPlainText(s.str().c_str());

}
