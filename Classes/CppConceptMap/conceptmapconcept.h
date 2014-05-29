//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#ifndef CONCEPTMAPCONCEPT_H
#define CONCEPTMAPCONCEPT_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <QRegExp>
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ConceptFactory;

///A Concept is a class that has a name and examples
///A Concept is a Node without coordinats
///A Concept is an Edge without coordinats, source and target
///A Concept is the GUI independent part of a concept. It is displayed as:
/// - QtConceptDialog (as a QDialog, to be used in a QDialog)
/// - (as part of QtNode)
/// - (as part of QtEdge)
struct Concept
{
  ///Block copying, as signals cannot be copied
  Concept(const Concept& other) = delete;
  Concept& operator=(const Concept& other) = delete;

  ///Get the examples of the concept, e.g. 'Plato', 'Aristotle'
  boost::shared_ptr<const Examples> GetExamples() const noexcept;
  boost::shared_ptr<Examples>& GetExamples() noexcept { return m_examples; }

  ///Has an assessor rated the name of this concept as being an addition to the complexity?
  ///This is something different than m_rating_complexity:
  ///m_is_complex can be used to help the assessor determine a m_rating_complexity,
  ///but m_rating_complexity is the final and complete rating
  bool GetIsComplex() const noexcept { return m_is_complex; }

  ///Get the name of the concept, e.g. 'Philosphy'
  const std::string& GetName() const noexcept { return m_name; }

  ///Get the rating of this Concept for complexity
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingComplexity() const noexcept { return m_rating_complexity; }

  ///Get the rating of this Concept for concreteness
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingConcreteness() const noexcept { return m_rating_concreteness; }

  ///Get the rating of this Concept for specificity
  ///-1: not rated, 0: lowest, 2: highest
  int GetRatingSpecificity() const noexcept { return m_rating_specificity; }

  ///Set the examples
  void SetExamples(const boost::shared_ptr<Examples>& examples) noexcept;

  ///Has an assessor rated the name of this concept as being an addition to the complexity?
  ///This is something different than m_rating_complexity:
  ///m_is_complex can be used to help the assessor determine a m_rating_complexity,
  ///but m_rating_complexity is the final and complete rating
  void SetIsComplex(const bool is_complex) noexcept;

  ///Set the name
  void SetName(const std::string& name) noexcept;

  ///Set the rating of this Concept for complexity
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingComplexity(const int rating_complexity) noexcept;

  ///Set the rating of this Concept for concreteness
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingConcreteness(const int rating_concreteness) noexcept;

  ///Set the rating of this Concept for specificity
  ///-1: not rated, 0: lowest, 2: highest
  void SetRatingSpecificity(const int rating_specificity) noexcept;

  ///Convert Concept to a short std::string
  std::string ToStr() const noexcept;

  ///Convert Concept to a std::string to write to file
  std::string ToXml() const noexcept;

  ///Emitted when the examples are changed
  mutable boost::signals2::signal<void(Concept*)> m_signal_examples_changed;

  ///Emitted when IsComplex
  mutable boost::signals2::signal<void(Concept*)> m_signal_is_complex_changed;

  ///Emitted when the name is changed
  mutable boost::signals2::signal<void(Concept*)> m_signal_name_changed;

  ///Emitted when the rating of the complexity is changed
  mutable boost::signals2::signal<void(Concept*)> m_signal_rating_complexity_changed;

  ///Emitted when the rating of the complexity is changed
  mutable boost::signals2::signal<void(Concept*)> m_signal_rating_concreteness_changed;

  ///Emitted when the rating of the specificity is changed
  mutable boost::signals2::signal<void(Concept*)> m_signal_rating_specificity_changed;

  private:

  ///Examples of the concept, e.g. 'Plato', 'Aristotle'
  boost::shared_ptr<Examples> m_examples;

  ///Has an assessor rated the name of this concept as being an addition to the complexity?
  ///This is something different than m_rating_complexity:
  ///m_is_complex can be used to help the assessor determine a m_rating_complexity,
  ///but m_rating_complexity is the final and complete rating
  bool m_is_complex;

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
  static void Test() noexcept;

  ///Use checked_delete for destructor
  ~Concept() {}
  friend void boost::checked_delete<>(Concept* x);

  ///Let only ConceptFactory construct Concepts
  Concept(
    const std::string& name,
    const boost::shared_ptr<Examples>& examples,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity);
  friend ConceptFactory;
};

bool operator==(const Concept& lhs, const Concept& rhs);
bool operator!=(const Concept& lhs, const Concept& rhs);

///Two Concept instances are ordered as follows:
///(1) Alphabetically on the name
///(2) (if the names are equal) On their Examples
bool operator<(const Concept& lhs, const Concept& rhs);

bool operator<(
  const boost::shared_ptr<Concept>& lhs,
  const boost::shared_ptr<Concept>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<const Concept>& lhs,
  const boost::shared_ptr<      Concept>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<      Concept>& lhs,
  const boost::shared_ptr<const Concept>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<const Concept>& lhs,
  const boost::shared_ptr<const Concept>& rhs) = delete;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCONCEPT_H
