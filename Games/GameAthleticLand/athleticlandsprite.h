#ifndef UnitSpriteH
#define UnitSpriteH

#include <boost/shared_ptr.hpp>
#include "rectangle.h"
#include "athleticlandfwd.h"

namespace ribi {
namespace athl {
struct Sprite
{
  Sprite(const std::string& filename);
  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  virtual ~Sprite() {}

  virtual void Draw(QPixmap * const canvas) const = 0;
  virtual void Move() = 0;
  virtual void Restart() = 0;
  virtual double GetX() const = 0;
  virtual double GetY() const = 0;
  bool DoesCollide(const Player& p) const;
  void OnCollide(Player& p);
  bool InSprite(const int x, const int y) const;
  const Rect GetRect() const;
  boost::shared_ptr<QPixmap> m_image;
  const int m_width;
  const int m_height;
  boost::shared_ptr<CollisionBehaviour> m_collision_behaviour;
};

struct MovingSprite : public Sprite
{
  MovingSprite(const int x, const int y,const std::string& filename)
  : Sprite(filename),
    m_movement_pattern{},
    m_x(static_cast<double>(x)),
    m_y(static_cast<double>(y))
  {

  }
  virtual ~MovingSprite() {}
  void Restart();
  double GetX() const { return m_x; }
  double GetY() const { return m_y; }
  void Draw(QPixmap * const canvas) const;
  void Move();

  boost::shared_ptr<ComplexMovePattern> m_movement_pattern;
  double m_x;
  double m_y;
};

struct NonMovingSprite : public Sprite
{
  NonMovingSprite(const int x, const int y,const std::string& filename)
    : Sprite(filename),
      m_x(x),
      m_y(y)
  {

  }
  ~NonMovingSprite() {}
  void Restart() {}
  double GetX() const { return static_cast<double>(m_x); }
  double GetY() const { return static_cast<double>(m_y); }
  const int m_x;
  const int m_y;
  void Draw(QPixmap * const canvas) const;
  void Move() {}
};

struct RockSprite : public NonMovingSprite
{
  RockSprite(const int x, const int y);
};

struct RollingBallSprite : public MovingSprite
{
  RollingBallSprite(const int x, const int y, const double dx);
  const double m_dx;
};


//const boost::shared_ptr<Sprite> CreateRollingBallSprite(const double speed);

} //~namespace ribi
} //~namespace athl


#endif
