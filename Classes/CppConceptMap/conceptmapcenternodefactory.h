#ifndef CONCEPTMAPCENTERNODEFACTORY_H
#define CONCEPTMAPCENTERNODEFACTORY_H

#include <string>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapfwd.h"
#include "conceptmapcompetency.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct CenterNodeFactory
{
  static const boost::shared_ptr<cmap::CenterNode> Create(
    const boost::shared_ptr<ribi::cmap::Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<cmap::CenterNode> Create(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0);

  #ifndef NDEBUG
  static const boost::shared_ptr<cmap::CenterNode> DeepCopy(
    const boost::shared_ptr<const cmap::CenterNode>& node);
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCENTERNODEFACTORY_H
