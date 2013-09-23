#ifndef PVDBCENTERNODEFACTORY_H
#define PVDBCENTERNODEFACTORY_H

#include <string>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#include "pvdbcompetency.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct CenterNodeFactory
{
  static const boost::shared_ptr<pvdb::CenterNode> Create(
    const boost::shared_ptr<ribi::pvdb::Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<pvdb::CenterNode> Create(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0);

  #ifndef NDEBUG
  static const boost::shared_ptr<pvdb::CenterNode> DeepCopy(
    const boost::shared_ptr<const pvdb::CenterNode>& node);
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBCENTERNODEFACTORY_H
