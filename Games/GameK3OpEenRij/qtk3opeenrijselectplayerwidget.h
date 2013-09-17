#ifndef QTK3OPEENRIJSELECTPLAYERWIDGET_H
#define QTK3OPEENRIJSELECTPLAYERWIDGET_H

#include <bitset>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include <QImage>
#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct QtK3OpEenRijResources;

class QtK3OpEenRijSelectPlayerWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtK3OpEenRijSelectPlayerWidget(
    const boost::shared_ptr<const QtK3OpEenRijResources> resources,
    QWidget *parent = 0);
  const std::bitset<3>& GetIsPlayerHuman() const { return m_is_player_human; }
  bool GetIsPlayer3Kathleen() const { return m_is_player3_kathleen; }

protected:
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);


private:
  bool m_is_player3_kathleen; //Player 3 can be either Kathleen or Josje
  std::bitset<3> m_is_player_human;
  const QImage m_josje;
  const QImage m_josje_grey;
  const QImage m_karen;
  const QImage m_karen_grey;
  const QImage m_kathleen;
  const QImage m_kathleen_grey;
  const QImage m_kristel;
  const QImage m_kristel_grey;
  const QImage m_computer1;
  const QImage m_computer2;
  const QImage m_computer3;
  const QImage m_computer_grey;
  static const int m_sprite_height;
  static const int m_sprite_width;
};

} //~namespace ribi

#endif // QTK3OPEENRIJSELECTPLAYERWIDGET_H
