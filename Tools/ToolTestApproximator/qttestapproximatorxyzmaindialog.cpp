#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestapproximatorxyzmaindialog.h"

#include <cassert>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#if QWT_VERSION >= 0x060000
#ifdef _WIN32
//#include <qwt_point_data.h>
#endif
#endif

#include "testtimer.h"
#include "ui_qttestapproximatorxyzmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtToolTestApproximatorXyzMainDialog::QtToolTestApproximatorXyzMainDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestApproximatorXyzMainDialog),
  m_approximator(),
  m_data(CreateData())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Set up the plots and curves
  GetPlot(0)->setTitle("Approximator, for z = 0.0");
  GetPlot(1)->setTitle("Approximator, for z = 0.5");
  GetPlot(2)->setTitle("Approximator, for z = 1.0");
  for (auto i=0; i!=m_n_curves; ++i)
  {
    const auto plot = GetPlot(i);
    plot->setAxisTitle(QwtPlot::xBottom,"X");
    plot->setAxisTitle(QwtPlot::yLeft,"Y");
    #ifdef _WIN32
    plot->setCanvasBackground(QBrush(QColor(255,255,255)));
    #else
    plot->setCanvasBackground(QColor(255,255,255));
    #endif

    const auto curve_values = GetCurveValues(i);
    assert(curve_values);
    curve_values->setTitle("Points");
    curve_values->attach(plot.get());
    curve_values->setStyle(QwtPlotCurve::Dots);
    curve_values->setPen(QPen(QColor(255,0,0),5));

    const auto curve_approximation = GetCurveApproximation(i);
    assert(curve_approximation);
    curve_approximation->setTitle("Approximation");
    curve_approximation->attach(plot.get());
    curve_approximation->setStyle(QwtPlotCurve::Dots);
    curve_approximation->setPen(QPen(QColor(0,0,255),3));

    //Add grid
    {
      QwtPlotGrid * const grid = new QwtPlotGrid;
      grid->setPen(QPen(QColor(128,128,128)));
      grid->attach(plot.get());
    }
    //Add zoomer
    {
      new QwtPlotZoomer(plot->canvas());
    }
    //Add legend
    {
      QwtLegend * const legend = new QwtLegend;
      legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
      plot->insertLegend(legend, QwtPlot::RightLegend);
    }

    plot->setAxisScale(
      QwtPlot::xBottom,
      static_cast<double>(ui->box_int_x->minimum()),
      static_cast<double>(ui->box_int_x->maximum())
    );
    plot->setAxisScale(
      QwtPlot::yLeft,
      static_cast<double>(ui->box_double_y->minimum()),
      static_cast<double>(ui->box_double_y->maximum())
    );

    //Add to dialog
    assert(ui->verticalLayout->layout());
    ui->verticalLayout->layout()->addWidget(plot.get());
  }




  //Add some nice testing values
  ui->box_int_x->setValue(ui->box_int_x->minimum() / 2);
  ui->box_double_y->setValue(ui->box_double_y->maximum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->minimum() / 4);
  ui->box_double_y->setValue(ui->box_double_y->minimum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->maximum() / 4);
  ui->box_double_y->setValue(ui->box_double_y->maximum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->maximum() / 2);
  ui->box_double_y->setValue(ui->box_double_y->minimum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(0);
  ui->box_double_y->setValue(0.0);
}

ribi::QtToolTestApproximatorXyzMainDialog::~QtToolTestApproximatorXyzMainDialog() noexcept
{
  delete ui;
}

ribi::QtToolTestApproximatorXyzMainDialog::Data
  ribi::QtToolTestApproximatorXyzMainDialog::CreateData() noexcept
{
  Data d;
  for (auto i=0; i!=m_n_curves; ++i)
  {
    QwtPlotCurve * const curve_approx { new QwtPlotCurve };
    QwtPlotCurve * const curve_values { new QwtPlotCurve };
    boost::shared_ptr<QwtPlot> plot { new QwtPlot };
    assert(curve_approx);
    assert(curve_values);
    assert(plot);
    d[i] = std::make_tuple(curve_approx,curve_values,plot);
  }
  return d;
}

