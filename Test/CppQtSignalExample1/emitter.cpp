#include "emitter.h"

#include <iostream>

Emitter::Emitter(QObject *parent)
  : QObject(parent)
{
}

void Emitter::DoEmit() const noexcept
{
  std::clog << "Emitter: emitting signal" << std::endl;
  emit signal_emit();
}
