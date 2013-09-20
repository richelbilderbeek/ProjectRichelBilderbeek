#ifndef QTPVDBDISPLAYCONCEPTITEM_H
#define QTPVDBDISPLAYCONCEPTITEM_H

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

///QtPvdbDisplayConcept display a Concept
struct QtPvdbDisplayConceptItem : public QtPvdbConceptItem
{
  ~QtPvdbDisplayConceptItem() noexcept;

  //concept can be modified (as it is not const), but I can promise I will try to prevent this from happening
  explicit QtPvdbDisplayConceptItem(const boost::shared_ptr<ribi::pvdb::Concept>& concept);

protected:
  virtual void keyPressEvent(QKeyEvent *) noexcept {} //Do not respond to key presses

private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void UpdateBrushesAndPens() noexcept;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBDISPLAYCONCEPTITEM_H
