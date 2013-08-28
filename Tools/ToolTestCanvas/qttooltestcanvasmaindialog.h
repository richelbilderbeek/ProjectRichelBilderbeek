#ifndef QTTOOLTESTCANVASMAINDIALOG_H
#define QTTOOLTESTCANVASMAINDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolTestCanvasMainDialog;
}

class QtToolTestCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestCanvasMainDialog(QWidget *parent = 0);
  ~QtToolTestCanvasMainDialog();
  
private slots:

  void on_box_color_system_currentIndexChanged(int index);

  void on_box_coordinat_system_currentIndexChanged(int index);

private:
  Ui::QtToolTestCanvasMainDialog *ui;
  void ShowCanvas();
};

#endif // QTTOOLTESTCANVASMAINDIALOG_H
