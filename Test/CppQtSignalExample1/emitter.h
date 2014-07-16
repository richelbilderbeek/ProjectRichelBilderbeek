#ifndef EMITTER_H
#define EMITTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QObject>
#pragma GCC diagnostic pop

class Emitter : public QObject
{
  Q_OBJECT
public:
  explicit Emitter(QObject *parent = 0);
  void DoEmit() const noexcept;

signals:
  void signal_emit() const;
};

#endif // EMITTER_H
