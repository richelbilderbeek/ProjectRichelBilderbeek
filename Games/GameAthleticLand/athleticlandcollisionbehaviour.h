#ifndef UnitCollisionBehaviourH
#define UnitCollisionBehaviourH

#include "athleticlandfwd.h"

namespace ribi {
namespace athl {

// CollisionBehaviour determines what will happen to a player
// * LethalCollision: kills player
// * MovePlayerAwayCollision: moves player away from collision zone
struct CollisionBehaviour
{
  virtual void OnCollision(Player& p) = 0;
  virtual ~CollisionBehaviour() {}
};

struct LethalCollision : public CollisionBehaviour
{
  void OnCollision(Player& p);
};

struct MovePlayerAwayCollision : public CollisionBehaviour
{
  MovePlayerAwayCollision(const int x1, const int y1, const int width, const int height);
  void OnCollision(Player& p);

  const int m_x1;
  const int m_x2;
  const int m_y1;
  const int m_y2;
};

bool DoCollide(const Rect& a, const Rect& b);
bool InRect(const int x, const int y, const Rect& r);
void MoveAway(Rect& r1, Rect& r2);

} //~namespace ribi
} //~namespace athl

#endif
