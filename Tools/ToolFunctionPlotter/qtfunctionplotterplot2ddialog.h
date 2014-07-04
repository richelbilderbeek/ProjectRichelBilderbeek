#ifndef QTFUNCTIONPLOTTERMAINDIALOG_H
#define QTFUNCTIONPLOTTERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtFunctionPlotterPlot2dDialog;
}

struct QwtPlot;
struct QwtPlotCurve;

namespace ribi {

class QtFunctionPlotterPlot2dDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtFunctionPlotterPlot2dDialog(QWidget *parent = 0);
    QtFunctionPlotterPlot2dDialog(const QtFunctionPlotterPlot2dDialog&) = delete;
    QtFunctionPlotterPlot2dDialog& operator=(const QtFunctionPlotterPlot2dDialog&) = delete;
    ~QtFunctionPlotterPlot2dDialog() noexcept;
    
private slots:
    void resizeEvent(QResizeEvent *);
    void OnAnyChange() noexcept;

private:
    Ui::QtFunctionPlotterPlot2dDialog *ui;

  QwtPlotCurve * const m_curve;
  QwtPlot * const m_plot;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTFUNCTIONPLOTTERMAINDIALOG_H
