#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct Reversi;

class ReversiWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ReversiWidget(QWidget *parent = 0);

signals:

private:
  boost::shared_ptr<Reversi> m_reversi;
  QColor m_color_player1;
  QColor m_color_player2;
  QColor m_color_square_even;
  QColor m_color_square_odd;
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);

};

} //~namespace ribi

#endif // REVERSIWIDGET_H
