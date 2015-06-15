//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestEntrance.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wttestentrancemaindialog.h"

#include <cassert>

#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WTable>
#include <Wt/WTableRow>

#include "ipaddress.h"
#include "testentrancemenudialog.h"
#include "wtentrance.h"
#include "wtaboutdialog.h"
#pragma GCC diagnostic pop

ribi::ToolTestEntrance::WtMainDialog::Ui::Ui()
  : m_edit(new Wt::WLineEdit),
    m_view_names_dialog(new Wt::WContainerWidget),
    m_view_visits_dialog(new Wt::WContainerWidget)
{
  assert(m_view_visits_dialog);
  m_edit->setMinimumSize(400,Wt::WLength::Auto);
}

ribi::ToolTestEntrance::WtMainDialog::WtMainDialog(boost::shared_ptr<const IpAddress> ip_address)
 :  m_ip_address(ip_address),
    ui{}
{
  assert(ip_address);
  this->setContentAlignment(Wt::AlignCenter);
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    menu->setStyleClass("menu");
    {

      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Welcome",
        CreateNewWelcomeDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "View names",
        ui.m_view_names_dialog);
      menu->addItem(item);
    }
    {
      assert(ui.m_view_visits_dialog);
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "View visits",
        ui.m_view_visits_dialog);
      menu->addItem(item);
    }
    //Display menu on top
    this->addWidget(menu);
    this->addWidget(new Wt::WBreak);
    //Display contents below menu
    this->addWidget(contents);
  }

  //DO NOT MAKE THESE CONNECTIONS!
  //When closing the page, and opening one again,
  //these signals connect to the old page!
  //WtEntrance::Get()->m_signal_name_changed.connect(boost::bind(
  //  &ribi::ToolTestEntrance::WtMainDialog::OnNewName,this));

  //WtEntrance::Get()->m_signal_new_visit.connect(boost::bind(
  //  &ribi::ToolTestEntrance::WtMainDialog::OnNewVisit,this));

  OnEditChanged();
  OnNewName();
  OnNewVisit();
}

void ribi::ToolTestEntrance::WtMainDialog::OnNewName()
{
  assert(ui.m_view_names_dialog);
  ui.m_view_names_dialog->clear();
  ui.m_view_names_dialog->addWidget(new Wt::WBreak);
  const std::vector<std::pair<std::string,std::string> > v
    = WtEntrance::Get()->GetNames();
  std::for_each(v.begin(),v.end(),
    [this](const std::pair<std::string,std::string>& p)
    {
      const std::string s
        = p.first
        + std::string(": ")
        + p.second;
      ui.m_view_names_dialog->addWidget(new Wt::WLabel(s.c_str()));
      ui.m_view_names_dialog->addWidget(new Wt::WBreak);
    }
  );
}

void ribi::ToolTestEntrance::WtMainDialog::OnNewVisit()
{
  assert(ui.m_view_visits_dialog);
  ui.m_view_visits_dialog->clear();
  ui.m_view_visits_dialog->addWidget(new Wt::WBreak);
  const std::vector<std::pair<std::string,std::string> > v
    = WtEntrance::Get()->GetVisits();
  std::for_each(v.begin(),v.end(),
    [this](const std::pair<std::string,std::string>& p)
    {
      const std::string s
        = p.first
        + std::string(": ")
        + p.second;
      ui.m_view_visits_dialog->addWidget(new Wt::WLabel(s.c_str()));
      ui.m_view_visits_dialog->addWidget(new Wt::WBreak);
    }
  );
}

Wt::WWidget * ribi::ToolTestEntrance::WtMainDialog::CreateNewWelcomeDialog()
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Welcome",dialog);
  {
    const std::string s = WtEntrance::Get()->GetName(m_ip_address.get());
    ui.m_edit->setText(s.c_str());
    ui.m_edit->keyWentUp().connect(this,&ribi::ToolTestEntrance::WtMainDialog::OnEditChanged);
    dialog->addWidget(ui.m_edit);
  }
  return dialog;
}

void ribi::ToolTestEntrance::WtMainDialog::OnEditChanged()
{
  std::string s = ui.m_edit->text().toUTF8();
  std::replace(s.begin(),s.end(),',',' ');
  s = boost::algorithm::trim_copy(s);
  if (s.empty()) return;
  WtEntrance::Get()->SetName(m_ip_address.get(),s);
  OnNewName();
}
