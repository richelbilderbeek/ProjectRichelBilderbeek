//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#ifndef CONCEPTMAPFWD_H
#define CONCEPTMAPFWD_H

//struct QRegExp;
//struct QTimer;

namespace ribi {
namespace cmap {

struct CenterNode;
struct CenterNodeFactory;
//struct Cluster; //Remove for now, must be added at ProjectBrainweaver later
struct Command;
struct CommandAddSelectedRandom;
struct CommandDeleteFocusNode;
struct Concept;
struct ConceptFactory;
struct ConceptMap;
struct ConceptMapFactory;
struct Edge;
struct EdgeFactory;
struct Element;
struct Example;
struct Examples;
//struct File;
struct Node;
struct Widget;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPFWD_H
