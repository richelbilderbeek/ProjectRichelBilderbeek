#ifndef PVDBCONCEPT_H
#define PVDBCONCEPT_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <QRegExp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbcompetency.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#endif

namespace pvdb {

struct ConceptFactory;

///A Concept is a class that has a name and examples
struct Concept
{
  ///Block copying, as signals cannot be copied
  Concept(const pvdb::Concept& other) = delete;
  Concept& operator=(const pvdb::Concept& other) = delete;

  ///Read concept from a std::string read from file
  static const boost::shared_ptr<pvdb::Concept> FromXml(const std::string& s);

  ///Get the examples of the concept, e.g. 'Plato', 'Aristotle'
  const boost::shared_ptr<const pvdb::Examples> GetExamples() const;
  const boost::shared_ptr<pvdb::Examples>& GetExamples() { return m_examples; }

  ///Get the name of the concept, e.g. 'Philosphy'
  const std::string& GetName() const { return m_name; }

  ///Get the rating of this Concept for complexity
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingComplexity() const { return m_rating_complexity; }

  ///Get the rating of this Concept for concreteness
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingConcreteness() const { return m_rating_concreteness; }

  ///Get the rating of this Concept for specificity
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingSpecificity() const { return m_rating_specificity; }

  ///Emitted when the examples are changed
  mutable boost::signals2::signal<void(const pvdb::Concept*)> m_signal_examples_changed;

  ///Emitted when the name is changed
  mutable boost::signals2::signal<void(const pvdb::Concept*)> m_signal_name_changed;

  ///Emitted when the rating of the complexity is changed
  mutable boost::signals2::signal<void(const pvdb::Concept*)> m_signal_rating_complexity_changed;

  ///Emitted when the rating of the complexity is changed
  mutable boost::signals2::signal<void(const pvdb::Concept*)> m_signal_rating_concreteness_changed;

  ///Emitted when the rating of the specificity is changed
  mutable boost::signals2::signal<void(const pvdb::Concept*)> m_signal_rating_specificity_changed;

  ///Convert Concept to a std::string to write to file
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Concept>& t);

  private:
  friend class ::QtPvdbConceptMapDialog;
  friend class ::QtPvdbStudentMenuDialog;
  friend class ::QtPvdbTestConceptItemDialog;
  friend class ::QtPvdbTestConceptMapEditWidgetDialog;
  friend class ::QtPvdbTestConceptMapRateWidgetDialog;
  friend class ::QtPvdbTestEdgeItemDialog;
  friend class ::QtPvdbTestNodeItemDialog;
  friend class ::QtPvdbEdgeItem;
  friend class ::QtPvdbNodeItem;
  friend class ::QtPvdbConceptEditDialog;
  friend class ::QtPvdbRateConceptDialog;
  friend class ::QtPvdbRateExamplesDialog;
  ///Set the examples
  void SetExamples(const boost::shared_ptr<pvdb::Examples>& examples);

  ///Set the name
  void SetName(const std::string& name);

  ///Set the rating of this Concept for complexity
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingComplexity(const int rating_complexity);

  ///Set the rating of this Concept for concreteness
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingConcreteness(const int rating_concreteness);

  ///Set the rating of this Concept for specificity
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingSpecificity(const int rating_specificity);

  private:

  ///Examples of the concept, e.g. 'Plato', 'Aristotle'
  boost::shared_ptr<pvdb::Examples> m_examples;

  ///The name of the concept, e.g. 'Philosphy'
  std::string m_name;

  ///The rating of this Concept for complexity
  ///-1: not rated, 0: lowest, 2: highest
  int m_rating_complexity;

  ///The rating of this Concept for concreteness
  ///-1: not rated, 0: lowest, 2: highest
  int m_rating_concreteness;

  ///The rating of this Concept for specificity
  ///-1: not rated, 0: lowest, 2: highest
  int m_rating_specificity;

  ///Test this class
  static void Test();

  ///Use checked_delete for destructor
  ~Concept() {}
  friend void boost::checked_delete<>(pvdb::Concept* x);

  ///Let only ConceptFactory construct Concepts
  Concept(
    const std::string& name,
    const boost::shared_ptr<pvdb::Examples>& examples,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity);
  friend ConceptFactory;

};


bool IsEqual(const pvdb::Concept& lhs, const pvdb::Concept& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);
bool operator==(const pvdb::Concept& lhs, const pvdb::Concept& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator!=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);
bool operator!=(const pvdb::Concept& lhs, const pvdb::Concept& rhs) = delete;

///Two Concept instances are ordered as follows:
///(1) Alphabetically on the name
///(2) (if the names are equal) On their Examples
bool operator<(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator<(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs);

bool operator<=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator<=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;
bool operator<=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator<=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;
bool operator>(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator>(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;
bool operator>(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator>(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;
bool operator>=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs) = delete;
bool operator>=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs) = delete;

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbconceptfactory.h"
#endif

#endif // PVDBCONCEPT_H
