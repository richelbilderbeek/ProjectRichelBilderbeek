#ifndef PVDBFILEFACTORY_H
#define PVDBFILEFACTORY_H

#include <boost/shared_ptr.hpp>

namespace pvdb {

struct File;

///Factory of pvdb::File
struct FileFactory
{
  static const boost::shared_ptr<pvdb::File> Create();

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<pvdb::File> DeepCopy(const boost::shared_ptr<const pvdb::File>& file);
  #endif

  static const std::vector<boost::shared_ptr<pvdb::File> > GetTests();
};

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfile.h"
#endif

#endif // PVDBFILEFACTORY_H
