#include <cassert>

#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/math/constants/constants.hpp>

#include <QApplication>
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#pragma GCC diagnostic pop

BOOST_STATIC_ASSERT(sizeof(qreal)==sizeof(double)
  && "Assume use of double is equivalent of qreal");

///Obtain the angle in radians between two deltas
///12 o'clock is 0.0 * pi
/// 3 o'clock is 0.5 * pi
/// 6 o'clock is 1.0 * pi
/// 9 o'clock is 1.5 * pi
//From www.richelbilderbeek.nl/CppGetAngle.htm
double GetAngle(const double dx, const double dy)
{
  const double pi = boost::math::constants::pi<double>();
  return pi - (std::atan2(dx,dy));
}

//From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
void DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2)
{
  const double pi = boost::math::constants::pi<double>();
  //The length of the impulse of player 1 (assumes both players have equal mass!)
  const double A = speed1;
  //The length of the impulse of player 2 (assumes both players have equal mass!)
  const double E = speed2;
  //The angles between the two globes
  const double c = angleCollision;
  //The angle between c and the impulse direction of player 1
  const double a = c - angle1;
  //The angle between c and the impulse direction of player 2
  const double b = c + pi - angle2;

  //Seperate the impulses to their impulses paralel and othoganal the angle of collision
  //The length of the impulse of player 1 parallel to the collision
  const double B = A * std::cos(a);
  //The length of the impulse of player 1 orthogonal to the collision
  const double C = A * std::sin(a);
  //The length of the impulse of player 2 parallel to the collision
  const double F = E * std::cos(b);
  //The length of the impulse of player 2 orthogonal to the collision
  const double G = E * std::sin(b);

  //Seperate the impulses in X and Y directions
  const double BdX = B *  std::sin(c + (0.0 * pi));
  const double BdY = B * -std::cos(c + (0.0 * pi));
  const double CdX = C *  std::sin(c + (1.5 * pi));
  const double CdY = C * -std::cos(c + (1.5 * pi));
  const double FdX = F *  std::sin(c + (1.0 * pi));
  const double FdY = F * -std::cos(c + (1.0 * pi));
  const double GdX = G *  std::sin(c + (0.5 * pi));
  const double GdY = G * -std::cos(c + (0.5 * pi));

  //The resulting impulses
  //The resulting impulse of player 1 in the X direction
  const double DdX = CdX + FdX;
  //The resulting impulse of player 1 in the Y direction
  const double DdY = CdY + FdY;
  //The resulting impulse of player 2 in the X direction
  const double HdX = BdX + GdX;
  //The resulting impulse of player 2 in the Y direction
  const double HdY = BdY + GdY;

  //Write the final results
  angle1 = GetAngle(DdX, DdY);
  angle2 = GetAngle(HdX, HdY);
  speed1 = std::sqrt( (DdX * DdX) + (DdY * DdY) ); //Pythagoras
  speed2 = std::sqrt( (HdX * HdX) + (HdY * HdY) ); //Pythagoras
}

//From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}

struct ChangingBackground : public QGraphicsPixmapItem
{
  ChangingBackground(const int width, const int height)
    : z(0)
  {
    QPixmap m(width,height);
    this->setPixmap(m);
  }
  void advance(int)
  {
    QImage i = this->pixmap().toImage();
    const int width = i.width();
    const int height = i.height();
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        QPoint pos(x,y);
        QColor c((x+z)%256,(y+z)%256,(x+y+z)%256);
        i.setPixel(pos,c.rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
    ++z;
  }
  private:
  int z;
};

struct SirSprite : public QGraphicsPixmapItem
{
  enum State { susceptible, infected, resistant };
  SirSprite(const int width, const int height, const bool is_infected = false)
    : angle(GetRandomUniform() * 2.0 * boost::math::constants::pi<double>()), //Random direction
      speed(5.0),
      state(is_infected ? infected : susceptible),
      maxx(0),
      maxy(0)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    this->setPixmap(this->pixmap().fromImage(i));
    setState(is_infected ? infected : susceptible);
  }
  void advance(int phase)
  {
    if (phase == 0)
    {
      //Bounce against others
      QList<QGraphicsItem*> others = this->collidingItems();
      const int n_others = others.size();
      for (int i=0; i!=n_others; ++i)
      {
        SirSprite * const other = dynamic_cast<SirSprite*>(others[i]);
        if (!other) continue;
        if (other == this) continue;
        //Ensure checking is only done once per colliding pair
        if (this->zValue() < other->zValue()) continue;
        //Relative between players 1 and 2
        const double dx_between = other->x() - this->x();
        const double dy_between = other->y() - this->y();
        const double angle_between = GetAngle(dx_between,dy_between);
        //For this player
        const double this_dx = std::cos(this->angle) * this->speed;
        const double this_dy = -std::sin(this->angle) * this->speed;
        double this_angle = GetAngle( this_dx, this_dy);
        double this_speed = std::sqrt((this_dy * this_dy) + (this_dx * this_dx));
        //For other player
        const double other_dx = std::cos(other->angle) * other->speed;
        const double other_dy = -std::sin(other->angle) * other->speed;
        double other_angle = GetAngle( other_dx, other_dy);
        double other_speed = std::sqrt((other_dy * other_dy) + (other_dx * other_dx));

        DoPerfectElasticCollision(
          angle_between,
          this_angle,
          this_speed,
          other_angle,
          other_speed);

        this->angle = this_angle;
        this->speed = this_speed;
        other->angle = other_angle;
        other->speed = other_speed;
        //Let them move once
        setX(x() + (std::sin(angle) * speed));
        setY(y() - (std::cos(angle) * speed));
        other->setX(other->x() + (std::sin(other->angle) * other->speed));
        other->setY(other->y() - (std::cos(other->angle) * other->speed));
        //Infection?
        if (this->state == infected && other->state == susceptible)
        {
          other->setState(infected);
        }
        if (other->state == infected && this->state == susceptible)
        {
          this->setState(infected);
        }
      }
    }
    //Bounce against the edges
    else if (phase == 1)
    {
      while (1)
      {
        const double pi = boost::math::constants::pi<double>();
        setX(x() + (std::sin(angle) * speed));
        setY(y() - (std::cos(angle) * speed));
        if (x() < 0.0) { setX(x()+1); angle = (0.0*pi) + ((0.0*pi) - angle); continue; }
        if (y() < 0.0) { setY(y()+1); angle = (0.5*pi) + ((0.5*pi) - angle); continue; }
        if (x() > maxx) { setX(x()-1); angle = (1.0*pi) + ((1.0*pi) - angle); continue; }
        if (y() > maxy) { setY(y()-1); angle = (1.5*pi) + ((1.5*pi) - angle); continue; }
        break;
      }
      //Resistance?
      if (state == infected && timer.elapsed() > 5.0) setState(resistant);
    }
  }
  void setRect(const int width, const int height)
  {
    maxx = static_cast<double>(width - this->pixmap().width() );
    maxy = static_cast<double>(height - this->pixmap().height());
  }
  QColor getStateColor() const
  {
    switch (state)
    {
      case susceptible: return QColor(0,0,255);
      case infected : return QColor(255,0,0);
      case resistant : return QColor(0,255,0);
    }
    assert(!"Should not get here");
    return QColor(0,0,0);
  }
  void setStateColor()
  {
    const int width = this->pixmap().width();
    const int height = this->pixmap().height();
    QImage i(width,height,QImage::Format_ARGB32);
    const QColor transparency_color = QColor(0,0,0,255);
    const QColor state_color = getStateColor();
    const double midx = static_cast<double>(width ) / 2.0;
    const double midy = static_cast<double>(height) / 2.0;
    const double ray = std::min(midx,midy);
    for (int y=0;y!=height;++y)
    {
      const double y_real = static_cast<double>(y);
      const double dy = midy - y_real;
      const double dy2 = dy * dy;
      for (int x=0;x!=width;++x)
      {
        const double x_real = static_cast<double>(x);
        const double dx = midx - x_real;
        const double dx2 = dx * dx;
        const double dist = std::sqrt(dx2 + dy2);
        if (dist < ray)
        {
          i.setPixel(x,y,state_color.rgb());
        }
        else
        {
          i.setPixel(x,y,transparency_color.rgb());
        }
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
    //Add transparancy
    QPixmap pixmap = this->pixmap();
    const QBitmap mask = pixmap.createMaskFromColor(transparency_color);
    pixmap.setMask(mask);
    this->setPixmap(pixmap);
  }
  void setState(const State any_state)
  {
    state = any_state;
    setStateColor();
    timer.restart();
  }
  double angle;
  double speed;
  private:
  State state;
  boost::timer timer;
  double maxx;
  double maxy;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsScene s;
  QGraphicsView v(&s);

  ChangingBackground background(512,512);
  s.addItem(&background);

  std::vector<boost::shared_ptr<SirSprite> > sprites;
  //Add multiple sprites
  {
    const int n_sprites = 20;
    const double midx = background.pixmap().width() / 2.0;
    const double midy = background.pixmap().height() / 2.0;
    const double ray = std::min(midx,midy) * 0.8;
    const double pi = boost::math::constants::pi<double>();
    const double d_angle = 2.0 * pi / static_cast<double>(n_sprites);
    double angle = 0.0;
    for (int i=0; i!=n_sprites; ++i)
    {
      boost::shared_ptr<SirSprite> sprite(new SirSprite(32,32, i == 0 ? true : false));
      const double x = midx + (std::sin(angle) * ray) - (sprite->pixmap().width() / 2);
      const double y = midy - (std::cos(angle) * ray) - (sprite->pixmap().height() / 2);
      sprite->setX(x);
      sprite->setY(y);
      sprite->setRect(background.pixmap().width(),background.pixmap().height());
      s.addItem(sprite.get());
      sprites.push_back(sprite);
      angle+=d_angle;
    }
  }
  v.show();

  boost::shared_ptr<QTimer> timer(new QTimer(&s));
  timer->connect(timer.get(), SIGNAL(timeout()), &s, SLOT(advance()));
  timer->start(100);

  return a.exec();
}
