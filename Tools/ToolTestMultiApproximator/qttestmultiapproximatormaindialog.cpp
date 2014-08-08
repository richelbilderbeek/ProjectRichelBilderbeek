#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmultiapproximatormaindialog.h"

#include <cassert>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#if QWT_VERSION >= 0x060100
#include <qwt_point_data.h>
#endif

#include "testtimer.h"
#include "ui_qttestmultiapproximatormaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolTestMultiApproximatorMainDialog::QtToolTestMultiApproximatorMainDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestMultiApproximatorMainDialog),
  m_multi_approximator(),
  m_curve_approximation(new QwtPlotCurve),
  m_curve_multi_approximation(new QwtPlotCurve),
  m_curve_multi_values(new QwtPlotCurve),
  m_curve_values(new QwtPlotCurve),
  m_multi_plot(new QwtPlot),
  m_plot(new QwtPlot)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Set up the plots
  assert(m_multi_plot);
  m_multi_plot->setTitle("MultiApproximator");
  m_multi_plot->setAxisTitle(QwtPlot::xBottom,"Key");
  m_multi_plot->setAxisTitle(QwtPlot::yLeft,"Value");
  #ifdef _WIN32
  m_multi_plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  m_multi_plot->setCanvasBackground(QColor(255,255,255));
  #endif

  assert(m_plot);
  m_plot->setTitle("Approximator");
  m_plot->setAxisTitle(QwtPlot::xBottom,"Key");
  m_plot->setAxisTitle(QwtPlot::yLeft,"Value");
  #ifdef _WIN32
  m_plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  m_plot->setCanvasBackground(QColor(255,255,255));
  #endif

  //Create plots
  assert(m_curve_multi_values);
  m_curve_multi_values->setTitle("Points");
  m_curve_multi_values->attach(m_multi_plot.get());
  m_curve_multi_values->setStyle(QwtPlotCurve::Dots);
  m_curve_multi_values->setPen(QPen(QColor(255,0,0),5));

  assert(m_curve_multi_approximation);
  m_curve_multi_approximation->setTitle("Approximation");
  m_curve_multi_approximation->attach(m_multi_plot.get());
  m_curve_multi_approximation->setStyle(QwtPlotCurve::Lines);
  m_curve_multi_approximation->setPen(QPen(QColor(0,0,255),3));

  assert(m_curve_values);
  m_curve_values->setTitle("Points");
  m_curve_values->attach(m_plot.get());
  m_curve_values->setStyle(QwtPlotCurve::Dots);
  m_curve_values->setPen(QPen(QColor(255,0,0),5));

  assert(m_curve_approximation);
  m_curve_approximation->setTitle("Approximation");
  m_curve_approximation->attach(m_plot.get());
  m_curve_approximation->setStyle(QwtPlotCurve::Lines);
  m_curve_approximation->setPen(QPen(QColor(0,0,255),3));

  //Add grids
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(m_multi_plot.get());
  }
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(m_plot.get());
  }
  //Add zoomers
  //{
  //  new QwtPlotZoomer(m_multi_plot->canvas());
  //  new QwtPlotZoomer(m_plot->canvas());
  //}
  //Add legends
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    m_multi_plot->insertLegend(legend, QwtPlot::RightLegend);
  }
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    m_plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  assert(ui->verticalLayout->layout());
  ui->verticalLayout->layout()->addWidget(m_multi_plot.get());
  ui->verticalLayout->layout()->addWidget(m_plot.get());

  m_multi_plot->setAxisScale(
    QwtPlot::xBottom,
    static_cast<double>(ui->box_int_x->minimum()),
    static_cast<double>(ui->box_int_x->maximum())
  );
  m_multi_plot->setAxisScale(
    QwtPlot::yLeft,
    static_cast<double>(ui->box_double_y->minimum()),
    static_cast<double>(ui->box_double_y->maximum())
  );

  m_plot->setAxisScale(
    QwtPlot::xBottom,
    static_cast<double>(ui->box_int_x->minimum()),
    static_cast<double>(ui->box_int_x->maximum())
  );
  m_plot->setAxisScale(
    QwtPlot::yLeft,
    static_cast<double>(ui->box_double_y->minimum()),
    static_cast<double>(ui->box_double_y->maximum())
  );

  //Add some nice testing values
  const double min_x = ui->box_int_x->minimum();
  const double max_x = ui->box_int_x->maximum();
  const double min_y = ui->box_double_y->minimum();
  const double max_y = ui->box_double_y->maximum();
  const double dy = max_y / 4.0;

  ui->box_int_x->setValue(min_x / 2);
  ui->box_double_y->setValue((max_y / 2.0) + dy);
  on_button_clicked();
  ui->box_double_y->setValue((max_y / 2.0) - dy);
  on_button_clicked();

  ui->box_int_x->setValue(min_x / 4);
  ui->box_double_y->setValue((min_y / 2.0) + dy);
  on_button_clicked();
  ui->box_double_y->setValue((min_y / 2.0) - dy);
  on_button_clicked();

  ui->box_int_x->setValue(max_x / 4);
  ui->box_double_y->setValue((max_y / 2.0) + dy);
  on_button_clicked();
  ui->box_double_y->setValue((max_y / 2.0) - dy);
  on_button_clicked();

  ui->box_int_x->setValue(max_x / 2);
  ui->box_double_y->setValue((min_y / 2.0) + dy);
  on_button_clicked();
  ui->box_double_y->setValue((min_y / 2.0) - dy);
  on_button_clicked();

  ui->box_int_x->setValue(0);
  ui->box_double_y->setValue(0.0);
}

ribi::QtToolTestMultiApproximatorMainDialog::~QtToolTestMultiApproximatorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestMultiApproximatorMainDialog::on_button_clicked() noexcept
{
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  m_multi_approximator.Add(x,y);
  Plot();
}

void ribi::QtToolTestMultiApproximatorMainDialog::Plot() noexcept
{
  //Plot multi approximation
  {
    //Plot raw data
    {
      std::vector<double> xs;
      std::vector<double> ys;
      for (const auto p: m_multi_approximator.GetContainer())
      {
        xs.push_back( static_cast<double>(p.first) );
        ys.push_back( static_cast<double>(p.second) );
      }
      assert(m_curve_multi_values);
      #if QWT_VERSION >= 0x060000
      m_curve_multi_values->setData(new QwtPointArrayData(&xs[0],&ys[0],xs.size()));
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
          const MultiApproximator_t::value_type y = m_multi_approximator.Approximate(x);
          ys.push_back(y);
          xs.push_back(x);
        }
        catch (ExceptionNoExtrapolation<MultiApproximator_t::key_type>& e)
        {

        }
      }
      assert(m_curve_multi_approximation);
      #if QWT_VERSION >= 0x060000
      m_curve_multi_approximation->setData(new QwtPointArrayData(&xs[0],&ys[0],xs.size()));
      #else
      m_curve_multi_approximation->setData(&xs[0],&y[0],xs.size());
      #endif
    }
    assert(m_multi_plot);
    m_multi_plot->replot();
  }
  //Plot (non-multi)approximation
  {
    //const Approximator<Key,Value,Container> approximator(
    const auto approximator(
      ToApproximator<Key,Value,MultiContainer,Container>(m_multi_approximator)
    );
    //Plot raw data
    {
      std::vector<double> xs;
      std::vector<double> ys;
      for (const auto p: approximator.Get())
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
          const Approximator_t::value_type y = approximator.Approximate(x);
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
  }
}

#ifndef NDEBUG
void ribi::QtToolTestMultiApproximatorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
