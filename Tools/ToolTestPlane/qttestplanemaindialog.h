#ifndef QTTESTPLANEMAINDIALOG_H
#define QTTESTPLANEMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestPlaneMainDialog;
}

namespace ribi {

class QtTestPlaneMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPlaneMainDialog(QWidget *parent = 0);
  QtTestPlaneMainDialog(const QtTestPlaneMainDialog&) = delete;
  QtTestPlaneMainDialog& operator=(const QtTestPlaneMainDialog&) = delete;
  ~QtTestPlaneMainDialog() noexcept;
    
private slots:
  void OnAnyChange();
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtTestPlaneMainDialog *ui;

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

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTPLANEMAINDIALOG_H
