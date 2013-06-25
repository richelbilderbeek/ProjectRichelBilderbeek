#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptitem.h"

#include <string>
#include <boost/lexical_cast.hpp>

#include <QCursor>
#include <QFont>
#include <QKeyEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>

#include "pvdbconcept.h"

#include "fuzzy_equal_to.h"
#include "pvdbedge.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "qtpvdbexamplesitem.h"
#include "trace.h"


QtPvdbConceptItem::QtPvdbConceptItem(
  const boost::shared_ptr<pvdb::Concept>& concept)
  : m_concept(concept),
    m_indicator_brush(QBrush(QColor(0,0,0,0))),
    m_indicator_pen(QPen(QColor(0,0,0)))
{
  assert(m_concept);
  assert(m_concept->GetExamples());

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  this->SetPadding(QtRoundedTextRectItem::Padding(1.0,6.0,1.0,2.0));

  //?FIX 2013-01-06 22:47
  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&QtPvdbConceptItem::OnConceptNameChanged,this)); //Obligatory

  //FIX? 2013-06-25
  //this->SetText("DUMMY TEXT");
  //assert(this->GetText() != m_concept->GetName()
  //  && "The text must be set, to get a resize");
  this->SetText(m_concept->GetName());
}

const boost::shared_ptr<const pvdb::Concept> QtPvdbConceptItem::GetConcept() const
{
  boost::shared_ptr<const pvdb::Concept> p(m_concept);
  assert(p);
  return p;
}

void QtPvdbConceptItem::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void QtPvdbConceptItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  Base::mouseMoveEvent(event);
  //this->m_signal_item_has_updated(); //2013-06-25
  m_signal_request_scene_update();
}

void QtPvdbConceptItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
  Base::mousePressEvent(event);
  //this->m_signal_item_has_updated(); //2013-06-25
  m_signal_request_scene_update();
}

// ?FIX 2013-01-06 22:47
void QtPvdbConceptItem::OnConceptNameChanged()
{
  assert(this);
  assert(m_concept);
  assert(m_concept->GetExamples());
  this->SetText( this->m_concept->GetName() );
  //m_signal_item_changed(this); //Called by SetText
}

void QtPvdbConceptItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  assert(m_concept);
  assert(m_concept->GetExamples());
  //assert(!this->hasFocus()); //Can have focus when used as stand-alone
  //assert(!this->isSelected()); //Can have focus when used as stand-alone
  this->UpdateBrushesAndPens();

  Base::paint(painter,option,widget);

  if (!m_concept->GetExamples()->Get().empty())
  {
    painter->setBrush(m_indicator_brush);
    painter->setPen(m_indicator_pen);
    //Draw indicator that a concept has examples in it
    painter->drawRect(
      rect().right() - 5.0,
      rect().top() + 3.0,
      3.0,
      3.0
      );
  }
}

void QtPvdbConceptItem::SetIndicatorBrush(const QBrush& brush)
{
  if (m_indicator_brush != brush)
  {
    m_indicator_brush = brush;
    this->update();
  }
}

void QtPvdbConceptItem::SetIndicatorPen(const QPen& pen)
{
  if (m_indicator_pen != pen)
  {
    m_indicator_pen = pen;
    this->update();
  }
}

void QtPvdbConceptItem::SetMainBrush(const QBrush& any_brush)
{

  if (this->brush() != any_brush)
  {
    this->setBrush(any_brush);
    this->update();
  }
  assert(this->brush() == any_brush);
}

QPainterPath QtPvdbConceptItem::shape() const
{
  const int click_easy_width = 5;
  QPainterPath path;
  QPainterPathStroker stroker;

  path.addRect(this->boundingRect());
  stroker.setWidth(click_easy_width);
  return stroker.createStroke(path);
}
