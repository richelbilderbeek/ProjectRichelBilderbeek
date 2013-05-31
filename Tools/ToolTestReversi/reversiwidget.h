#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------------------------
struct Reversi;
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#endif // REVERSIWIDGET_H
