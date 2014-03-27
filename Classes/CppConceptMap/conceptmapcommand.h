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
#ifndef CONCEPTMAPCOMMAND_H
#define CONCEPTMAPCOMMAND_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Command can be used to do and undo commands to a concept map Widget
///Command must use a Widget* because a Widget will call a Command with this:
///
///  some_command->CanDo(this);
///
struct Command
{
  virtual ~Command() noexcept {}
  bool CanDoCommand(const Widget * const widget) const noexcept;
  bool CanDoCommand(const boost::shared_ptr<const Widget> widget) const noexcept { return CanDoCommand(widget.get()); }
  void DoCommand(Widget * const widget) noexcept;
  void DoCommand(const boost::shared_ptr<Widget> widget) noexcept { DoCommand(widget.get()); }

  virtual std::string ToStr() const noexcept = 0;
  virtual void Undo() noexcept = 0;

  private:
  ///Hook
  virtual bool CanDoCommandSpecific(const Widget * const widget) const noexcept = 0;

  ///Hook
  virtual void DoCommandSpecific(Widget * const widget) noexcept = 0;
};






} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMAND_H
