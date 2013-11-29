#ifndef CONCEPTMAPEXAMPLEFACTORY_H
#define CONCEPTMAPEXAMPLEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ExampleFactory
{
  ///Create an example from string and enum
  static const boost::shared_ptr<cmap::Example> Create(
    const std::string& text,
    const cmap::Competency& competency,
    const bool is_complex = true,   //DEFAULT
    const bool is_concrete = true,  //DEFAULT
    const bool is_specific = true); //DEFAULT

  ///Create examples for strings
  ///Note that all cmap::Competency values are set to uninitialized
  //static const std::vector<boost::shared_ptr<cmap::Example> > CreateExamples(const std::vector<std::string>& v);

  static const std::vector<boost::shared_ptr<cmap::Example> > GetTests();

};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEXAMPLEFACTORY_H
