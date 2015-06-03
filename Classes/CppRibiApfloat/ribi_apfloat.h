#ifndef RIBI_APFLOAT_H
#define RIBI_APFLOAT_H

#include <iosfwd>
#include <string>

struct apfloat;

namespace ribi {

///To work with apfloats
struct Apfloat
{
  Apfloat() noexcept;
  double ToDouble(const apfloat& a) const noexcept;
  std::string ToStr(const apfloat& a) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_APFLOAT_H
