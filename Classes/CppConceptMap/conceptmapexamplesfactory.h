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
  ExamplesFactory() {}

  ///Constructor like
  static const boost::shared_ptr<Examples> Create();

  ///Copy-constructor like
  static const boost::shared_ptr<Examples> Create(
    const boost::shared_ptr<const cmap::Examples>& examples);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<boost::shared_ptr<cmap::Example> >& v);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<boost::shared_ptr<const cmap::Example> >& v);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<std::pair<std::string,Competency> >& v);

  ///Create an Examples from XML
  const boost::shared_ptr<Examples> FromXml(const std::string& s) const;

  int GetNumberOfTests() const noexcept { return static_cast<int>(GetTests().size()); }
  const boost::shared_ptr<Examples> GetTest(const int i) const noexcept;
  const std::vector<boost::shared_ptr<Examples>> GetTests() const noexcept;
};

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPEXAMPLESFACTORY_H
