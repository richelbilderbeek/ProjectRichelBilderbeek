#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapexamplesitem.h"

#include <QFont>
#include <QPainter>

#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapitem.h"
#include "conceptmapconcept.h"
#include "qtconceptmapitem.h"
#include "conceptmaphelper.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapbrushfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtExamplesItem::QtExamplesItem(
  QGraphicsItem* parent)
  : QtRoundedEditRectItem(
      { "..." },
      QtRoundedEditRectItem::Padding(),
      QFont("monospace",9),
      parent
    ),
    m_signal_request_scene_update{},
    m_item{}
{
  this->setPen(QPen(QColor(255,0,0)));
  this->setBrush(QtBrushFactory::CreateWhiteGradientBrush());
  this->setFlags(0);
  this->setZValue(2.0);
  this->setVisible(false);
  //this->SetBuddyItem(concept);
}

void ribi::cmap::QtExamplesItem::OnItemUpdated()
{
  this->update();
  this->m_signal_request_scene_update();
}

void ribi::cmap::QtExamplesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  this->SetExamples(this->m_item->GetConcept()->GetExamples());

  const QPointF p = m_item->pos();
  const QRectF r = m_item->GetConceptItem()->rect();
  this->setPos(
    p.x() + (0.5 * r.width() ) + 4.0 + (0.5 * this->rect().width() ),
    p.y() + (0.5 * r.height()) + 4.0 + (0.5 * this->rect().height())
  );

  QtRoundedEditRectItem::paint(painter,option,widget);
}

void ribi::cmap::QtExamplesItem::SetBuddyItem(const QtConceptMapItem* const item)
{
  if (m_item != item)
  {
    m_item = item;
    if (m_item && !m_item->GetConcept()->GetExamples()->Get().empty())
    {
      m_item->m_signal_item_has_updated.connect(
        boost::bind(
          &ribi::cmap::QtExamplesItem::OnItemUpdated,this
        )
      );
      this->SetExamples(item->GetConcept()->GetExamples());
      this->setVisible(true);
    }
    m_signal_request_scene_update();
  }
  else
  {
    if (this->isVisible())
    {
      this->setVisible(false);
      m_signal_request_scene_update();
    }
  }
}

void ribi::cmap::QtExamplesItem::SetExamples(const boost::shared_ptr<const cmap::Examples>& examples)
{
  std::vector<std::string> v;
  for (const boost::shared_ptr<const cmap::Example> example: examples->Get())
  {
    const std::string s { example->GetText() };
    const std::size_t wordwrap_length = 40;
    const std::vector<std::string> w { Wordwrap(s,wordwrap_length) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  this->SetText(v);
}
