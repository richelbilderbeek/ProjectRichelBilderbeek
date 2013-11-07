#include "nsanabrosstlheader.h"

ribi::NsanaBrosMenuDialog::NsanaBrosMenuDialog()
  : m_game(0),
    m_options(new NsanaBrosOptionsDialog)
{
  m_game.reset(
    new NsanaBrosGameDialog(
      m_options->GetOptions()));
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

const NsanaBrosOptionsDialog * ribi::NsanaBrosMenuDialog::GetOptionsDialog() const
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

boost::shared_ptr<NsanaBrosOptionsDialog> ribi::NsanaBrosMenuDialog::UseOptionsDialog()
{
  return m_options;
}

