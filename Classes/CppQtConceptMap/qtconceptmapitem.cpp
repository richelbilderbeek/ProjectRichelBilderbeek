#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapitem.h"

#include <QCursor>

#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "qtconceptitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

void ribi::cmap::QtConceptMapItem::OnConceptRequestsEdit()
{
  assert(this);
  assert(this->GetConcept());
  assert(this->GetConcept()->GetExamples());
  this->setAcceptHoverEvents(true);
  m_signal_conceptmapitem_requests_edit(this);
}

void ribi::cmap::QtConceptMapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}
