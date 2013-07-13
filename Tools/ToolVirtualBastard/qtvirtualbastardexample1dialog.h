#ifndef QTVIRTUALBASTARDEXAMPLE1DIALOG_H
#define QTVIRTUALBASTARDEXAMPLE1DIALOG_H

#include <QDialog>

namespace Ui {
  class QtVirtualBastardExample1Dialog;
}

class QtVirtualBastardExample1Dialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtVirtualBastardExample1Dialog(QWidget *parent = 0);
  ~QtVirtualBastardExample1Dialog();
  
private:
  Ui::QtVirtualBastardExample1Dialog *ui;
};

#endif // QTVIRTUALBASTARDEXAMPLE1DIALOG_H
