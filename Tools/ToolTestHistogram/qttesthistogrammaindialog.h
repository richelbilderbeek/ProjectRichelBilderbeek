#ifndef QTTESTHISTOGRAMMAINDIALOG_H_H
#define QTTESTHISTOGRAMMAINDIALOG_H_H

#include "qthideandshowdialog.h"

struct QwtPlotCurve;

namespace Ui {
  class QtTestHistogramMainDialog;
}

class QtTestHistogramMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestHistogramMainDialog(QWidget *parent = 0);
  ~QtTestHistogramMainDialog();

private slots:
  void Run();

private:
  Ui::QtTestHistogramMainDialog *ui;

  QwtPlotCurve * const m_curve_histogram;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTTESTHISTOGRAMMAINDIALOG_H_H
