#ifndef QTVIRTUALBASTARDMENUDIALOG_H
#define QTVIRTUALBASTARDMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtVirtualBastardMenuDialog;
}

class QtVirtualBastardMenuDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtVirtualBastardMenuDialog(QWidget *parent = 0);
  QtVirtualBastardMenuDialog(const QtVirtualBastardMenuDialog&) = delete;
  QtVirtualBastardMenuDialog& operator=(const QtVirtualBastardMenuDialog&) = delete;
  ~QtVirtualBastardMenuDialog();
  
private slots:
  void on_button_start_clicked();

  void on_button_1_clicked();

private:
  Ui::QtVirtualBastardMenuDialog *ui;
};

#endif // QTVIRTUALBASTARDMENUDIALOG_H
