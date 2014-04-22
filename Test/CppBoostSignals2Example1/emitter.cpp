#include <iostream>
#include "emitter.h"

QtEmitter::QtEmitter(QObject *parent) :
    QObject(parent)
{
}

void QtEmitter::DoEmit()
{
  std::clog << "QtEmitter: emitting signal\n";
  emit signal_emit();
}

void Emitter::DoEmit()
{
  m_signal();
  std::clog << "Emitter: emitting signal\n";
}
