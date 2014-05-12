#ifndef QTGAMEWIDGET_H
#define QTGAMEWIDGET_H

#include <set>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"


#include <boost/shared_ptr.hpp>

#include <QWidget>

#include "tankbattaliondirection.h"
#include "tankbattalionkey.h"
#include "tankbattalionspritetype.h"

#pragma GCC diagnostic pop

namespace Qt
{
  struct QImage;
}

namespace ribi {
namespace taba {

class QtGameWidget : public QWidget
{
    Q_OBJECT
public:

  typedef std::map<SpriteType,boost::shared_ptr<QPixmap>> SpriteMap;
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

  SpriteMap CreateSprites() const;
  boost::shared_ptr<QPixmap> GetPixmap(const SpriteType& s) const;

private slots:
  void OnTimer();

};

} //~namespace taba
} //~namespace ribi

#endif // QTGAMEWIDGET_H
