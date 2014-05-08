#ifndef QTEVERYTHINGTOPIECESSHOOTERGAMEWIDGET_H
#define QTEVERYTHINGTOPIECESSHOOTERGAMEWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <set>

#include <QWidget>
#pragma GCC diagnostic pop

class QtEverythingToPiecesShooterGameWidget : public QWidget
{
  Q_OBJECT

public:
  QtEverythingToPiecesShooterGameWidget();
  enum class Direction { up, right, down, left };
  enum class Key { up, right, down, left };

private:
  Direction m_direction;
  std::set<Key> m_keys;
  double m_x;
  double m_y;
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);
  void paintEvent(QPaintEvent *);

private slots:
  void OnTimer();
};

#endif // QTEVERYTHINGTOPIECESSHOOTERGAMEWIDGET_H
