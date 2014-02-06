#ifndef QTFUNCTIONPLOTTERMAINDIALOG_H
#define QTFUNCTIONPLOTTERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtFunctionPlotterMainDialog;
}

struct QwtPlot;
struct QwtPlotCurve;

namespace ribi {

class QtFunctionPlotterMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtFunctionPlotterMainDialog(QWidget *parent = 0);
    QtFunctionPlotterMainDialog(const QtFunctionPlotterMainDialog&) = delete;
    QtFunctionPlotterMainDialog& operator=(const QtFunctionPlotterMainDialog&) = delete;
    ~QtFunctionPlotterMainDialog() noexcept;
    
private slots:
    void resizeEvent(QResizeEvent *);
    void OnAnyChange() noexcept;

private:
    Ui::QtFunctionPlotterMainDialog *ui;

  QwtPlotCurve * const m_curve;
  QwtPlot * const m_plot;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTFUNCTIONPLOTTERMAINDIALOG_H
