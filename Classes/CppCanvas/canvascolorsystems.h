#ifndef RIBI_CANVASCOLORSYSTEMS_H
#define RIBI_CANVASCOLORSYSTEMS_H

#include <string>
#include <vector>

#include "canvascolorsystem.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct CanvasColorSystems
{
  CanvasColorSystems();

  std::vector<CanvasColorSystem> GetAll() const noexcept;
  std::string ToStr(const CanvasColorSystem s) const noexcept;
  CanvasColorSystem ToType(const std::string& s) const;

  private:
  static boost::bimap<CanvasColorSystem,std::string> m_map;
  static boost::bimap<CanvasColorSystem,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CANVASCOLORSYSTEMS_H
