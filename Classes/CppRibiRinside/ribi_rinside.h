#ifndef RIBI_INSIDE_R_H
#define RIBI_INSIDE_R_H

struct RInside;

namespace ribi {

//Singleton for an InsideR instance
struct Rinside
{
  Rinside();
  RInside& Get();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


} //~namespace ribi

#endif // RIBI_INSIDE_R_H
