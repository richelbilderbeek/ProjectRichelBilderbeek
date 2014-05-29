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
#ifndef CONCEPTMAPEXAMPLES_H
#define CONCEPTMAPEXAMPLES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Container of Example instances
///Examples is displayed by
/// - ?QtExamplesItem: a QGraphicsItem, to be used in a QGraphicsView
/// - QtExamplesDialog: a QDialog
struct Examples
{
  Examples(const std::vector<boost::shared_ptr<cmap::Example> >& v);
  Examples(const Example& rhs) = delete;
  Examples& operator=(const Example& rhs) = delete;


  std::vector<boost::shared_ptr<Example>>& Get() noexcept { return m_v; }
  std::vector<boost::shared_ptr<const Example>> Get() const noexcept;

  std::string ToStr() const noexcept;
  std::string ToXml() const noexcept;

  ///Something of one of the examples was changed
  mutable boost::signals2::signal<void(Examples*)> m_signal_examples_changed;
private:
  ~Examples() noexcept;

  std::vector<boost::shared_ptr<Example>> m_v;

  //void Add(const boost::shared_ptr<cmap::Example>& example);

  ///All signals emitted from the examples are connected to this member function
  void OnExampleChanged() noexcept;

  ///Test this class
  static void Test() noexcept;

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(Examples* x);
};


bool operator==(const Examples& lhs, const Examples& rhs);
bool operator!=(const Examples& lhs, const Examples& rhs);

///Two cmap::Examples instances are sorted as follows:
///(1) By their number of examples
///(2) (if the sizes are equal) Alphabetically on the first different example
bool operator<(const Examples& lhs, const Examples& rhs);

/*
bool operator<(const boost::shared_ptr<const cmap::Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs);
bool operator<(const boost::shared_ptr<const cmap::Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs);
bool operator<(const boost::shared_ptr<Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs);
bool operator<(const boost::shared_ptr<Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs);
bool operator<=(const boost::shared_ptr<const cmap::Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<const cmap::Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<const cmap::Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<const cmap::Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const cmap::Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const cmap::Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<Examples>& lhs, boost::shared_ptr<const cmap::Examples>& rhs) = delete;
*/

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEXAMPLES_H
