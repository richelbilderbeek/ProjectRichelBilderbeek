#ifndef QTGAMEWIDGET_H
#define QTGAMEWIDGET_H

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
  typedef std::map<TankBattalion::SpriteType,boost::shared_ptr<QImage> > SpriteMap;
  explicit QtGameWidget(QWidget *parent = 0);
protected:
  void paintEvent(QPaintEvent *);
signals:
public slots:
private:
  const SpriteMap CreateSprites() const;
  const boost::shared_ptr<QImage> GetImage(const TankBattalion::SpriteType& s) const;
  const SpriteMap m_sprites;
};

#endif // QTGAMEWIDGET_H
