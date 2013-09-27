#ifndef QTVIRTUALBASTARDEXAMPLE1DIALOG_H
#define QTVIRTUALBASTARDEXAMPLE1DIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtVirtualBastardExample1Dialog;
}

class QtVirtualBastardExample1Dialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtVirtualBastardExample1Dialog(QWidget *parent = 0);
  QtVirtualBastardExample1Dialog(const QtVirtualBastardExample1Dialog&) = delete;
  QtVirtualBastardExample1Dialog& operator=(const QtVirtualBastardExample1Dialog&) = delete;
  ~QtVirtualBastardExample1Dialog();
  
private:
  Ui::QtVirtualBastardExample1Dialog *ui;
};

#endif // QTVIRTUALBASTARDEXAMPLE1DIALOG_H
