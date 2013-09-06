#ifndef QTPVDBRATECONCEPT_H
#define QTPVDBRATECONCEPT_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///QtPvdbRateConcept display a Concept that is (1) a node (2) is unmovable (3) has focus on
///the concept AND its examples (4) has different colors depending on the concept being rated
struct QtPvdbRateConceptItem : public QtPvdbConceptItem
{
  //concept will be modified
  explicit QtPvdbRateConceptItem(const boost::shared_ptr<ribi::pvdb::Concept>& concept);

  virtual ~QtPvdbRateConceptItem();

  ///Key was pressed to indicate user wants to rate the concept
  boost::signals2::signal<void(QtPvdbConceptItem*)> m_signal_request_rate_concept;

  ///Key was pressed to indicate user wants to rate the concept
  boost::signals2::signal<void(QtPvdbConceptItem*)> m_signal_request_rate_examples;

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  ///Test this class
  static void Test();

  ///Update the brushes and pens
  void UpdateBrushesAndPens();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBRATECONCEPT_H
