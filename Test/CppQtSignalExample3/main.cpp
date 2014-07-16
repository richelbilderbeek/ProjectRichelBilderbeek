#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <iostream>

#include <QApplication>
#include <QDoubleSpinBox>

#include "receiver.h"
#pragma GCC diagnostic pop

int main(int argc,char* argv[])
{
  QApplication a(argc,argv);

  QDoubleSpinBox b;
  Receiver r;
  //QObject::connect(&b,SIGNAL(valueChanged(double)),&r,SLOT(OnReceive(double))); //Qt4
  QObject::connect(&b,
    static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
    &r,
    static_cast<void (Receiver::*)(double) const>(&Receiver::OnReceive)
  ); //Qt5
  b.setValue(1.1);
  b.setValue(2.2);


  a.exit(); //To satisfy the compiler
  return 0; //To satisfy the compiler
}

/* Screen output:

Receiver: received signal: a double with value 1.1
Receiver: received signal: a double with value 2.2

*/
