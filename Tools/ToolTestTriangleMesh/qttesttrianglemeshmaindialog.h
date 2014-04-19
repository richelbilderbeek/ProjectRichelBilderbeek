#ifndef QTTESTTRIANGLEMESHMAINDIALOG_H
#define QTTESTTRIANGLEMESHMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestTriangleMeshMainDialog;
}

namespace ribi {

class QtTestTriangleMeshMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestTriangleMeshMainDialog(QWidget *parent = 0);
  QtTestTriangleMeshMainDialog(const QtTestTriangleMeshMainDialog&) = delete;
  QtTestTriangleMeshMainDialog& operator=(const QtTestTriangleMeshMainDialog&) = delete;
  ~QtTestTriangleMeshMainDialog() noexcept;
    
private:
  Ui::QtTestTriangleMeshMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTRIANGLEMESHMAINDIALOG_H
