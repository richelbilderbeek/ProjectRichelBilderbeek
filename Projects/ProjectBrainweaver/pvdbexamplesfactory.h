#ifndef PVDBEXAMPLESFACTORY_H
#define PVDBEXAMPLESFACTORY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbexamples.h"
#endif

namespace pvdb {

struct ExamplesFactory
{
  ///Constructor like
  static const boost::shared_ptr<pvdb::Examples> Create();

  ///Copy-constructor like
  static const boost::shared_ptr<pvdb::Examples> Create(
    const boost::shared_ptr<const pvdb::Examples>& examples);

  static const boost::shared_ptr<pvdb::Examples> Create(
    const std::vector<boost::shared_ptr<pvdb::Example> >& v);

  static const boost::shared_ptr<pvdb::Examples> Create(
    const std::vector<boost::shared_ptr<const pvdb::Example> >& v);

  static const boost::shared_ptr<pvdb::Examples> Create(
    const std::vector<std::pair<std::string,Competency> >& v);

  static const std::vector<boost::shared_ptr<pvdb::Examples> > GetTests();
};

} //~namespace pvdb

#endif // PVDBEXAMPLESFACTORY_H
