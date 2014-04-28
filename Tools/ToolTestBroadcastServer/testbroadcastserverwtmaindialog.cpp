//---------------------------------------------------------------------------
/*
TestBroadcastServer, tool to test WtBroadcastServer
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm
//---------------------------------------------------------------------------
#include "testbroadcastserverwtmaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>

#include "testbroadcastservermenudialog.h"
#include "wtbroadcastserver.h"
#include "wtaboutdialog.h"
#pragma GCC diagnostic pop

ribi::ToolTestBroadcastServer::WtMainDialog::WtMainDialog()
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  ui.m_edit = new Wt::WLineEdit(this);
  ui.m_edit->keyWentUp().connect(this,&ribi::ToolTestBroadcastServer::WtMainDialog::OnEditChanged);
  ui.m_edit->setMinimumSize(400,Wt::WLength::Auto);
  UpdatePage();
}

void ribi::ToolTestBroadcastServer::WtMainDialog::OnEditChanged()
{
  WtBroadcastServer::GetInstance()->SetData(
    std::string(ui.m_edit->text().toUTF8()));
}

void ribi::ToolTestBroadcastServer::WtMainDialog::UpdatePage()
{
  boost::any any;
  WtBroadcastServer::GetInstance()->GetData(any);
  std::string text;
  try
  {
    text = boost::any_cast<std::string>(any);
  }
  catch (boost::bad_any_cast&)
  {
    text = "TestBroadcastServer";
  }
  ui.m_edit->setText(text.c_str());
}
