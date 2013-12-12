#ifndef QTSECRETMESSAGECREATEDIALOG_H
#define QTSECRETMESSAGECREATEDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSecretMessageCreateDialog;
}

namespace ribi {

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
  void paintEvent(QPaintEvent *);

private:
  Ui::QtSecretMessageCreateDialog *ui;
  QPixmap m_original;
  bool m_needs_repaint;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSECRETMESSAGECREATEDIALOG_H
