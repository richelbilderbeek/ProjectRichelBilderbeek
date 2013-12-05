#ifndef QTFUNCTIONPLOTTERMAINDIALOG_H
#define QTFUNCTIONPLOTTERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtFunctionPlotterMainDialog;
}

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


  ///Rescale calculates a value between old_min and old_max its relative place and transforms
  ///this relative position to a new_min and new_max
  ///For example: for the old range [1,5], the value 2 is at 25% of this range. Transforming this
  ///to the new range range [0,100] results in a 25
  static double Rescale(
    const double value,
    const double oldMin,
    const double oldMax,
    const double newMin,
    const double newMax);

};

} //~namespace ribi

#endif // QTFUNCTIONPLOTTERMAINDIALOG_H
