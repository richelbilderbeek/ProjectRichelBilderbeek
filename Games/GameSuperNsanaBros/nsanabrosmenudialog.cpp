//---------------------------------------------------------------------------
#include "nsanabrosstlheader.h"
//---------------------------------------------------------------------------
NsanaBrosMenuDialog::NsanaBrosMenuDialog()
  : m_game(0),
    m_options(new NsanaBrosOptionsDialog)
{
  m_game.reset(
    new NsanaBrosGameDialog(
      m_options->GetOptions()));
}
//---------------------------------------------------------------------------
const About NsanaBrosMenuDialog::GetAbout()
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
//---------------------------------------------------------------------------
const NsanaBrosOptionsDialog * NsanaBrosMenuDialog::GetOptionsDialog() const
{
  return m_options.get();
}
//---------------------------------------------------------------------------
const std::string NsanaBrosMenuDialog::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> NsanaBrosMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-03-xx: Version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
boost::shared_ptr<NsanaBrosOptionsDialog> NsanaBrosMenuDialog::UseOptionsDialog()
{
  return m_options;
}
//---------------------------------------------------------------------------
