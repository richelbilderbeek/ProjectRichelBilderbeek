//---------------------------------------------------------------------------
/*
TimePoll, time polling server
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
//From http://www.richelbilderbeek.nl/ToolTimePoll.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WRadioButton>

#include "timepolldata.h"
#include "wtaboutdialog.h"
#include "wtserverpusher.h"
#include "wttimepollmaindialog.h"
#pragma GCC diagnostic pop

ribi::ToolTimePoll::WtTimePollMainDialog::WtTimePollMainDialog()
  : ui{}
{
  ShowMain();
  OnServerPush();
  OnTimedServerPush();
}

void ribi::ToolTimePoll::WtTimePollMainDialog::ShowMain()
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Which option?",this);
    ui.m_group = new Wt::WButtonGroup(this);

    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("A", container);
      new Wt::WBreak(container);
      ui.m_group->addButton(button,0);
    }
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("B", container);
      new Wt::WBreak(container);
      ui.m_group->addButton(button,1);
    }
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("C", container);
      new Wt::WBreak(container);
      ui.m_group->addButton(button,2);
    }

    ui.m_group->checkedChanged().connect(
      this,&ribi::ToolTimePoll::WtTimePollMainDialog::OnChangeIndex);
  }
  //Faked chart
  {
    ui.m_label1 = new Wt::WLabel;
    ui.m_label2 = new Wt::WLabel;
    ui.m_label3 = new Wt::WLabel;
    //ui.m_chart = new Wt::Chart::WCartesianChart;

    this->addWidget(ui.m_label1);
    new Wt::WBreak(this);
    this->addWidget(ui.m_label2);
    new Wt::WBreak(this);
    this->addWidget(ui.m_label3);
    //new Wt::WBreak(this);
    //this->addWidget(ui.m_chart);

    ui.m_label1->setText("A: ? seconds, ? %");
    ui.m_label2->setText("B: ? seconds, ? %");
    ui.m_label3->setText("C: ? seconds, ? %");
    //ui.m_chart->setTitle("Choices in time");
    //ui.m_chart->setMinimumSize(400,400);
  }
}

///Send the new selected radio button's index
void ribi::ToolTimePoll::WtTimePollMainDialog::OnChangeIndex()
{
  ToolTimePoll::Data::GetInstance()->SetIndex(ui.m_group->selectedButtonIndex());
  WtServerPusher::GetInstance()->Post();
}

void ribi::ToolTimePoll::WtTimePollMainDialog::OnServerPush()
{
  //Only index has changed
  Data * const data = ToolTimePoll::Data::GetInstance();
  ui.m_group->setSelectedButtonIndex(data->GetIndex());
}

void ribi::ToolTimePoll::WtTimePollMainDialog::OnTimedServerPush()
{
  Data * const data = ToolTimePoll::Data::GetInstance();
  //Times have changed
  const std::vector<double> fractions = data->GetFractions();
  const std::vector<double> times = data->GetTimes();

  assert(fractions.size() == 3);
  assert(times.size() == 3);
  assert(ui.m_group);
  assert(ui.m_label1);
  assert(ui.m_label2);
  assert(ui.m_label3);

  ui.m_label1->setText(
    "A: "
    + boost::lexical_cast<std::string>(
        boost::numeric_cast<int>(
          times[0]))
    + " seconds, "
    + boost::lexical_cast<std::string>(
        boost::numeric_cast<int>(
          fractions[0] * 100.0))
    + "%"
    );
  ui.m_label2->setText(
    "B: "
    + boost::lexical_cast<std::string>(
        boost::numeric_cast<int>(
          times[1]))
    + " seconds, "
    + boost::lexical_cast<std::string>(
        boost::numeric_cast<int>(
          fractions[1] * 100.0))
    + "%"
    );
  ui.m_label3->setText(
    "C: "
    + boost::lexical_cast<std::string>(
        boost::numeric_cast<int>(
          times[2]))
    + " seconds, "
    + boost::lexical_cast<std::string>(
      boost::numeric_cast<int>(
        fractions[2] * 100.0))
    + "%"
    );
}

