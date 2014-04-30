#ifndef QTTOOLTESTTEXTPOSITIONWIDGETMAINDIALOG_H
#define QTTOOLTESTTEXTPOSITIONWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestTextPositionWidgetMainDialog;
}

namespace ribi {

class QtTestTextPositionWidgetMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestTextPositionWidgetMainDialog(QWidget *parent = 0);
  QtTestTextPositionWidgetMainDialog(const QtTestTextPositionWidgetMainDialog&) = delete;
  QtTestTextPositionWidgetMainDialog& operator = (const QtTestTextPositionWidgetMainDialog&) = delete;
  ~QtTestTextPositionWidgetMainDialog() noexcept;
    
private:
  Ui::QtTestTextPositionWidgetMainDialog *ui;
};

} //~namespace ribi

#endif // QTTOOLTESTTEXTPOSITIONWIDGETMAINDIALOG_H
