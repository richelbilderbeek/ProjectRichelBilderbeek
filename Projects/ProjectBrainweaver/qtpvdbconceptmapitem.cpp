#include "qtpvdbconceptmapitem.h"

#include <QCursor>

#include "pvdbconcept.h"
#include "pvdbexamples.h"
#include "qtpvdbconceptitem.h"
#include "trace.h"

void ribi::pvdb::QtPvdbConceptMapItem::OnConceptRequestsEdit()
{
  assert(this);
  assert(this->GetConcept());
  assert(this->GetConcept()->GetExamples());
  this->setAcceptHoverEvents(true);
  m_signal_conceptmapitem_requests_edit(this);
}

void ribi::pvdb::QtPvdbConceptMapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}
