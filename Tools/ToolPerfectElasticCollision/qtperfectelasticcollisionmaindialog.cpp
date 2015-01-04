//---------------------------------------------------------------------------
/*
PerfectElasticCollision, tool to investigate a perfect elastic collision
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From hhtp://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtperfectelasticcollisionmaindialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QBitmap>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

#include "geometry.h"
#include "ui_qtperfectelasticcollisionmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtPerfectElasticCollisionMainDialog::QtPerfectElasticCollisionMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPerfectElasticCollisionMainDialog),
    m_timer(new QTimer)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  QObject::connect(this->ui->dial_angle,&QDial::sliderMoved,this,&ribi::QtPerfectElasticCollisionMainDialog::onAnyChange);
  QObject::connect(this->ui->dial_impulse_angle1,&QDial::sliderMoved,this,&ribi::QtPerfectElasticCollisionMainDialog::onAnyChange);
  QObject::connect(this->ui->dial_impulse_angle2,&QDial::sliderMoved,this,&ribi::QtPerfectElasticCollisionMainDialog::onAnyChange);
  QObject::connect(this->ui->slider_impulse_1,&QDial::sliderMoved,this,&ribi::QtPerfectElasticCollisionMainDialog::onAnyChange);
  QObject::connect(this->ui->slider_impulse_2,&QDial::sliderMoved,this,&ribi::QtPerfectElasticCollisionMainDialog::onAnyChange);
  QObject::connect(this->ui->check_demo,&QCheckBox::toggled,this,&ribi::QtPerfectElasticCollisionMainDialog::onCheck);
  QObject::connect(m_timer,&QTimer::timeout,this,&ribi::QtPerfectElasticCollisionMainDialog::onTimer);
}

ribi::QtPerfectElasticCollisionMainDialog::~QtPerfectElasticCollisionMainDialog() noexcept
{
  delete ui;
  delete m_timer;
}

void ribi::QtPerfectElasticCollisionMainDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  assert(ui->dial_angle->minimum() == 0);
  assert(ui->dial_impulse_angle1->minimum() == 0);
  assert(ui->dial_impulse_angle2->minimum() == 0);
  assert(ui->slider_impulse_1->minimum() == 0);
  assert(ui->slider_impulse_2->minimum() == 0);

  const double pi = boost::math::constants::pi<double>();

  const double angle
    = 2.0 * pi * boost::numeric_cast<double>(ui->dial_angle->sliderPosition())
    / boost::numeric_cast<double>(ui->dial_angle->maximum());
  const double angle_impulse1
    = 2.0 * pi * boost::numeric_cast<double>(ui->dial_impulse_angle1->sliderPosition())
    / boost::numeric_cast<double>(ui->dial_impulse_angle1->maximum());
  const double angle_impulse2
    = 2.0 * pi * boost::numeric_cast<double>(ui->dial_impulse_angle2->sliderPosition())
    / boost::numeric_cast<double>(ui->dial_impulse_angle2->maximum());
  const double speed_impulse1
    = 100.0 * boost::numeric_cast<double>(ui->slider_impulse_1->sliderPosition())
    / boost::numeric_cast<double>(ui->slider_impulse_1->maximum());
  const double speed_impulse2
    = 100.0 * boost::numeric_cast<double>(ui->slider_impulse_2->sliderPosition())
    / boost::numeric_cast<double>(ui->slider_impulse_2->maximum());
  const int width = ui->widget_top->width();
  const int height = ui->widget_top->height();
  const int size = std::min(width,height);
  const int globe_size = size / 5;
  const double distance = boost::numeric_cast<double>(globe_size);
  const double dx =  std::sin(angle) * distance;
  const double dy = -std::cos(angle) * distance;
  const double midx = boost::numeric_cast<double>(size) / 2.0;
  const double midy = boost::numeric_cast<double>(size) / 2.0;
  const double midx1 = midx - (dx / 2.0);
  const double midy1 = midy - (dy / 2.0);
  const double midx2 = midx + (dx / 2.0);
  const double midy2 = midy + (dy / 2.0);
  const double x1 = midx1 - (boost::numeric_cast<double>(globe_size) / 2.0);
  const double y1 = midy1 - (boost::numeric_cast<double>(globe_size) / 2.0);
  const double x2 = midx2 - (boost::numeric_cast<double>(globe_size) / 2.0);
  const double y2 = midy2 - (boost::numeric_cast<double>(globe_size) / 2.0);
  //std::clog << "angle_impulse1: " << angle_impulse1 << '\n';
  //std::clog << "angle_impulse2: " << angle_impulse2 << '\n';

  //Draw black background
  {
    QPixmap pixmap(width,height);
    Paint(pixmap,1,1,1,255);
    painter.drawPixmap(ui->widget_top->geometry(),pixmap);
  }
  //Draw globe 1
  {
    QPixmap pixmap = DrawGlobe(globe_size,globe_size,255,0,0);
    painter.drawPixmap(x1,y1,pixmap);
  }
  //Draw globe 2
  {
    QPixmap pixmap = DrawGlobe(globe_size,globe_size,0,0,255);
    painter.drawPixmap(x2,y2,pixmap);
  }
  //Change the pen to white
  {
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);
  }
  //Draw impulses
  painter.drawLine(
    midx1,
    midy1,
    midx1 + (std::sin(angle_impulse1) * speed_impulse1),
    midy1 - (std::cos(angle_impulse1) * speed_impulse1) );
  painter.drawLine(
    midx2,
    midy2,
    midx2 + (std::sin(angle_impulse2) * speed_impulse2),
    midy2 - (std::cos(angle_impulse2) * speed_impulse2) );
  painter.drawText(
    midx1 + (std::sin(angle_impulse1) * speed_impulse1),
    midy1 - (std::cos(angle_impulse1) * speed_impulse1),112,16,0,"before1");
  painter.drawText(
    midx2 + (std::sin(angle_impulse2) * speed_impulse2),
    midy2 - (std::cos(angle_impulse2) * speed_impulse2),
    112,16,0,"before2");
  {
    double new_angle1 = angle_impulse1;
    double new_speed1 = speed_impulse1;
    double new_angle2 = angle_impulse2;
    double new_speed2 = speed_impulse2;
    DoPerfectElasticCollision(angle,new_angle1,new_speed1,new_angle2,new_speed2);
    const double impulse_before = speed_impulse1 + speed_impulse2;
    const double impulse_after  = new_speed1 + new_speed2;
    const double change = (impulse_after - impulse_before) / impulse_before;
    ui->label_error->setText("Impulse change: "
      + QString(boost::lexical_cast<std::string>(change * 100.0).c_str())
      + "%");
    //Draw resulting impulses
    {
      //Change the pen to white
      QPen pen = painter.pen();
      pen.setColor(Qt::gray);
      pen.setWidth(3);
      painter.setPen(pen);

    }
    painter.drawLine(
      midx1,
      midy1,
      midx1 + (std::sin(new_angle1) * new_speed1),
      midy1 - (std::cos(new_angle1) * new_speed1) );
    painter.drawLine(
      midx2,
      midy2,
      midx2 + (std::sin(new_angle2) * new_speed2),
      midy2 - (std::cos(new_angle2) * new_speed2) );
    painter.drawText(
      midx1 + (std::sin(new_angle1) * new_speed1),
      midy1 - (std::cos(new_angle1) * new_speed1),96,16,0,"after1");
    painter.drawText(
      midx2 + (std::sin(new_angle2) * new_speed2),
      midy2 - (std::cos(new_angle2) * new_speed2),96,16,0,"after2");
  }


}

void ribi::QtPerfectElasticCollisionMainDialog::onAnyChange()
{
  this->update();
}

void ribi::QtPerfectElasticCollisionMainDialog::onCheck()
{
  if (ui->check_demo->isChecked())
  {
    m_timer->start(10);
  }
  else
  {
    m_timer->stop();
  }
}

void ribi::QtPerfectElasticCollisionMainDialog::onTimer()
{
  ui->dial_angle->setSliderPosition(
     (ui->dial_angle->sliderPosition() + (std::rand() % 2))
    % ui->dial_angle->maximum() );
  ui->dial_impulse_angle1->setSliderPosition(
     (ui->dial_impulse_angle1->sliderPosition() + (std::rand() % 3))
    % ui->dial_impulse_angle1->maximum() );
  ui->dial_impulse_angle2->setSliderPosition(
     (ui->dial_impulse_angle2->sliderPosition() + (std::rand() % 4))
    % ui->dial_impulse_angle2->maximum() );
  this->update();
}

//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
QPixmap ribi::QtPerfectElasticCollisionMainDialog::DrawGlobe(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
{
  QPixmap pixmap(width,height);
  QImage image = pixmap.toImage();

  assert(image.bytesPerLine() / width == 4
    && "Assume there are 4 bytes per pixel");

  const double r_max = boost::numeric_cast<double>(r);
  const double g_max = boost::numeric_cast<double>(g);
  const double b_max = boost::numeric_cast<double>(b);
  const double midX = boost::numeric_cast<double>(width ) / 2.0;
  const double midY = boost::numeric_cast<double>(height) / 2.0;
  const double max_dist = std::min(midX,midY);

  for (int y=0; y!=height; ++y)
  {

    unsigned char * const line
      = static_cast<unsigned char *>(image.scanLine(y));
    const double y_d = boost::numeric_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double x_d = boost::numeric_cast<double>(x);
      const double dist
        = std::sqrt(
            ((x_d - midX) * (x_d - midX))
          + ((y_d - midY) * (y_d - midY)) );
      if (dist <= max_dist)
      {
        const double rel_dist = dist / max_dist;
        const int r_here = rel_dist * r_max;
        const int g_here = rel_dist * g_max;
        const int b_here = rel_dist * b_max;
        assert( r_here >= 0);
        assert( r_here < 256);
        assert( g_here >= 0);
        assert( g_here < 256);
        assert( b_here >= 0);
        assert( b_here < 256);
        line[x*4+3] = 255; //Alpha value
        line[x*4+2] = r_here; //Red
        line[x*4+1] = g_here; //Green
        line[x*4+0] = b_here; //Blue
      }
      else
      {
        line[x*4+3] = 0; //Alpha value
        line[x*4+2] = 0; //Red
        line[x*4+1] = 0; //Green
        line[x*4+0] = 0; //Blue
      }
    }
  }
  pixmap = pixmap.fromImage(image);

  //Add transparency
  const QBitmap mask = pixmap.createMaskFromColor(QColor(0,0,0,0).rgb());
  pixmap.setMask(mask);

  return pixmap;
}

void ribi::QtPerfectElasticCollisionMainDialog::Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a)
{
  const int width = pixmap.width();
  const int height = pixmap.height();

  QImage image = pixmap.toImage();

  assert(image.bytesPerLine() / width == 4
    && "Assume there are 4 bytes per pixel");

  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      line[x*4+3] = a; //Alpha value
      line[x*4+2] = r; //Red
      line[x*4+1] = g; //Green
      line[x*4+0] = b; //Blue
    }
  }
  pixmap = pixmap.fromImage(image);
}

//From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
void ribi::QtPerfectElasticCollisionMainDialog::DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2)
{
  const double pi = boost::math::constants::pi<double>();
  //The length of the impulse of player 1 (assumes both players have equal mass!)
  const double A = speed1;
  //The length of the impulse of player 2 (assumes both players have equal mass!)
  const double E = speed2;
  //The angles between the two globes
  const double c = angleCollision;
  //The angle between c and the impulse direction of player 1
  const double a = c - angle1;
  //The angle between c and the impulse direction of player 2
  const double b = c + pi - angle2;

  //Seperate the impulses to their impulses paralel and othoganal the angle of collision
  //The length of the impulse of player 1 parallel to the collision
  const double B = A * std::cos(a);
  //The length of the impulse of player 1 orthogonal to the collision
  const double C = A * std::sin(a);
  //The length of the impulse of player 2 parallel to the collision
  const double F = E * std::cos(b);
  //The length of the impulse of player 2 orthogonal to the collision
  const double G = E * std::sin(b);

  //Seperate the impulses in X and Y directions
  const double BdX = B *  std::sin(c + (0.0 * pi));
  const double BdY = B * -std::cos(c + (0.0 * pi));
  const double CdX = C *  std::sin(c + (1.5 * pi));
  const double CdY = C * -std::cos(c + (1.5 * pi));
  const double FdX = F *  std::sin(c + (1.0 * pi));
  const double FdY = F * -std::cos(c + (1.0 * pi));
  const double GdX = G *  std::sin(c + (0.5 * pi));
  const double GdY = G * -std::cos(c + (0.5 * pi));

  //The resulting impulses
  //The resulting impulse of player 1 in the X direction
  const double DdX = CdX + FdX;
  //The resulting impulse of player 1 in the Y direction
  const double DdY = CdY + FdY;
  //The resulting impulse of player 2 in the X direction
  const double HdX = BdX + GdX;
  //The resulting impulse of player 2 in the Y direction
  const double HdY = BdY + GdY;

  //Write the final results
  angle1 = GetAngle(DdX, DdY);
  angle2 = GetAngle(HdX, HdY);
  speed1 = std::sqrt( (DdX * DdX) + (DdY * DdY) ); //Pythagoras
  speed2 = std::sqrt( (HdX * HdX) + (HdY * HdY) ); //Pythagoras
}

double ribi::QtPerfectElasticCollisionMainDialog::GetAngle(const double dx, const double dy)
{
  return Geometry().GetAngleClockScreen(dx,dy);
}

#ifndef NDEBUG
void ribi::QtPerfectElasticCollisionMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
}
#endif
