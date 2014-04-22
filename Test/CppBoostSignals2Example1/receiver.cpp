#include <iostream>
#include "receiver.h"

QtReceiver::QtReceiver(QObject *parent) :
    QObject(parent)
{

}

void QtReceiver::OnReceive()
{
  std::clog << "QtReceiver: received signal\n";
}

void Receiver::OnReceive()
{
  std::clog << "Receiver: received signal\n";
}
