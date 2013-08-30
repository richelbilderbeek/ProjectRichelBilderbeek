#ifndef PONGMAINDIALOG_H
#define PONGMAINDIALOG_H

#include <cassert>
#include <cmath>
#include <QDialog>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPen>

///PongBackground is a resizable background used in Pong
struct PongBackground : public QGraphicsPixmapItem
{
  PongBackground(
    QGraphicsItem * parent = 0)
    : QGraphicsPixmapItem(parent)
  {

  }
  void SetGeometry(const int width, const int height)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        const int gray = (x + y) % 256;
        i.setPixel(QPoint(x,y),QColor(gray,gray,gray).rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
  }
};

///PongPlayer is a player
struct PongPlayer : public QGraphicsRectItem
{
  PongPlayer(
    QGraphicsItem * parent = 0)
    : QGraphicsRectItem(parent),
      m_dy(0.0)
  {
    this->setBrush(QBrush(QColor(0,0,0)));
    this->setPen(QPen(QColor(128,128,128)));
  }
  void SetArenaGeometry(const int maxx, const int maxy)
  {
    m_maxx = maxx;
    m_maxy = maxy;
  }
  ///Set the vertical speed of the player
  void SetDy(const double dy) { m_dy = dy; }
  void advance(int)
  {
    //Check the next coordinats
    {
      double new_y = this->y() + m_dy;
      if (new_y<0.0) m_dy = std::abs(m_dy);
      else if (new_y >= m_maxy - this->rect().height()) m_dy = -std::abs(m_dy);
    }
    //Set the nice new coordinats
    this->setY(this->y() + m_dy);
  }
  private:
  double m_dy;
  int m_maxx;
  int m_maxy;
};

///PongBall is the ball used in Pong
struct PongBall : public QGraphicsPixmapItem
{
  PongBall(
    QGraphicsItem * parent = 0,
    const int width = 32,
    const int height = 32)
    : QGraphicsPixmapItem(parent),
      m_dx(1.0), m_dy(1.0), m_maxx(0.0), m_maxy(0.0)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        const int gray = ((8 * x) + (8 * y)) % 256;
        i.setPixel(QPoint(x,y),QColor(gray,gray,gray).rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
  }
  ///Make the ball bounce
  //advance (an inherited method) determines what this sprite must
  //do upon a QGraphicsScene::advance call
  void advance(int)
  {
    //Check the next coordinats
    {
      double new_x = this->x() + m_dx;
      double new_y = this->y() + m_dy;
      if (new_x<0.0) m_dx = std::abs(m_dx);
      else if (new_x >= m_maxx - this->pixmap().width()) m_dx = -std::abs(m_dx);

      if (new_y<0.0) m_dy = std::abs(m_dy);
      else if (new_y >= m_maxy - this->pixmap().height()) m_dy = -std::abs(m_dy);
    }
    //Set the nice new coordinats
    this->setX(this->x() + m_dx);
    this->setY(this->y() + m_dy);
  }
  void SetArenaRect(const int width, const int height)
  {
    m_maxx = width;
    m_maxy = height;
  }
  private:
  double m_dx;
  double m_dy;
  double m_maxx;
  double m_maxy;
};


namespace Ui {
class PongMainDialog;
}

class PongMainDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit PongMainDialog(QWidget *parent = 0);
  ~PongMainDialog();
    
private:
  Ui::PongMainDialog *ui;

  PongBackground * const m_background;
  PongBall * const m_ball;
  std::vector<PongPlayer*> m_players;
protected:
  void keyPressEvent(QKeyEvent *);
  void resizeEvent(QResizeEvent *);

};

#endif // PONGMAINDIALOG_H