QwtPlotCurve * ribi::QtToolTestApproximatorXyzMainDialog::GetCurveApproximation(const int i) noexcept
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_data.size()));
  return std::get<0>(m_data[i]);
}

QwtPlotCurve * ribi::QtToolTestApproximatorXyzMainDialog::GetCurveValues(const int i) noexcept
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_data.size()));
  return std::get<1>(m_data[i]);
}

const boost::shared_ptr<QwtPlot> ribi::QtToolTestApproximatorXyzMainDialog::GetPlot(const int i) noexcept
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_data.size()));
  const auto p = std::get<2>(m_data[i]);
  assert(p);
  return p;
}

void ribi::QtToolTestApproximatorXyzMainDialog::on_button_clicked() noexcept
{
  #ifdef TODO_723468346509350397
  const double x = static_cast<double>(ui->box_int_x->value());
  const double y = ui->box_double_y->value();
  const double z = static_cast<double>(ui->box_int_z->value());
  assert(m_approximator.CanAdd(y, {x,z})
    && "Can only click the button when the pair can be added");

  m_approximator.Add(x,y);
  Plot();
  #endif
}

void ribi::QtToolTestApproximatorXyzMainDialog::on_box_int_x_valueChanged(int) noexcept
{
  #ifdef TODO_723468346509350397
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  const double z = static_cast<double>(ui->box_int_z->value());
  ui->button->setEnabled( m_approximator.CanAdd(x,y) );
  #endif
}

void ribi::QtToolTestApproximatorXyzMainDialog::on_box_double_y_valueChanged(double) noexcept
{
  #ifdef TODO_723468346509350397
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  const double z = static_cast<double>(ui->box_int_z->value());
  ui->button->setEnabled( m_approximator.CanAdd(x,y) );
  #endif
}

void ribi::QtToolTestApproximatorXyzMainDialog::on_box_int_z_valueChanged(int) noexcept
{
  #ifdef TODO_723468346509350397
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  const double z = static_cast<double>(ui->box_int_z->value());
  ui->button->setEnabled( m_approximator.CanAdd(x,y) );
  #endif
}

void ribi::QtToolTestApproximatorXyzMainDialog::Plot() noexcept
{
  #ifdef TODO_723468346509350397
  //Plot approximation
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto p: m_approximator.Get())
    {
      xs.push_back( static_cast<double>(p.first) );
      ys.push_back( static_cast<double>(p.second) );
    }
    assert(m_curve_values);
    #if QWT_VERSION >= 0x060000
    m_curve_values->setData(new QwtPointArrayData(&xs[0],&ys[0],xs.size()));
    #else
    m_curve_values->setData(&xs[0],&y[0],xs.size());
    #endif
  }

  const double min_x = static_cast<double>(ui->box_int_x->minimum());
  const double max_x = static_cast<double>(ui->box_int_x->maximum());

  //Plot approximation
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (double t=min_x; t < max_x; t+=0.5)
    {
      try
      {
        const double x = static_cast<double>(t);
        const double y = m_approximator.Approximate(x);
        ys.push_back(y);
        xs.push_back(x);
      }
      catch (ExceptionNoExtrapolation<Approximator_t::key_type>& e)
      {

      }
    }
    assert(m_curve_approximation);
    #if QWT_VERSION >= 0x060000
    m_curve_approximation->setData(new QwtPointArrayData(&xs[0],&ys[0],xs.size()));
    #else
    m_curve_approximation->setData(&xs[0],&y[0],xs.size());
    #endif
  }
  assert(m_plot);
  m_plot->replot();
  #endif
}

#ifndef NDEBUG
void ribi::QtToolTestApproximatorXyzMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
