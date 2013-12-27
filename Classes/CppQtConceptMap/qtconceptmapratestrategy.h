#ifndef QTCONCEPTMAPRATESTRATEGY_H
#define QTCONCEPTMAPRATESTRATEGY_H

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

///QtRateStrategy display a Concept that is (1) a node (2) is unmovable (3) has focus on
///the concept AND its examples (4) has different colors depending on the concept being rated
struct QtRateStrategy : public QtItemDisplayStrategy
{
  //concept will be modified
  explicit QtRateStrategy(const boost::shared_ptr<ribi::cmap::Concept>& concept);

  virtual ~QtRateStrategy() noexcept;

  ///Key was pressed to indicate user wants to rate the concept
  boost::signals2::signal<void(QtItemDisplayStrategy*)> m_signal_request_rate_concept;

  ///Key was pressed to indicate user wants to rate the concept
  boost::signals2::signal<void(QtItemDisplayStrategy*)> m_signal_request_rate_examples;

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  ///Update the brushes and pens
  void UpdateBrushesAndPens();
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPRATESTRATEGY_H
