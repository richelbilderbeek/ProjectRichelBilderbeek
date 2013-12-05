#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"

#include "qwt_point_data.h"

#include "qtfunctionplottermaindialog.h"
#include "ui_qtfunctionplottermaindialog.h"

#include "fparser.hh"
#pragma GCC diagnostic pop

ribi::QtFunctionPlotterMainDialog::QtFunctionPlotterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtFunctionPlotterMainDialog),
    m_curve(new QwtPlotCurve),
    m_plot(new QwtPlot)
{
  ui->setupUi(this);

  #ifndef NDEBUG
  assert(Rescale(2.0,1.0,5.0,0.0,100.0) >= 24.9999 && Rescale(2.0,1.0,5.0,0.0,100.0) < 25.0001);
  #endif
  //Create plot
  {
    assert(!ui->plot_contents->layout());
    QGridLayout * const layout = new QGridLayout;
    ui->plot_contents->setLayout(layout);

    layout->addWidget(m_plot);

    #ifdef _WIN32
    m_plot->setCanvasBackground(QBrush(QColor(255,255,255)));
    #else
    plot->setCanvasBackground(QColor(255,255,255));
    #endif

    m_curve->attach(m_plot);
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setPen(QPen(QColor(128,128,128)));
  }

  QObject::connect(
    this->ui->edit_equation,
    &QLineEdit::textChanged,
    this,
    &ribi::QtFunctionPlotterMainDialog::OnAnyChange
  );
  QObject::connect(
    this->ui->box_minx,
    SIGNAL(valueChanged(QString)),
    this,
    SLOT(OnAnyChange())
  );
  QObject::connect(
    this->ui->box_maxx,
    SIGNAL(valueChanged(QString)),
    this,
    SLOT(OnAnyChange())
  );


  ui->box_minx->setValue(-1.0);
  ui->box_maxx->setValue(1.0);

  ui->edit_equation->setText("cos(x)");


  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() /2 );
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::QtFunctionPlotterMainDialog::~QtFunctionPlotterMainDialog() noexcept
{
  delete ui;
}

void ribi::QtFunctionPlotterMainDialog::OnAnyChange() noexcept
{

  FunctionParser f;

  //Parse the formula
  f.Parse(ui->edit_equation->text().toStdString().c_str(),"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    this->setWindowTitle("Function cannot not be parsed"); return;
  }

  const double x_min = ui->box_minx->value();
  const double x_max = ui->box_maxx->value();

  if (x_min >= x_max)
  {
    this->setWindowTitle("Value of x_min must be smaller than x_max"); return;
  }

  //Evaluate the function in a 2D std::vector
  const int n_cols = ui->area_plot->width();
  std::vector<double> v_y(n_cols,0.0);
  std::vector<double> v_x(n_cols,0.0);
  const double n_cols_d = static_cast<double>(n_cols);

  for (int x = 0; x!=n_cols; ++x)
  {
    const double xD = static_cast<double>(x);
    const double x_scaled = Rescale(xD,0.0,n_cols_d,x_min,x_max);
    const double xs[1] = { x_scaled };
    const double y = f.Eval(xs);
    if (!f.EvalError())
    {
      v_y[x] = y;
    }
    else
    {
      v_y[x] = 0.0;
    }
    v_x[x] = x_scaled;
  }

  this->setWindowTitle("Function plotted successfully");

  //Plot
  #ifdef _WIN32
  m_curve->setData(new QwtPointArrayData(&v_x[0],&v_y[0],v_y.size()));
  #else
  m_curve->setData(&v_x[0],&v_y[0],v_y.size());
  #endif
  m_plot->replot();
}

double ribi::QtFunctionPlotterMainDialog::Rescale(
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

void ribi::QtFunctionPlotterMainDialog::resizeEvent(QResizeEvent *)
{
  OnAnyChange();
}
