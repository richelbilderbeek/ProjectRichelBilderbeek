#include "cppqwebviewexample1dialog.h"
#include "ui_cppqwebviewexample1dialog.h"

CppQWebViewExample1Dialog::CppQWebViewExample1Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CppQWebViewExample1Dialog)
{
  ui->setupUi(this);

  ui->webView->setHtml(
    "<h1>Hello World</h1>"
    "<h2>Hello World</h2>"
    "<h3>Hello World</h3>"
    "<p>Hello World</p>"
    "<ul><li>Hello World</li></ul>"
  );
}

CppQWebViewExample1Dialog::~CppQWebViewExample1Dialog()
{
  delete ui;
}
