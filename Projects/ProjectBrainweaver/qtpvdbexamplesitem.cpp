#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbexamplesitem.h"

#include <QFont>
#include <QPainter>

#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "qtpvdbconceptmapitem.h"
#include "pvdbconcept.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbbrushfactory.h"
#include "trace.h"

ribi::pvdb::QtPvdbExamplesItem::QtPvdbExamplesItem(
  QGraphicsItem* parent)
  : QtRoundedEditRectItem(
      { "..." },
      QtRoundedEditRectItem::Padding(),
      QFont("monospace",9),
      parent
    ),
    m_item(nullptr)
{
  this->setPen(QPen(QColor(255,0,0)));
  this->setBrush(QtPvdbBrushFactory::CreateWhiteGradientBrush());
  this->setFlags(0);
  this->setZValue(2.0);
  this->setVisible(false);
  //this->SetBuddyItem(concept);
}

void ribi::pvdb::QtPvdbExamplesItem::OnItemUpdated()
{
  this->update();
  this->m_signal_request_scene_update();
}

void ribi::pvdb::QtPvdbExamplesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ribi::pvdb::QtPvdbExamplesItem::SetBuddyItem(const QtPvdbConceptMapItem* const item)
{
  if (m_item != item)
  {
    m_item = item;
    if (m_item && !m_item->GetConcept()->GetExamples()->Get().empty())
    {
      m_item->m_signal_item_has_updated.connect(
        boost::bind(
          &ribi::pvdb::QtPvdbExamplesItem::OnItemUpdated,this
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

void ribi::pvdb::QtPvdbExamplesItem::SetExamples(const boost::shared_ptr<const pvdb::Examples>& examples)
{
  const std::vector<boost::shared_ptr<const pvdb::Example> >& v = examples->Get();
  std::vector<std::string> w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const boost::shared_ptr<const pvdb::Example>& p)
    {
      assert(p);
      return p->GetText();
    }
  );
  this->SetText(w);
}
