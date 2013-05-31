#ifndef QTPVDBCONCEPTMAPITEM_H
#define QTPVDBCONCEPTMAPITEM_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/signals2.hpp>

#include "pvdbfwd.h"
#include "qtroundedtextrectitem.h"

///Either a Node or Edge of a ConceptMap
struct QtPvdbConceptMapItem : public QtRoundedTextRectItem
{
  virtual ~QtPvdbConceptMapItem() {}

  virtual void DisableAll() = 0;
  virtual void EnableAll() = 0;

  ///Obtain the Concept from either a Node or an Edge
  virtual const boost::shared_ptr<const pvdb::Concept>  GetConcept() const = 0;
  virtual const boost::shared_ptr<      pvdb::Concept>  GetConcept()       = 0;

  virtual const boost::shared_ptr<const QtPvdbConceptItem> GetConceptItem() const = 0;

  ///Set the name of the concept
  virtual void SetName(const std::string& name) = 0;

  ///A more specific signal: a Concept requests an edit, this is passed to
  ///OnConceptRequestsEdit, which lets this QtPvdbConceptMapItem request for an edit
  boost::signals2::signal<void(QtPvdbConceptMapItem*)> m_signal_conceptmapitem_requests_edit;

  ///Slot for a Concept its signal to be edited, all it does is add the ConceptMapItem
  ///the Concept is a member of
  void OnConceptRequestsEdit();

  private:
  virtual void SetConcept(const boost::shared_ptr<pvdb::Concept> concept) = 0;

};

#endif // QTPVDBCONCEPTMAPITEM_H
