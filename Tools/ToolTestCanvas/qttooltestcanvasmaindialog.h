#ifndef QTTOOLTESTCANVASMAINDIALOG_H
#define QTTOOLTESTCANVASMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolTestCanvasMainDialog;
}

namespace ribi {

class QtToolTestCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestCanvasMainDialog(QWidget *parent = 0);
  QtToolTestCanvasMainDialog(const QtToolTestCanvasMainDialog&) = delete;
  QtToolTestCanvasMainDialog& operator=(const QtToolTestCanvasMainDialog&) = delete;
  ~QtToolTestCanvasMainDialog() noexcept;
  
private slots:

  void on_box_color_system_currentIndexChanged(int index);

  void on_box_coordinat_system_currentIndexChanged(int index);

private:
  Ui::QtToolTestCanvasMainDialog *ui;
  void ShowCanvas();
};

} //~namespace ribi

#endif // QTTOOLTESTCANVASMAINDIALOG_H
