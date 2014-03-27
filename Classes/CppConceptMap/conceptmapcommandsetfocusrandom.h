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
#ifndef CONCEPTMAPCOMMANDSETFOCUSRANDOM_H
#define CONCEPTMAPCOMMANDSETFOCUSRANDOM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Set focus with a coordinat
///- opposite of LoseFocus
///- SetFocus does not care if there currently is something in focus
struct CommandSetFocusRandom : public Command
{
  CommandSetFocusRandom() : m_old_focus{}, m_widget{} {}
  CommandSetFocusRandom(const CommandSetFocusRandom&) = delete;
  CommandSetFocusRandom& operator=(const CommandSetFocusRandom&) = delete;
  ~CommandSetFocusRandom() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "set focus random"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Node> m_old_focus;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDSETFOCUSRANDOM_H
