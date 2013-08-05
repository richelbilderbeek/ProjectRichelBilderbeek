#ifndef QTPVDBEDITCONCEPTITEM_H
#define QTPVDBEDITCONCEPTITEM_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptitem.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

///Displays a Concept that might be edited
struct QtPvdbEditConceptItem : public QtPvdbConceptItem
{
  //concept will be modified
  explicit QtPvdbEditConceptItem(const boost::shared_ptr<pvdb::Concept> concept);

  ///Signalled when the user wants to edit
  boost::signals2::signal<void (QtPvdbConceptItem *)> m_signal_request_edit;

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  static void Test() {}

  ///A Edit ConceptItem does not change its brushes and pens
  void UpdateBrushesAndPens() {}
};

#endif // QTPVDBEDITCONCEPTITEM_H
