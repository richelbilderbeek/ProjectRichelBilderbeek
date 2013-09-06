//---------------------------------------------------------------------------
/*
TestTimedServerPusher, tool to test WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestTimedServerPusher.htm
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WText>
//---------------------------------------------------------------------------
#include "testtimedserverpusherdata.h"
#include "testtimedserverpushermenudialog.h"
#include "testtimedserverpusherwtmaindialog.h"
#include "wttimedserverpusher.h"
#include "wtaboutdialog.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
ribi::ToolTestTimedServerPusher::WtMainDialog::WtMainDialog()
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  ui.m_text= new Wt::WText(this);
  OnTimedServerPush();
}
//---------------------------------------------------------------------------
void ribi::ToolTestTimedServerPusher::WtMainDialog::OnTimedServerPush()
{
  ui.m_text->setText(ToolTestTimedServerPusher::Data::GetInstance()->GetData());

  if (std::rand() % 10)
  {
    const int new_interval = std::rand() % 5000;
    WtTimedServerPusher::GetInstance()->SetTime(new_interval);
    std::clog << "new_interval: " << new_interval << '\n';
  }
}
//---------------------------------------------------------------------------

