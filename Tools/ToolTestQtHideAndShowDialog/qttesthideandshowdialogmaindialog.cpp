#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesthideandshowdialogmaindialog.h"

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include "ui_qttesthideandshowdialogmaindialog.h"
#pragma GCC diagnostic pop

QtTestHideAndShowMainDialog::QtTestHideAndShowMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestHideAndShowMainDialog)
{
  ui->setupUi(this);

  {
    const std::string s(200,boost::lexical_cast<char,std::string>("."));
    ui->label_spacer->setText(s.c_str());
  }

  const QString s = "Dialog width: " + QString::number(this->width()) + " pixels";
  ui->label_width_constructor->setText(s);
}

QtTestHideAndShowMainDialog::~QtTestHideAndShowMainDialog() noexcept
{
  delete ui;
}

void QtTestHideAndShowMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtTestHideAndShowMainDialog::showEvent(QShowEvent *)
{
  const QString s = "Dialog width: " + QString::number(this->width()) + " pixels";
  ui->label_width_showevent->setText(s);

}

void QtTestHideAndShowMainDialog::on_button_clicked()
{
  QtTestHideAndShowMainDialog d;

  //Move the child dialog a 8 pixels down and right
  QPoint pos = this->pos();
  pos+=QPoint(8,8);
  d.move(pos);

  this->ShowChild(&d);
}
