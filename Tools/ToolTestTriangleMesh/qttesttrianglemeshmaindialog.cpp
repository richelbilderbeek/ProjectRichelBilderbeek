#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <boost/lexical_cast.hpp>
#include <QDesktopWidget>

#include "fparser.hh"
#include "qttesttrianglemeshmaindialog.h"
#include "trace.h"
#include "ui_qttesttrianglemeshmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTestTriangleMeshMainDialog::QtTestTriangleMeshMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTriangleMeshMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  #ifndef NDEBUG
  assert(Rescale(2.0,1.0,5.0,0.0,100.0) >= 24.9999 && Rescale(2.0,1.0,5.0,0.0,100.0) < 25.0001);
  #endif

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
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() /2 );
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::QtTestTriangleMeshMainDialog::~QtTestTriangleMeshMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTriangleMeshMainDialog::OnAnyChange()
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

  this->setWindowTitle("Function plotted successfully");

  //Plot the 2D std::vector
  ui->surfaceplotwidget->SetSurfaceGrey(v);
}

double ribi::QtTestTriangleMeshMainDialog::Rescale(
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

void ribi::QtTestTriangleMeshMainDialog::resizeEvent(QResizeEvent *)
{
  OnAnyChange();
}

#ifndef NDEBUG
void ribi::QtTestTriangleMeshMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTriangleMeshMainDialog::Test");
  TRACE("Finished ribi::QtTestTriangleMeshMainDialog::Test successfully");
}
#endif
