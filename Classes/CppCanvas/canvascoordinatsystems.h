#ifndef RIBI_CANVASCOORDINATSYSTEMS_H
#define RIBI_CANVASCOORDINATSYSTEMS_H

#include <string>
#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>

#include "canvascoordinatsystem.h"
#pragma GCC diagnostic pop

namespace ribi {

struct CanvasCoordinatSystems
{
  static std::vector<CanvasCoordinatSystem> GetAll() noexcept;
  static std::string ToStr(const CanvasCoordinatSystem s) noexcept;
  static CanvasCoordinatSystem ToType(const std::string& s);

  private:
  static boost::bimap<CanvasCoordinatSystem,std::string> m_map;
  static boost::bimap<CanvasCoordinatSystem,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CANVASCOORDINATSYSTEMS_H
