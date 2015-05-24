//---------------------------------------------------------------------------
/*
Help, class for a program its help information
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppHelp.htm
//---------------------------------------------------------------------------
#ifndef RIBI_HELP_H
#define RIBI_HELP_H

#include <iosfwd>
#include <string>
#include <vector>

namespace ribi {

///Help is used to manage a help screen its info
///Help always has some default options, as used by each MenuDialog
struct Help
{
  //Help options
  struct Option
  {
    explicit Option(
      const char option_short,
      const std::string& option_long,
      const std::string& option_description);
    char m_short;              // a
    std::string m_long;        // about
    std::string m_description; // displays the about information
  };
  explicit Help(
    const std::string& program_name,
    const std::string& program_description,
    const std::vector<Option>& options,
    const std::vector<std::string> example_uses
  );

  const std::vector<std::string>& GetExampleUses() const noexcept { return m_example_uses; }
  const std::vector<Option>& GetOptions() const noexcept { return  m_options; }
  const std::string& GetProgramDescription() const noexcept { return  m_program_description; }
  const std::string& GetProgramName() const noexcept { return  m_program_name; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  // { "ProjectRichelBilderbeek --about", "ProjectRichelBilderbeek ToolHometrainer Exercise.txt" }
  const std::vector<std::string> m_example_uses;
  const std::vector<Option> m_options;

  //RichelBilderbeek's work
  const std::string m_program_description;

  //ProjectRichelBilderbeek
  const std::string m_program_name;

  static const std::vector<Option> AddDefaultOptions(const std::vector<Option>& options);

};

std::ostream& operator<<(std::ostream& os, const Help& help);

} //~namespace ribi

#endif // RIBI_HELP_H
