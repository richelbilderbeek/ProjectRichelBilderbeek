#ifndef QTCONCEPTMAPCONCEPTMAPITEM_H
#define QTCONCEPTMAPCONCEPTMAPITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include "qtconceptmapfwd.h"
#include "qtroundededitrectitem.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Either a Node or Edge of a ConceptMap
///QtRoundedTextRectItem: single line
///QtRoundedEditRectItem: multiple lines
struct QtConceptMapItem : public QtRoundedEditRectItem //NEW 2013-09-15
{
  virtual ~QtConceptMapItem() noexcept {}

  virtual void DisableAll() = 0;
  virtual void EnableAll() = 0;

  ///Obtain the Concept from either a Node or an Edge
  virtual const boost::shared_ptr<const ribi::cmap::Concept>  GetConcept() const = 0;
  virtual const boost::shared_ptr<      ribi::cmap::Concept>  GetConcept()       = 0;

  virtual const boost::shared_ptr<const QtItemDisplayStrategy> GetConceptItem() const = 0;
  virtual const boost::shared_ptr<      QtItemDisplayStrategy> GetConceptItem()       = 0;

  ///Set the name of the concept
  virtual void SetName(const std::string& name) = 0;

  ///Set the position
  void SetPos(const double x, const double y) { SetX(x); SetY(y); }

  ///Set the X coordinat
  virtual void SetX(const double x) = 0;

  ///Set the Y coordinat
  virtual void SetY(const double y) = 0;

  ///A more specific signal: a Concept requests an edit, this is passed to
  ///OnConceptRequestsEdit, which lets this QtConceptMapItem request for an edit
  boost::signals2::signal<void(QtConceptMapItem*)> m_signal_conceptmapitem_requests_edit;

  ///Slot for a Concept its signal to be edited, all it does is add the ConceptMapItem
  ///the Concept is a member of
  void OnConceptRequestsEdit();

  protected:
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  void setPos(const QPointF &pos) { QtRoundedEditRectItem::setPos(pos); }
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  void setPos(qreal x, qreal y) { QtRoundedEditRectItem::setPos(x,y); }

  void hoverMoveEvent(QGraphicsSceneHoverEvent *) final;

  private:
  virtual void SetConcept(const boost::shared_ptr<ribi::cmap::Concept> concept) = 0;

};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAPITEM_H
