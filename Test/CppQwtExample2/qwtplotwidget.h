#ifndef QWTPLOTWIDGET_H
#define QWTPLOTWIDGET_H

struct QwtPlot;
struct QwtPlotCurve;

#include <vector>
#include <QWidget>

struct QwtPlotWidget : public QWidget
{
  QwtPlotWidget(const int sz);

  void AddY(const double y);
private:
  QwtPlotCurve * const m_curve;
  QwtPlot * const m_plot;
  const std::vector<double> m_xs;
  std::vector<double> m_ys;

  static const std::vector<double> CreateXs(const int n);
};

#endif // QWTPLOTWIDGET_H
