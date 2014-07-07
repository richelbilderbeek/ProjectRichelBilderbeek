//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2014 Richel Bilderbeek

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

#include <QDesktopWidget>
#include <QKeyEvent>

#include "fparser.hh"
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

  QObject::connect(this->ui->edit_equation,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_minx,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_miny,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxx,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxy,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));

  ui->edit_minx->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_miny->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_maxx->setText(boost::lexical_cast<std::string>( 1.0).c_str());
  ui->edit_maxy->setText(boost::lexical_cast<std::string>( 1.0).c_str());

  ui->edit_equation->setText("cos(x*y*100)");

  {
    assert(!ui->widget->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget->setLayout(my_layout);
    my_layout->addWidget(m_plot);
  }

  m_plot->showSpectrogram(true);
  m_plot->showContour(true);

  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() /2 );
    this->move( screen.center() - this->rect().center() );
  }
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
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtSurfacePlotterQwtDialog::Test");
  TRACE("Finished ribi::QtSurfacePlotterQwtDialog::Test successfully");
}
#endif
