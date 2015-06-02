#include "qtstochasticityinspectorstackedbarplotsupportwidget.h"

#include <qwt_column_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>
#include <qwt_point_data.h>

#include "qtstochasticityinspectormodelcolors.h"
#include "ui_qtstochasticityinspectorstackedbarplotsupportwidget.h"


QtStochasticityInspectorStackedBarPlotSupportWidget::QtStochasticityInspectorStackedBarPlotSupportWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtStochasticityInspectorStackedBarPlotSupportWidget),
  m_support_plot{new QwtPlot(QwtText("Support for different models"))},
  m_support_plot_barchart{new QwtPlotMultiBarChart}
{
  ui->setupUi(this);

  //Prepare support widget
  for (int i=0; i!=2; ++i)
  {
    QwtColumnSymbol * symbol{new QwtColumnSymbol(QwtColumnSymbol::Box)};
    QPalette bar_color{i == 0
      ? ribi::QtStochasticityInspectorModelColors::m_bm_color
      : ribi::QtStochasticityInspectorModelColors::m_ou_color
    };
    symbol->setPalette(bar_color);
    m_support_plot_barchart->setSymbol(i,symbol);
  }
  QList<QwtText> titles;
  titles.push_back(QwtText("BM"));
  titles.push_back(QwtText("OU"));
  m_support_plot_barchart->setBarTitles(titles);

  QVector<QVector<double>> data;
  {
    const double a{0.6};
    const double b{1.0-a};
    QVector<double> this_bar = {a,b};
    data.push_back(this_bar);
  }
  m_support_plot_barchart->setSamples(data);
  m_support_plot_barchart->setStyle(QwtPlotMultiBarChart::Stacked);


  //plot is used to display the bar_plot on screen
  m_support_plot_barchart->attach(m_support_plot);
  m_support_plot->setAxisScale(QwtPlot::xBottom,0.0,1.0,1.0);
  m_support_plot->setAxisScale(QwtPlot::yLeft,0.0,1.0,0.1);
  //m_support_plot->setAxisTitle(QwtPlot::xBottom,"Sample");
  m_support_plot->setAxisTitle(QwtPlot::yLeft,"Fractions");

  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    m_support_plot->insertLegend(legend, QwtPlot::RightLegend);
  }
}

QtStochasticityInspectorStackedBarPlotSupportWidget::~QtStochasticityInspectorStackedBarPlotSupportWidget()
{
  delete ui;
}

void QtStochasticityInspectorStackedBarPlotSupportWidget::ShowSupport(
  const double log_likelihood_bm, const double log_likelihood_ou
)
{
  QVector<QVector<double>> data;

  const double a{log_likelihood_bm};
  const double b{log_likelihood_ou};
  QVector<double> this_bar
    =
    {
      std::exp(a) / (std::exp(a)+std::exp(b)),
      std::exp(b) / (std::exp(b)+std::exp(a))
    };
  data.push_back(this_bar);

  m_support_plot_barchart->setSamples(data);
  m_support_plot->replot();
}
