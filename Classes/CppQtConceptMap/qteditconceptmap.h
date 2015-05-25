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
#ifndef QTCONCEPTMAPEDITCONCEPTMAP_H
#define QTCONCEPTMAPEDITCONCEPTMAP_H

#include "qtconceptmapfwd.h"
#include "qtconceptmap.h"

namespace ribi {
namespace cmap {

///Editable QtConceptMap with a low-level interface
///Use QtEditConceptMapWidget for a Command driven interface
struct QtEditConceptMap : public QtConceptMap
{
  typedef QtEditConceptMap This_t;

  ///Mode is temporary: I want to seperate QtEditConceptMap
  ///into a class that only does the display (this class)
  ///and a class that handles the user interaction (QtConceptMapWidget).
  ///To not break the current build, I switch on Mode
  enum class Mode { classic, simple };

  QtEditConceptMap(
    const boost::shared_ptr<ConceptMap> concept_map = boost::shared_ptr<ConceptMap>(),
    const Mode mode = Mode::classic,
    QWidget* parent = 0);
  ~QtEditConceptMap() noexcept;
  QtEditConceptMap(const QtEditConceptMap& other) = delete;
  QtEditConceptMap& operator=(const QtEditConceptMap& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMap> CreateNewDerived() const;
  #endif

  #ifndef NDEBUG
  ///Do something random
  void DoRandomStuff();
  #endif

  ///Signal emitted when a concept map item requests to be edited
  boost::signals2::signal<void(QtConceptMapElement*)> m_signal_conceptmapitem_requests_edit;

protected:

  void keyPressEvent(QKeyEvent* event) noexcept;
  void mouseMoveEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:

  ///The arrow used to create a new arrow
  ///Is nullptr when not active
  QtNewArrow * m_arrow;

  ///The item highlighter, used when creating a new relation
  QtItemHighlighter * const m_highlighter;

  ///The current mode, to be removed later (see definition of Mode)
  const Mode m_mode;

  ///The item showing the tools
  QtTool * m_tools;

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  QtEdge * AddEdge(const boost::shared_ptr<Edge> edge);

  ///Add a new edge
  QtEdge * AddEdge(QtNode * const from, QtNode* const to);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtNode * AddNode(const boost::shared_ptr<Node> node);

  ///Remove all Qt and non-Qt items
  void CleanMe();

  ///Obtain the read-and-write Qt node items
  ///The read-only Qt node items is already supplied by QtConceptMap
  std::vector<QtNode *> GetQtNodes();

  ///Called when an item wants to be edited
  void OnEdgeKeyDownPressed(QtEdge * const item, const int key);

  ///Called when an item wants to be edited
  void OnNodeKeyDownPressed(QtNode* const item, const int key);

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called whenever the tools item is clicked
  void OnToolsClicked();

  ///Test this class
  static void Test() noexcept;
};

} //~namespace cmap

} //~namespace ribi


#endif // QTCONCEPTMAPEDITCONCEPTMAP_H
