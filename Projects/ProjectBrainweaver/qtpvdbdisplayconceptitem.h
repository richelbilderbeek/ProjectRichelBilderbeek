#ifndef QTPVDBDISPLAYCONCEPTITEM_H
#define QTPVDBDISPLAYCONCEPTITEM_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///QtPvdbDisplayConcept display a Concept
struct QtPvdbDisplayConceptItem : public QtPvdbConceptItem
{
  ~QtPvdbDisplayConceptItem();

  //concept can be modified (as it is not const), but I can promise I will try to prevent this from happening
  explicit QtPvdbDisplayConceptItem(const boost::shared_ptr<ribi::pvdb::Concept>& concept);

protected:
  virtual void keyPressEvent(QKeyEvent *) {} //Do not respond to key presses

private:
  static void Test() {}

  void UpdateBrushesAndPens();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBDISPLAYCONCEPTITEM_H
