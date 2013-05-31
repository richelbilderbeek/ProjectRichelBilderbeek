#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbeditconceptitem.h"

#include <QKeyEvent>

#include "pvdbconcept.h"
#include "qtpvdbbrushfactory.h"
#include "trace.h"

QtPvdbEditConceptItem::QtPvdbEditConceptItem(const boost::shared_ptr<pvdb::Concept>& concept)
  : QtPvdbConceptItem(concept)
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  this->setBrush(QtPvdbBrushFactory::CreateWhiteGradientBrush()); //NEW 2013-04-09

  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&QtPvdbEditConceptItem::OnConceptNameChanged,this)); //Obligatory
}


void QtPvdbEditConceptItem::keyPressEvent(QKeyEvent *event)
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
