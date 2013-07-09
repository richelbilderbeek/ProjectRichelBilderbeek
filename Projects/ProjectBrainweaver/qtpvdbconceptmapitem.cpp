#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapitem.h"

#include "pvdbconcept.h"
#include "pvdbexamples.h"
#include "qtpvdbconceptitem.h"
#include "trace.h"

void QtPvdbConceptMapItem::OnConceptRequestsEdit()
{
  assert(this);
  assert(this->GetConcept());
  assert(this->GetConcept()->GetExamples());
  this->setAcceptHoverEvents(true);
  m_signal_conceptmapitem_requests_edit(this);
}

void QtPvdbConceptMapItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
  this->GetConceptItem()->hoverMoveEvent(event);
}
