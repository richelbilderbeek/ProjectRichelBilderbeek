#ifndef QTPVDBEDITCONCEPTITEM_H
#define QTPVDBEDITCONCEPTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtconceptmapitem.h"
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Displays a Concept that might be edited
struct QtPvdbEditConceptItem : public QtConceptMapItem
{
  //concept will be modified
  explicit QtPvdbEditConceptItem(const boost::shared_ptr<ribi::cmap::Concept> concept);
  ~QtPvdbEditConceptItem() noexcept;
  ///Signalled when the user wants to edit
  boost::signals2::signal<void (QtConceptMapItem *)> m_signal_request_edit;

protected:
  void keyPressEvent(QKeyEvent *event) noexcept;

private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///A Edit ConceptItem does not change its brushes and pens
  void UpdateBrushesAndPens() noexcept {}
};

} //~namespace cmap
} //~namespace ribi

#endif // QTPVDBEDITCONCEPTITEM_H
