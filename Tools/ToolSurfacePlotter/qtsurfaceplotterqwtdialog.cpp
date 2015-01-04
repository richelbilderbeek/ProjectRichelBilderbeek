//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
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
//From http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsurfaceplotterqwtdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "fparser.hh"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtsurfaceplotterqwtdialog.h"
#include "qwtsurfaceplotterplot.h"

#pragma GCC diagnostic pop

ribi::QtSurfacePlotterQwtDialog::QtSurfacePlotterQwtDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSurfacePlotterQwtDialog),
    m_plot(new QwtSurfacePlotterPlot(this))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->edit_maxx->setValue( 1.0);
  ui->edit_maxy->setValue( 1.0);
  ui->edit_maxz->setValue( 1.0);
  ui->edit_minx->setValue(-1.0);
  ui->edit_miny->setValue(-1.0);
  ui->edit_minz->setValue(-1.0);

  ui->edit_equation->setText("cos(x*y*10)");

  {
    assert(!ui->widget->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget->setLayout(my_layout);
    my_layout->addWidget(m_plot);
  }


  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() /2 );
    this->move( screen.center() - this->rect().center() );
  }

  QObject::connect(this->ui->edit_equation,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxx,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxy,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxz,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_minx,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_miny,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);
  QObject::connect(this->ui->edit_minz,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtSurfacePlotterQwtDialog::OnAnyChange);

  OnAnyChange();
  m_plot->showSpectrogram(true);
  m_plot->showContour(true);
}

ribi::QtSurfacePlotterQwtDialog::~QtSurfacePlotterQwtDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterQwtDialog::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_plot->showSpectrogram(true); break;
    case Qt::Key_Down: m_plot->showSpectrogram(false); break;
    case Qt::Key_Right: m_plot->showContour(true); break;
    case Qt::Key_Left: m_plot->showContour(false); break;
    case Qt::Key_Escape: close(); return;
  }
}

void ribi::QtSurfacePlotterQwtDialog::OnAnyChange()
{
  const auto f = boost::make_shared<FunctionParser>();

  //Parse the formula
  f->Parse(ui->edit_equation->text().toStdString().c_str(),"x,y");
  if (f->GetParseErrorType() != FunctionParser::FP_NO_ERROR)
  {
    this->setWindowTitle("Function cannot not be parsed"); return;
  }


  const double x_min = ui->edit_minx->value();
  const double y_min = ui->edit_miny->value();
  const double z_min = ui->edit_minz->value();
  const double x_max = ui->edit_maxx->value();
  const double y_max = ui->edit_maxy->value();
  const double z_max = ui->edit_maxz->value();


  if (x_min >= x_max)
  {
    this->setWindowTitle("Value of x_min must be smaller than x_max"); return;
  }

  if (y_min >= y_max)
  {
    this->setWindowTitle("Value of y_min must be smaller than y_max"); return;
  }

  if (z_min >= z_max)
  {
    this->setWindowTitle("Value of z_min must be smaller than z_max"); return;
  }

  m_plot->SetData(
    f,
    x_min,x_max,
    y_min,y_max,
    z_min,z_max
  );

  //Evaluate the function in a 2D std::vector
  /*
  const int n_rows = ui->surfaceplotwidget->height();
  const int n_cols = ui->surfaceplotwidget->width();
  std::vector<std::vector<double> > v(n_rows,std::vector<double>(n_cols,0.0));
  const double n_rows_d = static_cast<double>(n_rows);
  const double n_cols_d = static_cast<double>(n_cols);

  for (int y = 0; y!=n_rows; ++y)
  {
    const double yD = static_cast<double>(y);
    const double y_scaled = Rescale(yD,0.0,n_rows_d,y_min,y_max);
    for (int x = 0; x!=n_cols; ++x)
    {
      const double xD = static_cast<double>(x);
      const double x_scaled = Rescale(xD,0.0,n_cols_d,x_min,x_max);
      const double xs[2] = { x_scaled,y_scaled };
      const double z = f.Eval(xs);
      if (!f.EvalError())
      {
        v[y][x] = z;
      }
      else
      {
        v[y][x] = 0.0;
      }
    }
  }
  */


  this->setWindowTitle("Function plotted successfully");

  //Plot the 2D std::vector
  //ui->surfaceplotwidget->SetSurfaceGrey(v);
}

#ifndef NDEBUG
void ribi::QtSurfacePlotterQwtDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
