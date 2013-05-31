#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapratewidget.h"

#include "pvdbconceptmapfactory.h"
#include "trace.h"

void QtPvdbConceptMapRateWidget::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test base class
  {
    boost::shared_ptr<QtPvdbConceptMapWidget> widget(new This_t);
    QtPvdbConceptMapWidget::Test(widget);
  }
  {
    //QtPvdbConceptMapRateWidget w;
    //const int sz = pvdb::ConceptMapFactory::GetAllTests().size();
    //w.ReadFromConceptMap(
  }
  TRACE("QtPvdbConceptMapRateWidget::Test finished successfully");
}


