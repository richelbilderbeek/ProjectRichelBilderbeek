#include "help.h"

#include <algorithm>
#include <iostream>

ribi::Help::Help(
  const std::string& program_name,
  const std::string& program_description,
  const std::vector<Option>& options)
  : m_options(AddDefaultOptions(options)),
    m_program_description(program_description),
    m_program_name(program_name)
{

}

const std::vector<ribi::Help::Option> ribi::Help::AddDefaultOptions(const std::vector<Option>& options)
{
  const int max_length = std::max_element(
    options.begin(), options.end(),
    [](const Option& lhs, const Option& rhs)
    {
  HIERO
    }
  );

  std::vector<Option> v { options };
  v.push_back(Option("a","about","display about message"));
  v.push_back(Option("h","help","display this help message"));
  v.push_back(Option("i","history","display version history"));
  v.push_back(Option("l","licence","display licence"));
  v.push_back(Option("v","version","display version"));
  return v;
}



std::ostream& ribi::operator<<(std::ostream& os, const Help& help)
{
  os
    << help.GetProgramName() << " help menu\n"
    << "\n";
    << help.GetProgramDescription() << "\n"
    << "\n"
    << "Uses:\n";
  for (const Help::Option& s: help.GetOptions())
  {
    os << "-" << s.m_short << ", --" << s.m_long << std::string(2,' ') << "\n";
  }

  os
    << "\n"
    << "Allowed options for " << help.GetProgramName() << ":";

    "-a, --about     display about message",
    "-h, --help                produce this help message",
    "-i, --history             display version history",
    "-l, --licence             display licence",
    "-p, --program             list all possible programs",
    "-s, --status              display class statuses",
    "-v, --version             display class versions",
    "",
    "Example uses:",
    "  ProjectRichelBilderbeekConsole --help",
    "  ProjectRichelBilderbeekConsole Hometrainer --help"
    };

}
