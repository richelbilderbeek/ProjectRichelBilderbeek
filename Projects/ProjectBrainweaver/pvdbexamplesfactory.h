#ifndef PVDBEXAMPLESFACTORY_H
#define PVDBEXAMPLESFACTORY_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

struct ExamplesFactory
{
  ///Constructor like
  static const boost::shared_ptr<ribi::pvdb::Examples> Create();

  ///Copy-constructor like
  static const boost::shared_ptr<ribi::pvdb::Examples> Create(
    const boost::shared_ptr<const pvdb::Examples>& examples);

  static const boost::shared_ptr<ribi::pvdb::Examples> Create(
    const std::vector<boost::shared_ptr<pvdb::Example> >& v);

  static const boost::shared_ptr<ribi::pvdb::Examples> Create(
    const std::vector<boost::shared_ptr<const pvdb::Example> >& v);

  static const boost::shared_ptr<ribi::pvdb::Examples> Create(
    const std::vector<std::pair<std::string,Competency> >& v);

  static const std::vector<boost::shared_ptr<ribi::pvdb::Examples> > GetTests();
};

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBEXAMPLESFACTORY_H
