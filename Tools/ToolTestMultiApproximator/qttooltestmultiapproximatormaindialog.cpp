#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooltestmultiapproximatormaindialog.h"

#include <cassert>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#if QWT_VERSION >= 0x060000
#include <qwt_point_data.h>
#endif

#include "ui_qttooltestmultiapproximatormaindialog.h"
#pragma GCC diagnostic pop

QtToolTestMultiApproximatorMainDialog::QtToolTestMultiApproximatorMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestMultiApproximatorMainDialog),
  m_approximator(),
  m_curve_approximation(new QwtPlotCurve),
  m_curve_values(new QwtPlotCurve),
  m_plot(new QwtPlot)
{
  ui->setupUi(this);

  //Set up the plot
  assert(m_plot);
  m_plot->setTitle("MultiApproximator");
  m_plot->setAxisTitle(QwtPlot::xBottom,"Key");
  m_plot->setAxisTitle(QwtPlot::yLeft,"Value");
  #ifdef _WIN32
  m_plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  plot->setCanvasBackground(QColor(255,255,255));
  #endif

  //Create plots
  assert(m_curve_values);
  m_curve_values->setTitle("Points");
  m_curve_values->attach(m_plot.get());
  m_curve_values->setStyle(QwtPlotCurve::Dots);
  m_curve_values->setPen(QPen(QColor(255,0,0),5));

  assert(m_curve_approximation);
  m_curve_approximation->setTitle("Approximation");
  m_curve_approximation->attach(m_plot.get());
  m_curve_approximation->setStyle(QwtPlotCurve::Dots);
  m_curve_approximation->setPen(QPen(QColor(0,0,255),3));

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(m_plot.get());
  }
  //Add zoomer
  {
    new QwtPlotZoomer(m_plot->canvas());
  }
  {
    // legend
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    m_plot->insertLegend(legend, QwtPlot::RightLegend);
  }
  assert(ui->verticalLayout->layout());
  ui->verticalLayout->layout()->addWidget(m_plot.get());

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

  TRACE_FUNC();
}

QtToolTestMultiApproximatorMainDialog::~QtToolTestMultiApproximatorMainDialog()
{
  delete ui;
}

void QtToolTestMultiApproximatorMainDialog::on_button_clicked()
{
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  m_approximator.Add(x,y);
  Plot();
}

void QtToolTestMultiApproximatorMainDialog::Plot()
{
  //Plot approximation
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto p: m_approximator.GetContainer())
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
        const MultiApproximator_t::value_type y = m_approximator.Approximate(x);
        ys.push_back(y);
        xs.push_back(x);
      }
      catch (ExceptionNoExtrapolation<MultiApproximator_t::key_type>& e)
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
