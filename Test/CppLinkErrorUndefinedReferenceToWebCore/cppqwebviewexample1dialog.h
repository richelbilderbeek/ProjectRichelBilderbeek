#ifndef CPPQWEBVIEWEXAMPLE1DIALOG_H
#define CPPQWEBVIEWEXAMPLE1DIALOG_H

#include <QDialog>

namespace Ui {
  class CppQWebViewExample1Dialog;
}

class CppQWebViewExample1Dialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit CppQWebViewExample1Dialog(QWidget *parent = 0);
  ~CppQWebViewExample1Dialog();
  
private:
  Ui::CppQWebViewExample1Dialog *ui;
};

#endif // CPPQWEBVIEWEXAMPLE1DIALOG_H
