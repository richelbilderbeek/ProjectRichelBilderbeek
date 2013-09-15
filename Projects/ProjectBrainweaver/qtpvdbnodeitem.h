#ifndef QTPVDBNODEITEM_H
#define QTPVDBNODEITEM_H

#include <boost/shared_ptr.hpp>
#include "qtroundedtextrectitem.h"
#include "qtpvdbconceptmapitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///QtPvdbNodeItem displays a Node
struct QtPvdbNodeItem : public QtPvdbConceptMapItem
{
  virtual ~QtPvdbNodeItem() {}

  ///Node cannot be const as it contains a Concept that the user might want to edit
  ///concept_item contains the Stategy to display (and respond to the concept)
  explicit QtPvdbNodeItem(
    const boost::shared_ptr<ribi::pvdb::Node> node,
    const boost::shared_ptr<QtPvdbConceptItem> concept_item);

  virtual QRectF boundingRect() const;

  QBrush brush() const;

  void DisableAll();
  void EnableAll();

  const boost::shared_ptr<const ribi::pvdb::Concept>  GetConcept() const;
  const boost::shared_ptr<      ribi::pvdb::Concept>  GetConcept()      ;

  const boost::shared_ptr<const QtPvdbConceptItem> GetConceptItem() const final { return m_concept_item; }
  const boost::shared_ptr<      QtPvdbConceptItem> GetConceptItem()       final { return m_concept_item; }

  const boost::shared_ptr<const pvdb::Node>  GetNode() const { return m_node; }
  const boost::shared_ptr<      pvdb::Node>& GetNode()       { return m_node; }

  void SetConcept(const boost::shared_ptr<ribi::pvdb::Concept> concept);

  void SetName(const std::string& name);

  ///Set the X coordinat of the central concept
  void SetX(const double x);

  ///Set the Y coordinat of the central concept
  void SetY(const double y);

  ///m_signal_request_rate_node is emitted due to a m_signal_request_rate_node
  ///of the Node its QtRateConceptItem
  boost::signals2::signal<void (QtPvdbNodeItem *)> m_signal_node_requests_rate_concept;
  boost::signals2::signal<void (QtPvdbNodeItem *)> m_signal_node_requests_rate_examples;

  ///No other signals, these are present in the ConceptItems

protected:

  void focusInEvent(QFocusEvent *event) final;
  void focusOutEvent(QFocusEvent *event) final;
  void keyPressEvent(QKeyEvent *event) final;

  //const boost::shared_ptr<QtPvdbConceptItem>& GetConceptItem() { return m_concept_item; }

  ///Next to QtPvdbConcept::paint, check for collision
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) final;


private:

  ///The Strategy for displaying a Concept
  const boost::shared_ptr<QtPvdbConceptItem> m_concept_item;

  const QPen m_contour_pen;
  const QPen m_focus_pen;

  ///The node being edited, or displayed and not changed, or rated
  const boost::shared_ptr<ribi::pvdb::Node> m_node;

  void OnItemHasUpdated();

  ///The m_node has changed
  void OnNodeChanged(const pvdb::Node * node);
  void OnRequestsSceneUpdate();

  ///The item
  void OnItemRequestsRateConcept();
  void OnItemRequestsRateExamples();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBNODEITEM_H
