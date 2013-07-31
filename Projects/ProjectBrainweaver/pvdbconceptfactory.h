#ifndef PVDBCONCEPTFACTORY_H
#define PVDBCONCEPTFACTORY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <array>
#include <vector>

#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include "pvdbcompetency.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif


///Creates pvdb::Concepts
namespace pvdb {

struct ConceptFactory
{
  //Default and complete Create method
  static const boost::shared_ptr<pvdb::Concept> Create(
    const std::string& name,
    const boost::shared_ptr<pvdb::Examples>& examples,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity);

  static const boost::shared_ptr<pvdb::Concept> Create(
    const std::string& name = "",
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const bool is_complex = true,
    const int rating_complexity = -1,
    const int rating_concreteness = -1,
    const int rating_specificity = -1
    );

  #ifndef NDEBUG
  ///Like a Concept deep-copy constructor
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<pvdb::Concept> DeepCopy(
    const boost::shared_ptr<const pvdb::Concept>& concept);
  #endif

  ///Obtain some testing concepts
  static const std::vector<boost::shared_ptr<pvdb::Concept> > GetTests();
};

} //~namespace pvdb

#endif // PVDBCONCEPTFACTORY_H
