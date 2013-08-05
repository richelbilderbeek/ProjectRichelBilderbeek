#ifndef QTK3OPEENRIJSELECTPLAYERWIDGET_H
#define QTK3OPEENRIJSELECTPLAYERWIDGET_H

#include <bitset>

#include <QImage>
#include <QWidget>

class QtK3OpEenRijSelectPlayerWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtK3OpEenRijSelectPlayerWidget(QWidget *parent = 0);
  const std::bitset<3>& GetIsPlayerHuman() const { return m_is_player_human; }

protected:
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);


private:
  std::bitset<3> m_is_player_human;
  const QImage m_player1;
  const QImage m_player1_grey;
  const QImage m_player2;
  const QImage m_player2_grey;
  const QImage m_player3;
  const QImage m_player3_grey;
  const QImage m_computer1;
  const QImage m_computer2;
  const QImage m_computer3;
  const QImage m_computer_grey;
  static const int m_sprite_height;
  static const int m_sprite_width;
};

#endif // QTK3OPEENRIJSELECTPLAYERWIDGET_H
