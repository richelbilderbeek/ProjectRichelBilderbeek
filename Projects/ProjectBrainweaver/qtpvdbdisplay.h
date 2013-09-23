#ifndef QTPVDBDISPLAY_H
#define QTPVDBDISPLAY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

struct QTableWidget;

namespace ribi {

namespace pvdb {

///Functions for printing
struct QtDisplay
{

  static void DisplayRatedConcepts(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayExamples(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayValues(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBDISPLAY_H
