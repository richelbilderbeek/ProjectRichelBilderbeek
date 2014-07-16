#include "receiver.h"

#include <iostream>

Receiver::Receiver(QObject *parent)
  : QObject(parent)
{

}

void Receiver::OnReceive() const noexcept
{
  std::clog << "Receiver: received signal" << std::endl;
}
