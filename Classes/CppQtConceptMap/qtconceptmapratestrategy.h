//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPRATESTRATEGY_H
#define QTCONCEPTMAPRATESTRATEGY_H

#ifdef USE_ITEMDISPLAYSTRATEGY_20140622

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
  explicit QtRateStrategy(const boost::shared_ptr<Concept>& concept);

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

#endif // USE_ITEMDISPLAYSTRATEGY_20140622

#endif // QTCONCEPTMAPRATESTRATEGY_H
