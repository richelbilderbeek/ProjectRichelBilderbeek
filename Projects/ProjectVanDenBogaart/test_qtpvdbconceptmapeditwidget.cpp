#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapeditwidget.h"

#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "trace.h"

void QtPvdbConceptMapEditWidget::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test cloning
  {
  }
  //Test base class (after having tested cloning of derived class)
  {
    boost::shared_ptr<QtPvdbConceptMapWidget> widget(new This_t);
    assert(widget);
    QtPvdbConceptMapWidget::Test(widget);
  }
  TRACE("QtPvdbConceptMapEditWidget::Test finished successfully");
}

