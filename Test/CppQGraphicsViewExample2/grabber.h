#ifndef GRABBER_H
#define GRABBER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QObject>
#pragma GCC diagnostic pop

struct Grabber : public QObject
{
  Q_OBJECT

  public:
  Grabber(
    const int win_id,
    const std::string& filename = "screengrab.png"
  );
  ~Grabber() noexcept;

  public slots:
  void Grab() const noexcept;

  private:
  const std::string m_filename;
  const int m_win_id;
};

#endif // GRABBER_H
