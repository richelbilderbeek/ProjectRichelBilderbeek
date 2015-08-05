#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class QtReceiver : public QObject
{
  Q_OBJECT
public:
  explicit QtReceiver(QObject *parent = 0);

signals:

public slots:
  void OnReceive();
};

#include <boost/signals2.hpp>

struct Receiver
{
  void OnReceive();
};

#endif // RECEIVER_H
