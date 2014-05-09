#ifndef QTGAMEWIDGET_H
#define QTGAMEWIDGET_H

#include <set>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"


#include <boost/shared_ptr.hpp>

#include <QWidget>

#include "tankbattalion.h"
#pragma GCC diagnostic pop

namespace Qt
{
  struct QImage;
}

class QtGameWidget : public QWidget
{
    Q_OBJECT
public:
  enum class Direction { up, right, down, left };
  enum class Key { up, right, down, left };
  typedef std::map<TankBattalion::SpriteType,boost::shared_ptr<QImage>> SpriteMap;
  explicit QtGameWidget(QWidget *parent = 0);


  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);

protected:
  void paintEvent(QPaintEvent *);

private:
  Direction m_direction;
  std::set<Key> m_keys;
  const SpriteMap m_sprites;
  int m_x;
  int m_y;

  const SpriteMap CreateSprites() const;
  const boost::shared_ptr<QImage> GetImage(const TankBattalion::SpriteType& s) const;

private slots:
  void OnTimer();

};

#endif // QTGAMEWIDGET_H
