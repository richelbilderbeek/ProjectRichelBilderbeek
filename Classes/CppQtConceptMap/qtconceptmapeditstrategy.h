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
