#ifndef QTSTATEOBSERVERMAINDIALOG_H
#define QTSTATEOBSERVERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlotCurve;

namespace Ui {
  class QtStateObserverMainDialog;
}

namespace ribi {

class QtStateObserverMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtStateObserverMainDialog(QWidget *parent = 0) noexcept;
  QtStateObserverMainDialog(const QtStateObserverMainDialog&) = delete;
  QtStateObserverMainDialog& operator=(const QtStateObserverMainDialog&) = delete;
  ~QtStateObserverMainDialog() noexcept;
  
private slots:
  void Run() noexcept;

  void on_button_rerun_clicked() noexcept;


private:
  Ui::QtStateObserverMainDialog *ui;

  QwtPlotCurve * const m_curve_ou;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTATEOBSERVERMAINDIALOG_H
