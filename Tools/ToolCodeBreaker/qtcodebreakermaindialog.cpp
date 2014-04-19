#include "qtcodebreakermaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QVBoxLayout>

#include "qtcaesarciphermaindialog.h"
#include "qtvigenereciphermaindialog.h"

#include "ui_qtcodebreakermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtCodeBreakerMainDialog::QtCodeBreakerMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtCodeBreakerMainDialog)
{
  ui->setupUi(this);

  assert(!this->layout());
  QLayout * const layout = new QVBoxLayout;
  assert(layout);
  this->setLayout(layout);

  {
    QtCaesarCipherMainDialog * const dialog
      = new QtCaesarCipherMainDialog;
    assert(dialog);
    layout->addWidget(dialog);
  }
  {
    QtVigenereCipherMainDialog * const dialog
      = new QtVigenereCipherMainDialog;
    assert(dialog);
    layout->addWidget(dialog);
  }
}

ribi::QtCodeBreakerMainDialog::~QtCodeBreakerMainDialog()
{
  delete ui;
}
