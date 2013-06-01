#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapeditwidget.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "trace.h"

#ifndef NDEBUG
void QtPvdbConceptMapEditWidget::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  //Test cloning
  {
  }
  //Test base class (after having tested cloning of derived class)
  {
    const auto v = pvdb::ConceptMapFactory::GetAllTests();
    for (const boost::shared_ptr<pvdb::ConceptMap> concept_map: v)
    {
      boost::shared_ptr<QtPvdbConceptMapWidget> widget(new This_t(concept_map));
      assert(widget);
      QtPvdbConceptMapWidget::Test(widget);
    }
  }
  TRACE("QtPvdbConceptMapEditWidget::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
