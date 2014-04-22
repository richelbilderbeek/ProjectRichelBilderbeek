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
#ifndef CONCEPTMAPEXAMPLE_H
#define CONCEPTMAPEXAMPLE_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "conceptmapcompetency.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ExampleFactory;

///A concept (on a node or an edge) can have examples
struct Example
{
  Example(const Example&) = delete;
  Example& operator=(const Example&) = delete;

  ///Convert a cmap::Competency to a std::string
  static std::string CompetencyToStr(const Competency competency) noexcept;

  ///Get the competency, as might be judged by an assessor
  cmap::Competency GetCompetency() const noexcept { return m_competency; }

  ///Has an assessor rated this example as being an addition to the complexity?
  bool GetIsComplex() const noexcept { return m_is_complex; }

  ///Has an assessor rated this example as being an addition to the concreteness?
  bool GetIsConcrete() const noexcept { return m_is_concrete; }

  ///Has an assessor rated this example as being an addition to the specificity?
  bool GetIsSpecific() const noexcept { return m_is_specific; }

  ///Get the text of the example
  const std::string& GetText() const noexcept { return m_text; }

  ///Set the competency
  void SetCompetency(const cmap::Competency competency) noexcept;

  ///Has an assessor rated this example as being an addition to the complexity?
  void SetIsComplex(const bool is_complex) noexcept { m_is_complex = is_complex; }

  ///Has an assessor rated this example as being an addition to the concreteness?
  void SetIsConcrete(const bool is_concrete) noexcept { m_is_concrete = is_concrete; }

  ///Has an assessor rated this example as being an addition to the specificity?
  void SetIsSpecific(const bool is_specific) noexcept { m_is_specific = is_specific; }

  ///Set the text
  void SetText(const std::string& text) noexcept;

  ///Convert a std::string to a cmap::Competency
  static Competency StrToCompetency(const std::string& s);

  ///Test this class
  static void Test() noexcept;

  ///Convert Example to a std::string
  std::string ToXml() const noexcept;

  ///Emitted when SetCompetency changes the competency
  boost::signals2::signal<void(Example*)> m_signal_competency_changed;

  ///Emitted when SetText changes the text
  boost::signals2::signal<void(Example*)> m_signal_text_changed;

private:

  ///The competency, as might be judged by an assessor
  cmap::Competency m_competency;

  ///Has an assessor rated this example as being an addition to the complexity?
  bool m_is_complex;

  ///Has an assessor rated this example as being an addition to the concreteness?
  bool m_is_concrete;

  ///Has an assessor rated this example as being an addition to the specificity?
  bool m_is_specific;

  ///The text of the example
  ///For example: 'Plato', 'When I was a kid', 'As I did on holiday'
  std::string m_text;

  ///Set the competency with a string
  void SetCompetencyAsStr(const std::string& s) const;

  ///Use checked_delete only
  ~Example() {}
  friend void boost::checked_delete<>(Example* x);

  ///Only let ExampleFactory create Example instances
  Example(
    const std::string& text,
    const cmap::Competency competency = cmap::Competency::uninitialized,
    const bool is_complex = true,
    const bool is_concrete = true,
    const bool is_specific = true
    );
  friend class ExampleFactory;
};

bool operator==(const cmap::Example& lhs, const cmap::Example& rhs) noexcept;
bool operator!=(const cmap::Example& lhs, const cmap::Example& rhs) noexcept;

bool operator<(const Example& lhs,const Example& rhs) noexcept;
bool operator>(const Example& lhs,const Example& rhs) noexcept;

bool operator<(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs) = delete;
bool operator<(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<cmap::Example>& rhs) = delete;
bool operator<(const boost::shared_ptr<cmap::Example>& lhs,const boost::shared_ptr<cmap::Example>& rhs) = delete;
bool operator<(const boost::shared_ptr<cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs) = delete;
bool operator>(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs) = delete;
bool operator>(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<cmap::Example>& rhs) = delete;
bool operator>(const boost::shared_ptr<cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs) = delete;
bool operator>(const boost::shared_ptr<cmap::Example>& lhs,const boost::shared_ptr<cmap::Example>& rhs) = delete;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEXAMPLE_H
