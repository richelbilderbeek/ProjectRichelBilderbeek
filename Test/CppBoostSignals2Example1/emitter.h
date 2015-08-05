#ifndef EMITTER_H
#define EMITTER_H

#include <QObject>

class QtEmitter : public QObject
{
  Q_OBJECT
public:
  explicit QtEmitter(QObject *parent = 0);
  void DoEmit();

signals:
  void signal_emit();
};

#include <boost/signals2.hpp>

struct Emitter
{
  Emitter() : m_signal{} {}
  boost::signals2::signal<void ()> m_signal;
  void DoEmit();
};

#endif // EMITTER_H
