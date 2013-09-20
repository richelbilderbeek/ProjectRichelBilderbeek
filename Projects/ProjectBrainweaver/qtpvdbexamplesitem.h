#ifndef QTPVDBEXAMPLESITEM_H
#define QTPVDBEXAMPLESITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "qtroundededitrectitem.h"
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct QtPvdbExamplesItem : public QtRoundedEditRectItem
{
  QtPvdbExamplesItem(QGraphicsItem* parent = 0);
  QtPvdbExamplesItem(const QtPvdbExamplesItem&) = delete;
  QtPvdbExamplesItem& operator=(const QtPvdbExamplesItem&) = delete;
  ~QtPvdbExamplesItem() noexcept {}
  ///Check the buddy item
  const QtPvdbConceptMapItem* GetBuddyItem() const noexcept { return m_item; }

  ///Set the concept this item displays the examples of.
  ///If the concept is nullptr, this item hides
  void SetBuddyItem(const QtPvdbConceptMapItem* const item);

  ///Request update of QGraphicsScene, because this item has changed
  mutable boost::signals2::signal<void() > m_signal_request_scene_update;

protected:

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

  ///The concept this item displays the examples of.
  ///If m_concept is nullptr, this item hides
  const QtPvdbConceptMapItem* m_item;

  ///Item has updated, Examples must follow
  void OnItemUpdated();

  void SetExamples(const boost::shared_ptr<const pvdb::Examples>& examples);
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBEXAMPLESITEM_H
