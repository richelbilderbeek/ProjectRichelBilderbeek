#ifndef EMITTER_H
#define EMITTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QObject>
#pragma GCC diagnostic pop

class QtEmitter : public QObject
{
  Q_OBJECT
public:
  explicit QtEmitter(QObject *parent = 0);
  void DoEmit();

signals:
  void signal_emit();
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

struct Emitter
{
  boost::signals2::signal<void ()> m_signal;
  void DoEmit();
};

#endif // EMITTER_H
