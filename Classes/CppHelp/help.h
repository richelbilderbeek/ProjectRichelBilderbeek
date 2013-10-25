#ifndef HELP_H
#define HELP_H

#include <iosfwd>
#include <set>
#include <string>

namespace ribi {

///Help is used to manage a help screen its info
///Help always has some default options, as used by each MenuDialog
struct Help
{
  //Help options
  struct Option
  {
    Option(
      const std::string& option_short,
      const std::string& option_long,
      const std::string& option_description)
      : m_short(option_short),
        m_long(option_long),
        m_description(option_description)
    {

    }

    const std::string m_short;       // a
    const std::string m_long;        // about
    const std::string m_description; // displays the about information
  };
  Help(
    const std::string& program_name,
    const std::string& program_description,
    const std::set<Option>& options);

  const const std::vector<Option>& GetOptions() const noexcept { return  m_options; }
  const std::string& GetProgramDescription() const noexcept { return  m_program_description; }
  const std::string& GetProgramName() const noexcept { return  m_program_name; }

  private:

  const std::vector<Option> m_options;
  const std::string m_program_description;
  const std::string m_program_name;

  static const std::vector<Option> AddDefaultOptions(const std::vector<Option>& options);
};

std::ostream& operator<<(std::ostream& os, const Help& help);

} //~namespace ribi

#endif // HELP_H
