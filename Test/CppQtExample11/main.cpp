#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  boost::scoped_ptr<QDialog> dialog(new QDialog);
  boost::scoped_ptr<QVBoxLayout> layout(new QVBoxLayout);
  boost::scoped_ptr<QPushButton> button1(new QPushButton);
  boost::scoped_ptr<QPushButton> button2(new QPushButton);

  //Cannot let button1 do anything fancy,
  //without creating a derived class from QDialog
  button1->setText("Nothing");
  button2->setText("Quit");
  button2->connect(button2.get(),SIGNAL(clicked()),dialog.get(),SLOT(close()));
  layout->addWidget(button1.get());
  layout->addWidget(button2.get());

  dialog->setGeometry(0,0,200,100);
  dialog->setWindowTitle("CppQtExample11");
  dialog->setLayout(layout.get());

  dialog->show();
  return a.exec();
}
