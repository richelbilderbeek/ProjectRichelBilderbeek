#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "MyDialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  boost::scoped_ptr<MyDialog> dialog(new MyDialog);
  boost::scoped_ptr<QVBoxLayout> layout(new QVBoxLayout);
  boost::scoped_ptr<QPushButton> button1(new QPushButton);
  boost::scoped_ptr<QPushButton> button2(new QPushButton);

  button1->setText("Count");
  button1->connect(
    button1.get(),SIGNAL(clicked()),
    dialog.get(),SLOT(buttonClicked()));
  button2->setText("Quit");
  button2->connect(
    button2.get(),SIGNAL(clicked()),
    dialog.get(),SLOT(close()));
  layout->addWidget(button1.get());
  layout->addWidget(button2.get());

  dialog->setGeometry(0,0,300,100);
  dialog->setWindowTitle("CppQtExample12");
  dialog->setLayout(layout.get());

  dialog->show();
  return a.exec();
}
