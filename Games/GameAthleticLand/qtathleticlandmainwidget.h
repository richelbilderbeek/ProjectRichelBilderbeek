#ifndef QTATHLETICLANDMAINWIDGET_H
#define QTATHLETICLANDMAINWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QWidget>
#include "athleticlandfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace athl {

struct QtAthleticLandMainWidget : public QWidget
{
  enum class Key { left, right, jump };

  QtAthleticLandMainWidget();
  void OnKeyPress(const Key key);

  private:
  void paintEvent(QPaintEvent *);
  //void resizeEvent(QResizeEvent *);

  const boost::shared_ptr<Player> m_player;
};

} //~namespace athl
} //~namespace ribi

#endif // QTATHLETICLANDMAINWIDGET_H
