//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef RICHELBILDERBEEKMENUDIALOG_H
#define RICHELBILDERBEEKMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace RichelBilderbeek {

struct Program;

///The GUI independent version of Project Richel Bilderbeek its menu dialog
struct MenuDialog
{
  MenuDialog();

  ///Get every Program by Richel Bilderbeek
  const std::vector<boost::shared_ptr<Program> >& GetPrograms() const { return m_programs; }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the About information of this class
  static const About GetAbout() noexcept;

  ///Every Program by Richel Bilderbeek
  const std::vector<boost::shared_ptr<Program> > m_programs;


  private:
  ///Create all programs in a sorted order
  const std::vector<boost::shared_ptr<Program> > CreatePrograms() const;
};

} //~namespace RichelBilderbeek
} //~namespace ribi

#endif // RICHELBILDERBEEKMENUDIALOG_H

