#ifndef PVDBEXAMPLEFACTORY_H
#define PVDBEXAMPLEFACTORY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"

namespace pvdb {

struct ExampleFactory
{
  ///Create an example from string and enum
  static const boost::shared_ptr<pvdb::Example> Create(const std::string& text, const pvdb::Competency& competency);

  ///Create examples for strings
  ///Note that all pvdb::Competency values are set to uninitialized
  //static const std::vector<boost::shared_ptr<pvdb::Example> > CreateExamples(const std::vector<std::string>& v);

  static const std::vector<boost::shared_ptr<pvdb::Example> > GetTests();

};

} //~namespace pvdb

#endif // PVDBEXAMPLEFACTORY_H
