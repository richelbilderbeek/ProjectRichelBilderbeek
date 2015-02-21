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
#include "tankbattalionfwd.h"
#include "qttankbattalionsprite.h"

#pragma GCC diagnostic pop

namespace Qt
{
  struct QImage;
}

namespace ribi {
namespace taba {

///Draws the Arena
class QtArenaWidget : public QWidget
{
    Q_OBJECT
public:
  explicit QtArenaWidget(QWidget *parent = 0);

  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);
private:
  //const QtSprite m_sprites;
  boost::shared_ptr<GameWidget> m_widget;



private slots:
  void OnTimer();

};

} //~namespace taba
} //~namespace ribi

#endif // QTGAMEWIDGET_H
