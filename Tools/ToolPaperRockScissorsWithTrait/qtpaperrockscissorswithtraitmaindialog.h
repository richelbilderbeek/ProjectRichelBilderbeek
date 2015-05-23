#ifndef QTPAPERROCKSCISSORSMAINDIALOG_H
#define QTPAPERROCKSCISSORSMAINDIALOG_H

#include "qthideandshowdialog.h"

struct QtPaperRockScissorsWithTraitWidget;
struct QwtPlotCurve;

namespace Ui { class QtPaperRockScissorsWithTraitMainDialog; }

class QtPaperRockScissorsWithTraitMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPaperRockScissorsWithTraitMainDialog(QWidget *parent = 0);
  QtPaperRockScissorsWithTraitMainDialog(const QtPaperRockScissorsWithTraitMainDialog&) = delete;
  QtPaperRockScissorsWithTraitMainDialog& operator=(const QtPaperRockScissorsWithTraitMainDialog&) = delete;
  ~QtPaperRockScissorsWithTraitMainDialog();

private slots:
  ///When any parameter has changed
  void OnAnyChange();
  ///When the simulation has finished a timestep
  void OnNext();

private:
  Ui::QtPaperRockScissorsWithTraitMainDialog *ui;
  QtPaperRockScissorsWithTraitWidget * const m_widget;

  QwtPlotCurve * const m_curve_popsizes_paper;
  QwtPlotCurve * const m_curve_popsizes_rock;
  QwtPlotCurve * const m_curve_popsizes_scissors;
  QwtPlotCurve * const m_curve_traits_paper;
  QwtPlotCurve * const m_curve_traits_rock;
  QwtPlotCurve * const m_curve_traits_scissors;

  std::vector<double> m_timeseries;
  std::vector<double> m_popsizes_paper;
  std::vector<double> m_popsizes_rock;
  std::vector<double> m_popsizes_scissors;
  std::vector<double> m_traits_paper;
  std::vector<double> m_traits_rock;
  std::vector<double> m_traits_scissors;
};

#endif // QTPAPERROCKSCISSORSMAINDIALOG_H
