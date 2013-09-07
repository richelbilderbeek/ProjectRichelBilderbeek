#include "qtpvdbeditconceptitem.h"

#include <QKeyEvent>

#include "pvdbconcept.h"
#include "qtpvdbbrushfactory.h"
#include "trace.h"

ribi::pvdb::QtPvdbEditConceptItem::QtPvdbEditConceptItem(const boost::shared_ptr<ribi::pvdb::Concept> concept)
  : QtPvdbConceptItem(concept)
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  this->setBrush(QtPvdbBrushFactory::CreateGrayGradientBrush()); //NEW 2013-04-09

  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&ribi::pvdb::QtPvdbEditConceptItem::OnConceptNameChanged,this)); //Obligatory

  //GetConcept()->m_signal_rating_complexity_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
  //GetConcept()->m_signal_rating_concreteness_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
  //GetConcept()->m_signal_rating_specificity_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
}


void ribi::pvdb::QtPvdbEditConceptItem::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_F2:
      m_signal_request_edit(this);
      m_signal_request_scene_update(); //???really needed
    return; //Done
    break;
  }
}
