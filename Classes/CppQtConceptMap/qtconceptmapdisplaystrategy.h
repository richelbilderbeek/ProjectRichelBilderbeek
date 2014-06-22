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
#ifndef QTCONCEPTMAPDISPLAYSTRATEGY_H
#define QTCONCEPTMAPDISPLAYSTRATEGY_H

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

///QtDisplayStrategy display a Concept
struct QtDisplayStrategy : public QtItemDisplayStrategy
{
  ~QtDisplayStrategy() noexcept;

  //concept can be modified (as it is not const), but I can promise I will try to prevent this from happening
  explicit QtDisplayStrategy(const boost::shared_ptr<Concept>& concept);

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

#endif // USE_ITEMDISPLAYSTRATEGY_20140622


#endif // QTCONCEPTMAPDISPLAYSTRATEGY_H
