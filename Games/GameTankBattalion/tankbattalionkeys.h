#ifndef TANKBATTALIONKEYS_H
#define TANKBATTALIONKEYS_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/bimap.hpp>

#include "tankbattalionkey.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace taba {

struct Keys
{
  Keys() noexcept;

  std::vector<Key> GetAll() const noexcept;

  Key GetOpposite(const Key k) const noexcept;
  bool IsMovement(const Key k) const noexcept;
  bool IsOpposite(const Key a, const Key b) const noexcept;

  Key ToKey(const std::string& s) const noexcept;
  std::string ToStr(const Key k) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:
  static boost::bimap<Key,std::string> m_map;
  static boost::bimap<Key,std::string> CreateMap() noexcept;

};

} //~namespace taba
} //~namespace ribi


#endif // TANKBATTALIONKEYS_H
