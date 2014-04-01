#include "qtcodebreakermaindialog.h"
#include "ui_qtcodebreakermaindialog.h"

QtCodeBreakerMainDialog::QtCodeBreakerMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtCodeBreakerMainDialog)
{
  ui->setupUi(this);
}

QtCodeBreakerMainDialog::~QtCodeBreakerMainDialog()
{
  delete ui;
}

void QtCodeBreakerMainDialog::on_lineEdit_2_textEdited(const QString &arg1)
{
  std::string s = ui-
}
