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
#include "qtsurfaceplotterribidialog.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testtimer.h"
#include "fparser.hh"
#include "trace.h"
#include "ui_qtsurfaceplotterribidialog.h"

#pragma GCC diagnostic pop

ribi::QtSurfacePlotterRibiDialog::QtSurfacePlotterRibiDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSurfacePlotterRibiDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);


  QObject::connect(this->ui->edit_equation,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_minx,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_miny,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxx,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterRibiDialog::OnAnyChange);
  QObject::connect(this->ui->edit_maxy,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtSurfacePlotterRibiDialog::OnAnyChange);


  ui->edit_minx->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_miny->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_maxx->setText(boost::lexical_cast<std::string>( 1.0).c_str());
  ui->edit_maxy->setText(boost::lexical_cast<std::string>( 1.0).c_str());

  ui->edit_equation->setText("cos(x*y*100)");

  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() /2 );
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::QtSurfacePlotterRibiDialog::~QtSurfacePlotterRibiDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterRibiDialog::keyPressEvent(QKeyEvent *event)
{
 switch (event->key())
  {
    case Qt::Key_Escape: close(); return;
  }
}

void ribi::QtSurfacePlotterRibiDialog::OnAnyChange()
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

  FunctionParser f;

  //Parse the formula
  f.Parse(ui->edit_equation->text().toStdString().c_str(),"x,y");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    this->setWindowTitle("Function cannot not be parsed"); return;
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

  struct MyFunction : public QtSurfacePlotWidget::Function
  {
    MyFunction(const FunctionParser& f) : m_f(f) {}
    double operator()(const double x, const double y) const noexcept
    {
      const double xs[2] = { x,y };
      //FunctionParser::Eval is not const, although it does not change
      //the state of the FunctionParser itself
      const double z{const_cast<FunctionParser&>(m_f).Eval(xs)};
      return m_f.EvalError() ? 0.0 : z;
    }
    private:
    const FunctionParser m_f;
  };

  ui->surfaceplotwidget->Plot(
    MyFunction(f),
    x_min, x_max,
    y_min, y_max
  );

  /*
  //Evaluate the function in a 2D std::vector
  const int n_rows = ui->surfaceplotwidget->height();
  const int n_cols = ui->surfaceplotwidget->width();
  std::vector<std::vector<double>> v(n_rows,std::vector<double>(n_cols,0.0));
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
  //Plot the 2D std::vector
  ui->surfaceplotwidget->SetSurfaceGrey(v);
  */

  this->setWindowTitle("Function plotted successfully");

}

/*
double ribi::QtSurfacePlotterRibiDialog::Rescale(
  const double value,
  const double old_min,
  const double old_max,
  const double new_min,
  const double new_max)
{
  assert(value >= old_min);
  assert(value <= old_max);
  const double old_distance = old_max - old_min;
  //At which relative distance is value on old_min to old_max ?
  const double distance = (value - old_min) / old_distance;
  assert(distance >= 0.0);
  assert(distance <= 1.0);
  const double new_distance = new_max - new_min;
  const double new_value = new_min + (distance * new_distance);
  assert(new_value >= new_min);
  assert(new_value <= new_max);
  return new_value;
}
*/

void ribi::QtSurfacePlotterRibiDialog::resizeEvent(QResizeEvent *)
{
  OnAnyChange();
}

#ifndef NDEBUG
void ribi::QtSurfacePlotterRibiDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
