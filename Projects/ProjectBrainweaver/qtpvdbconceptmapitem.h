#ifndef QTPVDBCONCEPTMAPITEM_H
#define QTPVDBCONCEPTMAPITEM_H

#include <boost/signals2.hpp>

#include "pvdbfwd.h"
#include "qtroundedtextrectitem.h"

namespace ribi {

namespace pvdb {

///Either a Node or Edge of a ConceptMap
struct QtPvdbConceptMapItem : public QtRoundedTextRectItem
{
  ///ABC must have public virtual destructor
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines, and best practices.
  //   ISBN: 0-32-111358-6. Item 50: 'Make base class destructors public and virtual, or protected and nonvirtual'
  virtual ~QtPvdbConceptMapItem() {}

  virtual void DisableAll() = 0;
  virtual void EnableAll() = 0;

  ///Obtain the Concept from either a Node or an Edge
  virtual const boost::shared_ptr<const ribi::pvdb::Concept>  GetConcept() const = 0;
  virtual const boost::shared_ptr<      ribi::pvdb::Concept>  GetConcept()       = 0;

  virtual const boost::shared_ptr<const QtPvdbConceptItem> GetConceptItem() const = 0;
  virtual const boost::shared_ptr<      QtPvdbConceptItem> GetConceptItem()       = 0;

  ///Set the name of the concept
  virtual void SetName(const std::string& name) = 0;

  ///Set the position
  void SetPos(const double x, const double y) { SetX(x); SetY(y); }

  ///Set the X coordinat
  virtual void SetX(const double x) = 0;

  ///Set the Y coordinat
  virtual void SetY(const double y) = 0;

  ///A more specific signal: a Concept requests an edit, this is passed to
  ///OnConceptRequestsEdit, which lets this QtPvdbConceptMapItem request for an edit
  boost::signals2::signal<void(QtPvdbConceptMapItem*)> m_signal_conceptmapitem_requests_edit;

  ///Slot for a Concept its signal to be edited, all it does is add the ConceptMapItem
  ///the Concept is a member of
  void OnConceptRequestsEdit();

  protected:
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  void setPos(const QPointF &pos) { QtRoundedTextRectItem::setPos(pos); }
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  void setPos(qreal x, qreal y) { QtRoundedTextRectItem::setPos(x,y); }

  void hoverMoveEvent(QGraphicsSceneHoverEvent *) final;

  private:
  virtual void SetConcept(const boost::shared_ptr<ribi::pvdb::Concept> concept) = 0;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCONCEPTMAPITEM_H
