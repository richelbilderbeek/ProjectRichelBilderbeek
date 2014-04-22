#ifndef QTSECRETMESSAGECREATEDIALOG_H
#define QTSECRETMESSAGECREATEDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSecretMessageCreateDialog;
}

namespace ribi {
namespace sema {

class QtSecretMessageCreateDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtSecretMessageCreateDialog(QWidget *parent = 0);
  QtSecretMessageCreateDialog(const QtSecretMessageCreateDialog&) = delete;
  QtSecretMessageCreateDialog& operator=(const QtSecretMessageCreateDialog&) = delete;
  ~QtSecretMessageCreateDialog() noexcept;
    
private slots:
  void on_button_load_original_clicked();

  void on_button_load_secret_clicked();

  void on_button_save_clicked();

private:
  Ui::QtSecretMessageCreateDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace sema
} //~namespace ribi

#endif // QTSECRETMESSAGECREATEDIALOG_H
