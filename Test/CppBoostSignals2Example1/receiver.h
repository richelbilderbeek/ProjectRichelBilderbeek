#ifndef RECEIVER_H
#define RECEIVER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QObject>
#pragma GCC diagnostic pop

class QtReceiver : public QObject
{
  Q_OBJECT
public:
  explicit QtReceiver(QObject *parent = 0);

signals:

public slots:
  void OnReceive();
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

struct Receiver
{
  void OnReceive();
};

#endif // RECEIVER_H
