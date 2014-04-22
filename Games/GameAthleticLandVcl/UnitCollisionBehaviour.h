//---------------------------------------------------------------------------

#ifndef UnitCollisionBehaviourH
#define UnitCollisionBehaviourH
//---------------------------------------------------------------------------
struct Player;
namespace Types { struct TRect; }
//---------------------------------------------------------------------------
// CollisionBehaviour determines what will happen to a player
// * LethalCollision: kills player
// * MovePlayerAwayCollision: moves player away from collision zone
//---------------------------------------------------------------------------
struct CollisionBehaviour
{
  virtual void OnCollision(Player& p) = 0;
  virtual ~CollisionBehaviour() {}
};
//---------------------------------------------------------------------------
struct LethalCollision : public CollisionBehaviour
{
  void OnCollision(Player& p);
};
//---------------------------------------------------------------------------
struct MovePlayerAwayCollision : public CollisionBehaviour
{
  MovePlayerAwayCollision(const int x1, const y1, const int width, const int height);
  void OnCollision(Player& p);
  const int m_x1;
  const int m_y1;
  const int m_y2;
  const int m_x2;
};
//---------------------------------------------------------------------------
const bool DoCollide(const Types::TRect& a, const Types::TRect& b);
const bool InRect(const int x, const int y, const Types::TRect& r);
//void MoveAway(Types::TRect& r1, Types::TRect& r2);

#endif
