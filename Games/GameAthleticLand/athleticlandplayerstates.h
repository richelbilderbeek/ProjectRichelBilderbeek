#ifndef ATHLETICLANDPLAYERSTATES_H
#define ATHLETICLANDPLAYERSTATES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

#include "athleticlandplayerstate.h"

namespace ribi {
namespace athl {

struct PlayerStates
{
  PlayerStates();

  static std::vector<PlayerState> GetAll() noexcept;
  static std::string ToStr(const PlayerState s) noexcept;
  static PlayerState ToType(const std::string& s);

  private:
  static boost::bimap<PlayerState,std::string> m_map;
  static boost::bimap<PlayerState,std::string> CreateMap();

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace athl
} //~namespace ribi

#endif // ATHLETICLANDPLAYERSTATES_H
