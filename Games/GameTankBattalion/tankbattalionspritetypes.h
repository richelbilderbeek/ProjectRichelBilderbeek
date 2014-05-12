#ifndef TANKBATTALIONSPRITETYPES_H
#define TANKBATTALIONSPRITETYPES_H

namespace ribi {
namespace taba {

struct SpriteTypes
{
  SpriteTypes();

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif //~ifndef NDEBUG

};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONSPRITETYPES_H
