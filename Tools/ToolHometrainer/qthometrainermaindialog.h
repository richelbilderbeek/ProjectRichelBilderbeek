#ifndef QTHOMETRAINERMAINDIALOG_H
#define QTHOMETRAINERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtHometrainerMainDialog;
}

namespace ribi {

class QtHometrainerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtHometrainerMainDialog(QWidget *parent = 0) noexcept;
  QtHometrainerMainDialog(const QtHometrainerMainDialog&) = delete;
  QtHometrainerMainDialog& operator=(const QtHometrainerMainDialog&) = delete;
  ~QtHometrainerMainDialog() noexcept;
  
private:
  Ui::QtHometrainerMainDialog *ui;
};

} //~namespace ribi

#endif // QTHOMETRAINERMAINDIALOG_H
