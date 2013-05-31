//---------------------------------------------------------------------------
/*
Loose, reduce an emailaddress to an unknown limited set
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
//From http://www.richelbilderbeek.nl/ToolLoose.htm
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WScrollArea>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "wtloosemaindialog.h"

WtLooseMaindialog::WtLooseMaindialog()
  : m_button_about(new Wt::WPushButton),
    m_button_check(new Wt::WPushButton),
    m_button_licence(new Wt::WPushButton),
    m_button_whatsnew(new Wt::WPushButton),
    m_container(new Wt::WContainerWidget),
    m_edit(new Wt::WLineEdit),
    m_image(new Wt::WImage),
    m_result(new Wt::WText),
    m_scroll_area(new Wt::WScrollArea(this)),
    m_text_area(new Wt::WTextArea)
{
  m_container->addWidget(new Wt::WText("To which email adress would you like to mail?"));
  m_container->addWidget(new Wt::WBreak());
  m_container->addWidget(m_edit);
  m_container->addWidget(new Wt::WText("@frameless.com"));
  m_container->addWidget(m_button_check);
  m_container->addWidget(m_button_about);
  m_container->addWidget(m_button_licence);
  m_container->addWidget(m_button_whatsnew);
  m_container->addWidget(new Wt::WBreak());
  m_container->addWidget(m_result);
  m_container->addWidget(new Wt::WBreak());
  m_container->addWidget(m_image);
  m_container->addWidget(new Wt::WBreak());
  m_container->addWidget(m_text_area);

  m_scroll_area->setWidget(m_container);

  m_button_about->setText("About");
  m_button_check->setText("Check");
  m_button_licence->setText("Licence");
  m_button_whatsnew->setText("What's new?");
  m_edit->setText("any_name");
  m_edit->setFocus();
  m_image->setMaximumSize(200,200);
  m_result->setText("This would result in an email to this person:");
  m_result->hide();
  m_text_area->hide();
  m_text_area->setMinimumSize(800,256);

  m_button_about->clicked().connect(this, &WtLooseMaindialog::onAboutClick);
  m_button_check->clicked().connect(this, &WtLooseMaindialog::onCheckClick);
  m_button_licence->clicked().connect(this, &WtLooseMaindialog::onLicenceClick);
  m_button_whatsnew->clicked().connect(this, &WtLooseMaindialog::onWhatsNewClick);

}

const std::vector<std::string> WtLooseMaindialog::GetAbout()
{
  std::vector<std::string> v;
  v.push_back("Loose, tool to redirect to any email adress");
  v.push_back("Version " + GetVersion());
  v.push_back("Copyright (C) 2010-2013 Richel Bilderbeek");
  v.push_back("");
  v.push_back("Programmed by Richel Bilderbeek");
  v.push_back("on the 25th of May 2013");
  v.push_back("");
  v.push_back("From http://www.richelbilderbeek.nl/ToolLoose.htm");
  v.push_back("Licenced under GPL 3.0");
  return v;
}

const std::vector<std::string> WtLooseMaindialog::GetLicence()
{
  std::vector<std::string> v;
  v.push_back("Loose, reduce an emailaddress to an unknown limited set");
  v.push_back("Copyright (C) 2007  Richel Bilderbeek");
  v.push_back("");
  v.push_back("This program is free software: you can redistribute it and/or modify");
  v.push_back("it under the terms of the GNU General Public License as published by");
  v.push_back("the Free Software Foundation, either version 3 of the License, or");
  v.push_back("(at your option) any later version.");
  v.push_back("");
  v.push_back("This program is distributed in the hope that it will be useful,");
  v.push_back("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  v.push_back("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
  v.push_back("GNU General Public License for more details.");
  v.push_back("\n");
  v.push_back("You should have received a copy of the GNU General Public License");
  v.push_back("along with this program.  If not, see <http://www.gnu.org/licenses/>.");
  return v;
}

const std::string WtLooseMaindialog::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> WtLooseMaindialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2010-12-03: version 1.0: initial version");
  v.push_back("2010-12-21: version 1.1: seperated WWidget from WApplication");
  v.push_back("2010-12-24: version 2.0: added 'Check' and 'What's New' buttons");
  v.push_back("2013-05-25: version 2.1: conformized naming towards ProjectRichelBilderbeek");
  return v;
}

void WtLooseMaindialog::onAboutClick()
{
  m_result->hide();

  const std::vector<std::string> v = GetAbout();
  std::string s;
  BOOST_FOREACH(const std::string& line,v)
  {
    s += line + '\n';
  }
  m_text_area->setText(s);

  m_text_area->show();
  m_image->setImageRef("R.png");
}

void WtLooseMaindialog::onCheckClick()
{
  m_text_area->hide();
  m_result->show();

  const int n_photos = 4;
  const int photo_index
    = (StringToMagicInt(m_edit->text().toUTF8())
    % n_photos)
    + 1; //Humans start counting from 1
  m_image->setImageRef(
    "RichelBilderbeek"
    + boost::lexical_cast<std::string>(photo_index)
    + ".jpg");
  m_image->setAlternateText(
    "Richel Bilderbeek "
    + boost::lexical_cast<std::string>(photo_index));
  m_image->setToolTip(
    "Richel Bilderbeek "
    + boost::lexical_cast<std::string>(photo_index));
}

void WtLooseMaindialog::onLicenceClick()
{
  m_result->hide();

  const std::vector<std::string> v = GetLicence();
  std::string s;
  BOOST_FOREACH(const std::string& line,v)
  {
    s += line + '\n';
  }
  m_text_area->setText(s);


  m_text_area->show();
  m_image->setImageRef("R.png");
}

void WtLooseMaindialog::onWhatsNewClick()
{
  m_result->hide();

  const std::vector<std::string> v = GetVersionHistory();
  std::string s;
  BOOST_FOREACH(const std::string& line,v)
  {
    s += line + '\n';
  }
  m_text_area->setText(s);


  m_text_area->show();
  m_image->setImageRef("R.png");
}

int StringToMagicInt(const std::string& s)
{
  int i = 0;
  BOOST_FOREACH(const char& c,s)
  {
    i+=static_cast<int>(c);
  }
  return i;
}


