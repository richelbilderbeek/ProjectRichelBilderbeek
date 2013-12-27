#ifndef QTCONCEPTMAPDISPLAYSTRATEGY_H
#define QTCONCEPTMAPDISPLAYSTRATEGY_H

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

///QtDisplayStrategy display a Concept
struct QtDisplayStrategy : public QtItemDisplayStrategy
{
  ~QtDisplayStrategy() noexcept;

  //concept can be modified (as it is not const), but I can promise I will try to prevent this from happening
  explicit QtDisplayStrategy(const boost::shared_ptr<ribi::cmap::Concept>& concept);

protected:
  virtual void keyPressEvent(QKeyEvent *) noexcept {} //Do not respond to key presses

private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void UpdateBrushesAndPens() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPDISPLAYSTRATEGY_H
