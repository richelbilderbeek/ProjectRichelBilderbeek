#ifndef QTPVDBEDITCONCEPTITEM_H
#define QTPVDBEDITCONCEPTITEM_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///Displays a Concept that might be edited
struct QtPvdbEditConceptItem : public QtPvdbConceptItem
{
  //concept will be modified
  explicit QtPvdbEditConceptItem(const boost::shared_ptr<ribi::pvdb::Concept> concept);
  ~QtPvdbEditConceptItem() noexcept {}
  ///Signalled when the user wants to edit
  boost::signals2::signal<void (QtPvdbConceptItem *)> m_signal_request_edit;

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  #ifndef NDEBUG
  static void Test();
  #endif

  ///A Edit ConceptItem does not change its brushes and pens
  void UpdateBrushesAndPens() {}
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBEDITCONCEPTITEM_H
