#ifndef QTPVDBCONCEPT_H
#define QTPVDBCONCEPT_H

#include <string>
#include <vector>

#include <QBrush>
#include <QGraphicsItem>
#include <QPen>

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#include "pvdbnode.h"
#endif

#include "qtroundedtextrectitem.h"

///A QtPvdbConceptItem shows a Concept
///A Concept can be shown in multiple different ways, which is performed by its derived classes.
struct QtPvdbConceptItem : public QtRoundedTextRectItem
{
  typedef QtRoundedTextRectItem Base;

  ///concept cannot be const, the user might edit it (in derived classes for example)
  explicit QtPvdbConceptItem(const boost::shared_ptr<pvdb::Concept>& concept);
  QtPvdbConceptItem(const QtPvdbConceptItem& other) = delete;
  QtPvdbConceptItem& operator=(const QtPvdbConceptItem& other) = delete;
  virtual ~QtPvdbConceptItem() {}

  ///Read the Concept
  const boost::shared_ptr<const pvdb::Concept>  GetConcept() const;
  const boost::shared_ptr<      pvdb::Concept>& GetConcept() { return m_concept; }

  ///Get he brush by which the indicator is filled
  const QBrush& GetIndicatorBrush() const { return m_indicator_brush; }

  ///The pen by which the indicator is drawn
  const QPen& GetIndicatorPen() const { return m_indicator_pen; }

  ///Derived classes respond differently to key presses
  virtual void keyPressEvent(QKeyEvent *event) = 0;

  ///Derived classes draw the concept the same, only with different pens
  ///It is QtPvdbEdgeItem however, that also draws an arrow underneath
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) final;

  ///The brush by which the indicator is filled
  void SetIndicatorBrush(const QBrush& brush);

  ///The pen by which the indicator is filled
  void SetIndicatorPen(const QPen& pen);

  ///Set the main brush
  void SetMainBrush(const QBrush& any_brush);

  ///Convert the QtNode to Node
  //const boost::shared_ptr<pvdb::Node> WriteToNode() const;

protected:
  void setBrush(const QBrush &brush) { QtRoundedRectItem::setBrush(brush); }

  void hoverMoveEvent(QGraphicsSceneHoverEvent *);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  ///Slot whenever the name of the concept is changed
  void OnConceptNameChanged();

  virtual void UpdateBrushesAndPens() = 0;

private:

  ///The concept on the node
  ///m_concept cannot be const: the user might edit it
  const boost::shared_ptr<pvdb::Concept> m_concept;

  ///The brush by which the indicator is filled
  QBrush m_indicator_brush;

  ///The pen by which the indicator is drawn
  QPen m_indicator_pen;

  void setFocus(Qt::FocusReason focusReason) = delete;
};

#endif // QTPVDBCONCEPT_H
