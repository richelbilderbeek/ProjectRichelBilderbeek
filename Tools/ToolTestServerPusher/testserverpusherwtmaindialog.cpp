//---------------------------------------------------------------------------
/*
TestServerPusher, tool to test WtServerPusher
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestServerPusher.htm
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
//---------------------------------------------------------------------------
#include "testserverpusherdata.h"
#include "testserverpushermenudialog.h"
#include "testserverpusherwtmaindialog.h"
#include "wtserverpusher.h"
#include "wtaboutdialog.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
ribi::ToolTestServerPusher::WtMainDialog::WtMainDialog()
  : ui{}
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  ui.m_edit = new Wt::WLineEdit(this);
  ui.m_edit->keyWentUp().connect(this,&ribi::ToolTestServerPusher::WtMainDialog::OnEditChanged);
  ui.m_edit->setMinimumSize(400,Wt::WLength::Auto);
  OnServerPush();
}
//---------------------------------------------------------------------------
void ribi::ToolTestServerPusher::WtMainDialog::OnEditChanged()
{
  const std::string s = ui.m_edit->text().toUTF8();
  const std::string t = ToolTestServerPusher::Data::GetInstance()->GetData();
  if (s!=t)
  {
    ToolTestServerPusher::Data::GetInstance()->SetData(s);
    WtServerPusher::GetInstance()->Post();
  }
}
//---------------------------------------------------------------------------
void ribi::ToolTestServerPusher::WtMainDialog::OnServerPush()
{
  ui.m_edit->setText(ToolTestServerPusher::Data::GetInstance()->GetData());
}
//---------------------------------------------------------------------------
