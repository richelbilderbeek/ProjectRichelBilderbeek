#ifndef QTREVERSIWIDGET_H
#define QTREVERSIWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QWidget>
#include "reversifwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace reversi {

class QtWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

signals:

private:
  boost::shared_ptr<Widget> m_reversi;
  QColor m_color_player1;
  QColor m_color_player2;
  QColor m_color_square_even;
  QColor m_color_square_odd;
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);

};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIWIDGET_H
