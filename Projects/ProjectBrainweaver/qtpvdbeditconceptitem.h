#ifndef QTPVDBEDITCONCEPTITEM_H
#define QTPVDBEDITCONCEPTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

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
  void keyPressEvent(QKeyEvent *event) noexcept;

private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///A Edit ConceptItem does not change its brushes and pens
  void UpdateBrushesAndPens() noexcept {}
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBEDITCONCEPTITEM_H
