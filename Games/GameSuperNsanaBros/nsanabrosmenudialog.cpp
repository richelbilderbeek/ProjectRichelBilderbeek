#include "nsanabrosmenudialog.h"

#include <cassert>
#include <iostream>

#include "nsanabrosoptions.h"
#include "nsanabrosoptionsdialog.h"
#include "nsanabrosgamedialog.h"
#include "nsanabrosgamearea2dwidget.h"

ribi::NsanaBrosMenuDialog::NsanaBrosMenuDialog()
  : m_game(0),
    m_options(new NsanaBrosOptionsDialog)
{
  m_game.reset(
    new NsanaBrosGameDialog(
      m_options->GetOptions()));
}

int ribi::NsanaBrosMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::NsanaBrosMenuDialog::~NsanaBrosMenuDialog() noexcept
{

}

const ribi::About ribi::NsanaBrosMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Super Nsana Bros",
    "true two-dimensional platform game",
    "the 29th of March 2011",
    "2011",
    "http://www.richelbilderbeek.nl/GameNsanaBros.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

const ribi::Help ribi::NsanaBrosMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::NsanaBrosMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramSuperNsanaBros
  };
  assert(p);
  return p;
}

const ribi::NsanaBrosOptionsDialog * ribi::NsanaBrosMenuDialog::GetOptionsDialog() const
{
  return m_options.get();
}

const std::string ribi::NsanaBrosMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::NsanaBrosMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-03-xx: Version 1.0: initial version"
    "2013-11-07: Version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

boost::shared_ptr<ribi::NsanaBrosOptionsDialog> ribi::NsanaBrosMenuDialog::UseOptionsDialog()
{
  return m_options;
}

