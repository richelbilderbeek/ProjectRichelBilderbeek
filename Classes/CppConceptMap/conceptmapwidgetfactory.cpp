#include "conceptmapwidgetfactory.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmapfactory.h"

const std::vector<boost::shared_ptr<ribi::cmap::Widget>>
  ribi::cmap::WidgetFactory::GetAllTests() noexcept
{
  std::vector<boost::shared_ptr<Widget>> v;
  for (const boost::shared_ptr<ConceptMap> m: ConceptMapFactory::GetAllTests())
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
