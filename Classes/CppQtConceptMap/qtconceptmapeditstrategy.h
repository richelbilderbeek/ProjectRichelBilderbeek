#ifndef QTCONCEPTMAPEDITSTRATEGY_H
#define QTCONCEPTMAPEDITSTRATEGY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtitemdisplaystrategy.h"
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Displays a Concept that might be edited
///QtEditStrategy -> QtEditStrategy
struct QtEditStrategy : public QtItemDisplayStrategy
{
  //concept will be modified
  explicit QtEditStrategy(const boost::shared_ptr<Concept> concept);
  ~QtEditStrategy() noexcept;
  ///Signalled when the user wants to edit
  boost::signals2::signal<void (QtItemDisplayStrategy *)> m_signal_request_edit;

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

#endif // QTCONCEPTMAPEDITSTRATEGY_H
