//---------------------------------------------------------------------------
/*
WtAboutDialog, Wt dialog for displaying the About class
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtAboutDialog.htm
//---------------------------------------------------------------------------
#include <string>

#include <boost/foreach.hpp>

#include <Wt/WBreak>
#include <Wt/WConfig.h>
#include <Wt/WLabel>
#include <Wt/WTextArea>
#include "wtaboutdialog.h"

ribi::WtAboutDialog::WtAboutDialog(
  const About& about_original,
  const bool display_close_button)
  : m_signal_close{},
    m_button_close(new Wt::WPushButton)
{
  About about = about_original;
  about.AddLibrary("Wt version: " + GetWtVersion());
  about.AddLibrary("WtAboutDialog version: " + GetVersion());

  this->setContentAlignment(Wt::AlignCenter);
  const int min_width = 800;
  //Display the general about text
  {
    const std::vector<std::string> v = about.CreateAboutText();
    BOOST_FOREACH(const std::string s,v)
    {
      new Wt::WLabel(s.c_str(),this);
      this->addWidget(new Wt::WBreak);
    }
  }
  this->addWidget(new Wt::WBreak);
  //Display the libraries used text
  {
    Wt::WTextArea * text = new Wt::WTextArea;
    {
      const std::vector<std::string> v = about.CreateLibrariesUsedText();
      std::string s;
      BOOST_FOREACH(const std::string t,v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(text);
  }
  this->addWidget(new Wt::WBreak);
  //Display the version history
  {
    Wt::WTextArea * text = new Wt::WTextArea;
    {
      const std::vector<std::string> v = about.CreateVersionHistory();
      std::string s;
      BOOST_FOREACH(const std::string t,v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(text);
  }
  this->addWidget(new Wt::WBreak);
  //Display the licence text
  {
    Wt::WTextArea * text = new Wt::WTextArea;
    {
      const std::vector<std::string> v = about.CreateLicenceText();
      std::string s;
      BOOST_FOREACH(const std::string t,v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(text);
  }
  addWidget(new Wt::WBreak);
  {
    const std::string s
      = std::string("Source code built at ")
      + std::string(__DATE__)
      + std::string(" ")
      + std::string(__TIME__);
    new Wt::WLabel(s.c_str(),this);
     this->addWidget(new Wt::WBreak);
  }

  if (display_close_button)
  {
    this->addWidget(new Wt::WBreak);
    this->addWidget(m_button_close);
    m_button_close->setText("Close");
    m_button_close->clicked().connect(
      this,&ribi::WtAboutDialog::OnClose);
  }
}

const std::string ribi::WtAboutDialog::GetVersion()
{
  return "1.5";
}

const std::vector<std::string> ribi::WtAboutDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-01-07: version 1.0: initial version");
  v.push_back("2011-04-10: version 1.1: displays version numbers of Wt and WtAboutDialog");
  v.push_back("2011-04-15: version 1.2: made displayal of Close button optional");
  v.push_back("2011-05-24: version 1.3: made all text areas read-only");
  v.push_back("2011-05-30: version 1.4: should build date and time");
  v.push_back("2011-06-26: version 1.5: added newline for displaying build date and time");
  return v;
}

///GetWtVersion returns the version of the currently installed Wt library
///From http://www.richelbilderbeek.nl/CppGetWtVersion.htm
const std::string ribi::WtAboutDialog::GetWtVersion()
{
  return WT_VERSION_STR;
}

void ribi::WtAboutDialog::OnClose()
{
  //emit that this dialog closes
  m_signal_close();
}

