#ifndef QTSTOCHASTICITYINSPECTORSTACKEDBARPLOTSUPPORTWIDGET_H
#define QTSTOCHASTICITYINSPECTORSTACKEDBARPLOTSUPPORTWIDGET_H

#include <QWidget>

namespace Ui {
  class QtStochasticityInspectorStackedBarPlotSupportWidget;
}

struct QwtPlot;
struct QwtPlotMultiBarChart;

class QtStochasticityInspectorStackedBarPlotSupportWidget : public QWidget
{
  Q_OBJECT

public:
  using This = QtStochasticityInspectorStackedBarPlotSupportWidget;

  explicit QtStochasticityInspectorStackedBarPlotSupportWidget(QWidget *parent = 0);
  QtStochasticityInspectorStackedBarPlotSupportWidget (const This&) = delete;
  This& operator=(const This&) = delete;
  ~QtStochasticityInspectorStackedBarPlotSupportWidget();

  void ShowSupport(const double log_likelihood_bm, const double log_likelihood_ou);

private:
  Ui::QtStochasticityInspectorStackedBarPlotSupportWidget *ui;


  ///Does the actual displayal on screen
  QwtPlot * const m_support_plot;

  ///Contains the data
  QwtPlotMultiBarChart * const m_support_plot_barchart;

};

#endif // QTSTOCHASTICITYINSPECTORSTACKEDBARPLOTSUPPORTWIDGET_H
