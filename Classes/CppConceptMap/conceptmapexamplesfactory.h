#ifndef CONCEPTMAPEXAMPLESFACTORY_H
#define CONCEPTMAPEXAMPLESFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace cmap {

struct ExamplesFactory
{
  ///Constructor like
  static const boost::shared_ptr<ribi::cmap::Examples> Create();

  ///Copy-constructor like
  static const boost::shared_ptr<ribi::cmap::Examples> Create(
    const boost::shared_ptr<const cmap::Examples>& examples);

  static const boost::shared_ptr<ribi::cmap::Examples> Create(
    const std::vector<boost::shared_ptr<cmap::Example> >& v);

  static const boost::shared_ptr<ribi::cmap::Examples> Create(
    const std::vector<boost::shared_ptr<const cmap::Example> >& v);

  static const boost::shared_ptr<ribi::cmap::Examples> Create(
    const std::vector<std::pair<std::string,Competency> >& v);

  static const std::vector<boost::shared_ptr<ribi::cmap::Examples> > GetTests();
};

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPEXAMPLESFACTORY_H
