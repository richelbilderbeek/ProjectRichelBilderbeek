#include "richelbilderbeekplaceholdermenudialog.h"


#include <cassert>
#include <iostream>

ribi::PlaceholderMenuDialog::PlaceholderMenuDialog(
  const ribi::About& about,
  const boost::shared_ptr<const ribi::Program> program,
  const std::string& version,
  const std::vector<std::string> version_history
  )
  : m_about(about),
    m_program(program),
    m_version(version),
    m_version_history(version_history)
{
  assert(m_program);
  assert(!m_version.empty());
  assert(!m_version_history.empty());
}

int ribi::PlaceholderMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

const ribi::Help ribi::PlaceholderMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}
