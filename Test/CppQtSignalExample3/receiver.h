#ifndef RECEIVER_H
#define RECEIVER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QObject>
#pragma GCC diagnostic pop

class Receiver : public QObject
{
  Q_OBJECT
public:
  explicit Receiver(QObject *parent = 0);

public slots:
  void OnReceive() const noexcept;
  void OnReceive(const double x) const noexcept;
};

#endif // RECEIVER_H
