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
  CanvasCoordinatSystems();

  std::vector<CanvasCoordinatSystem> GetAll() const noexcept;
  std::string ToStr(const CanvasCoordinatSystem s) const noexcept;
  CanvasCoordinatSystem ToType(const std::string& s) const;

  private:
  static boost::bimap<CanvasCoordinatSystem,std::string> m_map;
  static boost::bimap<CanvasCoordinatSystem,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CANVASCOORDINATSYSTEMS_H
