#ifndef QTPAPERROCKSCISSORSMAINDIALOG_H
#define QTPAPERROCKSCISSORSMAINDIALOG_H

#include "qthideandshowdialog.h"

struct QtPaperRockScissorsWidget;
struct QwtPlotCurve;

namespace Ui { class QtPaperRockScissorsMainDialog; }

class QtPaperRockScissorsMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPaperRockScissorsMainDialog(QWidget *parent = 0);
  QtPaperRockScissorsMainDialog(const QtPaperRockScissorsMainDialog&) = delete;
  QtPaperRockScissorsMainDialog& operator=(const QtPaperRockScissorsMainDialog&) = delete;
  ~QtPaperRockScissorsMainDialog();

private slots:
  void OnAnyChange();

private:
  Ui::QtPaperRockScissorsMainDialog *ui;
  QtPaperRockScissorsWidget * const m_widget;

  QwtPlotCurve * const m_curve_popsizes;
  QwtPlotCurve * const m_curve_traits;

};

#endif // QTPAPERROCKSCISSORSMAINDIALOG_H
