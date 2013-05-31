#ifndef QTPVDBDISPLAYCONCEPTITEM_H
#define QTPVDBDISPLAYCONCEPTITEM_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbnode.h"
#include "pvdbconcept.h"
#endif


///QtPvdbDisplayConcept display a Concept
struct QtPvdbDisplayConceptItem : public QtPvdbConceptItem
{
  //concept can be modified (as it is not const), but I can promise I will try to prevent this from happening
  explicit QtPvdbDisplayConceptItem(const boost::shared_ptr<pvdb::Concept>& concept);

protected:
  virtual void keyPressEvent(QKeyEvent *) {} //Do not respond to key presses

private:
  static void Test() {}

  void UpdateBrushesAndPens();
};

#endif // QTPVDBDISPLAYCONCEPTITEM_H
