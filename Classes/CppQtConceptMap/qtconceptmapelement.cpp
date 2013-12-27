#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapelement.h"

#include <QCursor>

#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "qtitemdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

void ribi::cmap::QtConceptMapElement::OnConceptRequestsEdit()
{
  assert(this);
  assert(this->GetConcept());
  assert(this->GetConcept()->GetExamples());
  this->setAcceptHoverEvents(true);
  m_signal_conceptmapitem_requests_edit(this);
}

void ribi::cmap::QtConceptMapElement::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}
