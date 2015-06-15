//---------------------------------------------------------------------------
/*
TestGroupWidget, tool to test the GroupWidget class
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
//From http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm
//---------------------------------------------------------------------------
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "wtgroupwidget.h"
#include "wttestgroupwidgetmaindialog.h"
#pragma GCC diagnostic pop

ribi::WtTestGroupWidgetMainDialog::Ui::Ui()
  : m_edit(new Wt::WLineEdit),
    m_widget(new WtGroupWidget)
{

}
//---------------------------------------------------------------------------
ribi::WtTestGroupWidgetMainDialog::WtTestGroupWidgetMainDialog()
  : ui{}
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_widget);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_edit);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Create random groups",this);
    button->clicked().connect(this,&ribi::WtTestGroupWidgetMainDialog::OnClicked);
  }

  ui.m_edit->resize(400,Wt::WLength::Auto);
  ui.m_edit->changed().connect(this,&ribi::WtTestGroupWidgetMainDialog::OnChanged);
  ui.m_edit->enterPressed().connect(this,&ribi::WtTestGroupWidgetMainDialog::OnChanged);
  ui.m_edit->setText("1|2,3|4,5,6|7,8,9,10");
  ui.m_widget->resize(400,400);

  this->OnChanged();
}
//---------------------------------------------------------------------------
void ribi::WtTestGroupWidgetMainDialog::OnChanged()
{
  const std::vector<std::string> groups_str
    = SeperateString(ui.m_edit->text().toUTF8(),'|');

  std::vector<std::vector<int> > groups_ids;

  BOOST_FOREACH(const std::string& group_str,groups_str)
  {
    const std::vector<std::string> ids_str
      = SeperateString(group_str,',');
    std::vector<int> ids;

    BOOST_FOREACH(const std::string& s,ids_str)
    {
      try
      {
        const int id = boost::lexical_cast<int>(s);
        ids.push_back(id);
      }
      catch (boost::bad_lexical_cast& e)
      {
        ui.m_widget->SetIds(groups_ids);
        return;
      }
    }
    groups_ids.push_back(ids);
  }
  ui.m_widget->SetIds(groups_ids);
}
//---------------------------------------------------------------------------
void ribi::WtTestGroupWidgetMainDialog::OnClicked()
{
  int id = 0;
  std::vector<std::vector<int> > v;
  const int n_groups = std::rand() % 20;
  for (int i=0; i!=n_groups; ++i)
  {
    std::vector<int> w;
    const int group_size = std::rand() % 20;
    for (int j=0; j!=group_size;++j)
    {
      w.push_back(id++);
    }
    v.push_back(w);
  }
  ui.m_widget->SetIds(v);
}
//---------------------------------------------------------------------------
const std::vector<std::string> ribi::WtTestGroupWidgetMainDialog::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}
//---------------------------------------------------------------------------
