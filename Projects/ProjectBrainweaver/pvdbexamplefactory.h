#ifndef PVDBEXAMPLEFACTORY_H
#define PVDBEXAMPLEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct ExampleFactory
{
  ///Create an example from string and enum
  static const boost::shared_ptr<pvdb::Example> Create(
    const std::string& text,
    const pvdb::Competency& competency,
    const bool is_complex = true,   //DEFAULT
    const bool is_concrete = true,  //DEFAULT
    const bool is_specific = true); //DEFAULT

  ///Create examples for strings
  ///Note that all pvdb::Competency values are set to uninitialized
  //static const std::vector<boost::shared_ptr<pvdb::Example> > CreateExamples(const std::vector<std::string>& v);

  static const std::vector<boost::shared_ptr<pvdb::Example> > GetTests();

};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBEXAMPLEFACTORY_H
