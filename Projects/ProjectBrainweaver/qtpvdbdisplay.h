#ifndef QTPVDBDISPLAY_H
#define QTPVDBDISPLAY_H

#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
struct QTableWidget;
#else

#endif

namespace pvdb {

///Functions for printing
struct QtDisplay
{

  static void DisplayRatedConcepts(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayExamples(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayValues(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);

};

} //~namespace pvdb

#endif // QTPVDBDISPLAY_H
