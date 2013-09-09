//---------------------------------------------------------------------------

#ifndef UnitSpriteH
#define UnitSpriteH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
namespace Extctrls { struct TImage; }
namespace Graphics { struct TCanvas; }
namespace Types { struct TRect; }
struct CollisionBehaviour;
struct ComplexMovePattern;
struct MovementPattern;
struct Player;
//---------------------------------------------------------------------------
struct Sprite
{
  Sprite(Extctrls::TImage* const image);
  virtual ~Sprite() {}

  virtual void Draw(Graphics::TCanvas * const canvas) const = 0;
  virtual void Move() = 0;
  virtual void Restart() = 0;
  virtual const double GetX() const = 0;
  virtual const double GetY() const = 0;
  const bool DoesCollide(const Player& p) const;
  void OnCollide(Player& p);
  const bool InSprite(const int x, const int y) const;
  const Types::TRect GetRect() const;
  Extctrls::TImage * m_image; //TImage to be drawn
  const int m_width;
  const int m_height;
  boost::shared_ptr<CollisionBehaviour> m_collision_behaviour;
};
//---------------------------------------------------------------------------
struct MovingSprite : public Sprite
{
  MovingSprite(const int x, const int y,Extctrls::TImage* const image)
  : Sprite(image),
    m_x(static_cast<double>(x)),
    m_y(static_cast<double>(y))
  {

  }
  virtual ~MovingSprite() {}

  void Restart();
  const double GetX() const { return m_x; }
  const double GetY() const { return m_y; }
  double m_x;
  double m_y;
  void Draw(Graphics::TCanvas * const canvas) const;
  void Move();
  boost::shared_ptr<ComplexMovePattern> m_movement_pattern;
};
//---------------------------------------------------------------------------
struct NonMovingSprite : public Sprite
{
  NonMovingSprite(const int x, const int y,Extctrls::TImage* const image)
    : Sprite(image),
      m_x(x),
      m_y(y)
  {

  }
  ~NonMovingSprite() {}
  void Restart() {}
  const double GetX() const { return static_cast<double>(m_x); }
  const double GetY() const { return static_cast<double>(m_y); }
  const int m_x;
  const int m_y;
  void Draw(Graphics::TCanvas * const canvas) const;
  void Move() {}
};
//---------------------------------------------------------------------------
struct RockSprite : public NonMovingSprite
{
  RockSprite(const int x, const int y);
};
//---------------------------------------------------------------------------
struct RollingBallSprite : public MovingSprite
{
  RollingBallSprite(const int x, const int y, const double dx);
  const double m_dx;
};
//---------------------------------------------------------------------------

//const boost::shared_ptr<Sprite> CreateRollingBallSprite(const double speed);


#endif
