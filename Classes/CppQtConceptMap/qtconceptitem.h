#ifndef QTCONCEPTMAPCONCEPT_H
#define QTCONCEPTMAPCONCEPT_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QBrush>
#include <QGraphicsItem>
#include <QPen>

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "qtconceptmapfwd.h"

#include "qtroundededitrectitem.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///A QtItemDisplayStrategy shows a Concept
///A Concept can be shown in multiple different ways, which is performed by its derived classes.
struct QtItemDisplayStrategy : public QtRoundedEditRectItem //NEW 2013-09-15
{
  typedef QtRoundedEditRectItem Base;

  ///concept cannot be const, the user might edit it (in derived classes for example)
  explicit QtItemDisplayStrategy(const boost::shared_ptr<ribi::cmap::Concept>& concept);
  QtItemDisplayStrategy(const QtItemDisplayStrategy& other) = delete;
  QtItemDisplayStrategy& operator=(const QtItemDisplayStrategy& other) = delete;
  virtual ~QtItemDisplayStrategy() noexcept {}

  ///Read the Concept
  const boost::shared_ptr<const ribi::cmap::Concept>  GetConcept() const noexcept;
  const boost::shared_ptr<      ribi::cmap::Concept>& GetConcept() noexcept { return m_concept; }

  ///Get he brush by which the indicator is filled
  const QBrush& GetIndicatorBrush() const noexcept { return m_indicator_brush; }

  ///The pen by which the indicator is drawn
  const QPen& GetIndicatorPen() const noexcept { return m_indicator_pen; }

  ///Get the (un-word-wrapped) name (the text written on the concept-item)
  const std::string GetName() const noexcept;

  //Move hove
  virtual void hoverStartEvent(QGraphicsSceneHoverEvent *) final;
  virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *) final;

  ///Derived classes respond differently to key presses
  virtual void keyPressEvent(QKeyEvent *event) = 0;

  ///Derived classes draw the concept the same, only with different pens
  ///It is QtEdge however, that also draws an arrow underneath
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) final;

  ///The brush by which the indicator is filled
  void SetIndicatorBrush(const QBrush& brush);

  ///The pen by which the indicator is filled
  void SetIndicatorPen(const QPen& pen);

  ///Set the main brush
  void SetMainBrush(const QBrush& any_brush);

  ///Set the name (the text), the base class (QtRoundedEditRectItem)
  ///will wordwrap it
  ///This class guarantees that GetName() will yield the same string again
  void SetName(const std::string& s);

  ///Set the position
  void SetPos(const double x, const double y);

  ///Increase the sensitive area
  ///Add final to be sure that the shape is not set smaller
  //QPainterPath shape() const final;

  ///Emitted by SetPos
  boost::signals2::signal<void(const double,const double)> m_signal_position_changed;

protected:
  void setBrush(const QBrush &brush) { QtRoundedRectItem::setBrush(brush); }

  ///Hide setPos from callers, let them use SetPos instead
  void setPos(const QPointF &pos) { QtRoundedEditRectItem::setPos(pos); }
  ///Hide setPos from callers, let them use SetPos instead
  void setPos(qreal x, qreal y) { QtRoundedEditRectItem::setPos(x,y); }

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) final;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) final;

  ///Slot whenever the name of the concept is changed
  void OnConceptNameChanged();

  virtual void UpdateBrushesAndPens() = 0;

private:

  ///The concept on the node
  ///m_concept cannot be const: the user might edit it
  const boost::shared_ptr<ribi::cmap::Concept> m_concept;

  ///The brush by which the indicator is filled
  QBrush m_indicator_brush;

  ///The pen by which the indicator is drawn
  QPen m_indicator_pen;

  void setFocus(Qt::FocusReason focusReason) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPT_H
