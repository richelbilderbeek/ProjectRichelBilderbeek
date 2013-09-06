#ifndef QTPVDBDISPLAY_H
#define QTPVDBDISPLAY_H

#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
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
