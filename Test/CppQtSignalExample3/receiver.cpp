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

void Receiver::OnReceive(const double x) const noexcept
{
  std::clog << "Receiver: received signal: a double with value " << x << std::endl;
}
