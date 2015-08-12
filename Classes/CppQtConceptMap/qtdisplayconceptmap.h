//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
#ifndef QTCONCEPTMAPDISPLAYCONCEPTMAP_H
#define QTCONCEPTMAPDISPLAYCONCEPTMAP_H
/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtconceptmap.h"

#include "conceptmapfwd.h"

#include "conceptmapnode.h"
#include "conceptmapedge.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMap for displayal of a ConceptMap in a read-only fashion
struct QtDisplayConceptMap : public QtConceptMap
{
  typedef QtDisplayConceptMap This_t;

  QtDisplayConceptMap(
    QWidget* parent = 0
  );
  ~QtDisplayConceptMap() noexcept {}

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMap> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff();
  #endif

private:
  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as it has a Concept on it that the user might want to edit
  ///In this derived class, I promise not to change the Edge
  QtEdge * AddEdge(const boost::shared_ptr<Edge> edge);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///In this derived class, I promise not to change the Node
  QtNode * AddNode(const boost::shared_ptr<Node> node);

  void CleanMe();

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  ///QGraphicsItem cannot be const: some items request for an update via-via
  void OnItemRequestUpdateImpl(const QGraphicsItem* const);

  #ifndef NDEBUG
  ///Test this class
  static void Test() {}
  #endif
};

} //~namespace cmap
} //~namespace ribi
*/
#endif // QTCONCEPTMAPDISPLAYCONCEPTMAP_H
