#ifndef CONCEPTMAPWIDGETFACTORY_H
#define CONCEPTMAPWIDGETFACTORY_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapfwd.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Widget does the Command-driven communication with ConceptMap
struct WidgetFactory
{
  ///Get all the testing concept maps as a widget in one vector
  static const std::vector<boost::shared_ptr<Widget> > GetAllTests() noexcept;

};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPWIDGETFACTORY_H
