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
#ifndef QTCONCEPTMAPFWD_H
#define QTCONCEPTMAPFWD_H

#include "conceptmapfwd.h"

namespace ribi {

struct QtQuadBezierArrowItem;
struct QtRoundedRectItemDialog;
struct QtRoundedEditRectItem;
struct QtRoundedEditRectItemDialog;
struct QtKeyboardFriendlyGraphicsView;

namespace cmap {

struct QtConceptDialog;
struct QtConceptMap;
struct QtConceptMapElement;
struct QtConceptMapWidget;
struct QtDisplayConceptMap;
struct QtDisplayStrategy;
struct QtEdge;
struct QtEdge2;
struct QtEdgeDialog;
//struct QtEditStrategy;
struct QtExampleDialog;
struct QtExamplesDialog;
struct QtExamplesItem;
//struct QtItemDisplayStrategy;
struct QtItemHighlighter;
struct QtNewArrow;
struct QtNode;
struct QtNodeDialog;   //QtDialog showing a Node
struct QtQtEdgeDialog; //QtDialog showing a QtEdge
struct QtQtNodeDialog; //QtDialog showing a QtNode
struct QtRateConceptMap;
struct QtRateStrategy;
struct QtTool;

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPFWD_H
