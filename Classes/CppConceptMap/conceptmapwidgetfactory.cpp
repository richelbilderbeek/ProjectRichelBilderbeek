//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#include "conceptmapwidgetfactory.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmapfactory.h"

const std::vector<boost::shared_ptr<ribi::cmap::Widget>>
  ribi::cmap::WidgetFactory::GetAllTests() noexcept
{
  std::vector<boost::shared_ptr<Widget>> v;
  for (const boost::shared_ptr<ConceptMap> m: ConceptMapFactory().GetAllTests())
  {
    assert( (m || !m)
      && "Allow a widget with and without an actual concept map");
    const boost::shared_ptr<Widget> w {
      new Widget(m)
    };
    assert(w);
    assert( (!m && !w->GetConceptMap())                              //both nullptr
       || (   m &&  w->GetConceptMap() && *w->GetConceptMap() == *m) //both point to same
    );
    v.push_back(w);
  }
  return v;
}
