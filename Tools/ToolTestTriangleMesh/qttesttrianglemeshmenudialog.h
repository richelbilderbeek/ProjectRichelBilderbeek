#ifndef QTTESTTRIANGLEMESHMENUDIALOG_H
#define QTTESTTRIANGLEMESHMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestTriangleMeshMenuDialog;
}

namespace ribi {

class QtTestTriangleMeshMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtTestTriangleMeshMenuDialog(QWidget *parent = 0);
  QtTestTriangleMeshMenuDialog(const QtTestTriangleMeshMenuDialog&) = delete;
  QtTestTriangleMeshMenuDialog& operator=(const QtTestTriangleMeshMenuDialog&) = delete;
  ~QtTestTriangleMeshMenuDialog() noexcept;
    
private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestTriangleMeshMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTRIANGLEMESHMENUDIALOG_H
