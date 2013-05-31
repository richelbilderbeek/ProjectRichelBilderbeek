//---------------------------------------------------------------------------
/*
Rasper, Raspberry Pi GPIO web application controller
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRasper.htm
//---------------------------------------------------------------------------
#include <cassert>

#include <set>

//#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/numeric/conversion/cast.hpp>
#include <boost/lambda/lambda.hpp>


#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>

#include "raspberrypigpiopin.h"
#include "raspermenudialog.h"
#include "trace.h"
#include "wtrasperresources.h"
#include "wtaboutdialog.h"
#include "wtraspermaindialog.h"

namespace ToolRasper {


const std::vector<rpi::gpio::Pin> WtMainDialog::CreatePins()
{
  std::vector<rpi::gpio::Pin> v;
  for (int pin: rpi::gpio::Pin::CreatePinNumbers())
  {
    v.push_back(rpi::gpio::Pin(pin));
  }
  return v;
}

WtMainDialog::Ui::Ui()
{
  for (int i=0; i!=rpi::gpio::GetMaxPinNumber(); ++i)
  {
    Wt::WPushButton * const button
      = new Wt::WPushButton;
    button->setText(".");
    m_buttons.push_back(button);
  }
}

WtMainDialog::WtMainDialog()
  : m_pins(CreatePins())
{
  this->setContentAlignment(Wt::AlignCenter);

  //-1 as buttons are human counted
  //const std::set<int> pins { 3,5,7,8,10,11,12,13,15,16,18,19,21,22,23,24,26 };

  ui.m_buttons[ 1-1]->setText("3v3");
  //ui.m_buttons[ 1-1]->setText("1");
  //ui.m_buttons[ 1-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick1);
  ui.m_buttons[ 2-1]->setText("5 V");
  //ui.m_buttons[ 2-1]->setText("2");
  //ui.m_buttons[ 2-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick2);
  ui.m_buttons[ 3-1]->setText("3");
  ui.m_buttons[ 3-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick3);
  ui.m_buttons[ 4-1]->setText("DNC");
  //ui.m_buttons[ 4-1]->setText("4");
  //ui.m_buttons[ 4-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick4);
  ui.m_buttons[ 5-1]->setText("5");
  ui.m_buttons[ 5-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick5);
  ui.m_buttons[ 6-1]->setText("DNC");
  //ui.m_buttons[ 6-1]->setText("6");
  //ui.m_buttons[ 6-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick6);
  ui.m_buttons[ 7-1]->setText("7");
  ui.m_buttons[ 7-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick7);
  ui.m_buttons[ 8-1]->setText("8");
  ui.m_buttons[ 8-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick8);
  ui.m_buttons[ 9-1]->setText("DNC");
  //ui.m_buttons[ 9-1]->setText("9");
  //ui.m_buttons[ 9-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick9);
  ui.m_buttons[10-1]->setText("10");
  ui.m_buttons[10-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick10);
  ui.m_buttons[11-1]->setText("11");
  ui.m_buttons[11-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick11);
  ui.m_buttons[12-1]->setText("12");
  ui.m_buttons[12-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick12);
  ui.m_buttons[13-1]->setText("13");
  ui.m_buttons[13-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick13);
  ui.m_buttons[14-1]->setText("DNC");
  //ui.m_buttons[14-1]->setText("14");
  //ui.m_buttons[14-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick14);
  ui.m_buttons[15-1]->setText("15");
  ui.m_buttons[15-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick15);
  ui.m_buttons[16-1]->setText("16");
  ui.m_buttons[16-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick16);
  ui.m_buttons[17-1]->setText("DNC");
  //ui.m_buttons[17-1]->setText("17");
  //ui.m_buttons[17-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick17);
  ui.m_buttons[18-1]->setText("18");
  ui.m_buttons[18-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick18);
  ui.m_buttons[19-1]->setText("19");
  ui.m_buttons[19-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick19);
  ui.m_buttons[20-1]->setText("DNC");
  //ui.m_buttons[20-1]->setText("20");
  //ui.m_buttons[20-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick20);
  ui.m_buttons[21-1]->setText("21");
  ui.m_buttons[21-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick21);
  ui.m_buttons[22-1]->setText("22");
  ui.m_buttons[22-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick22);
  ui.m_buttons[23-1]->setText("23");
  ui.m_buttons[23-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick23);
  ui.m_buttons[24-1]->setText("24");
  ui.m_buttons[24-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick24);
  ui.m_buttons[25-1]->setText("DNC");
  //ui.m_buttons[25-1]->setText("25");
  //ui.m_buttons[25-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick25);
  ui.m_buttons[26-1]->setText("26");
  ui.m_buttons[26-1]->clicked().connect(this,&ToolRasper::WtMainDialog::OnClick26);

  //Add buttons
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Control buttons",this);
    for (int i=0; i!=rpi::gpio::GetMaxPinNumber(); ++i)
    {
      const int row = 1 - (i / (rpi::gpio::GetMaxPinNumber() / 2));
      const int col = i % (rpi::gpio::GetMaxPinNumber() / 2);
      const int button_index = (col * 2) + row;
      box->addWidget(ui.m_buttons[button_index]);

      ui.m_buttons[i]->setMaximumSize(43,32);
      ui.m_buttons[i]->setMinimumSize(43,32);

      if (col == ((rpi::gpio::GetMaxPinNumber() / 2) - 1)) box->addWidget(new Wt::WBreak);
    }
  }
  this->addWidget(new Wt::WBreak);
  //Add images
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("GPIO pins layout",this);
    const WtResources w;
    box->addWidget(new Wt::WBreak);
    box->addWidget(new Wt::WImage(w.GetImageGpioFilename().c_str()));
    box->addWidget(new Wt::WBreak);
    box->addWidget(new Wt::WAnchor( WtResources().GetImageGpioSource(), WtResources().GetImageGpioAttribute()));
  }
  this->addWidget(new Wt::WBreak);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Raspberry Pi",this);
    const WtResources w;
    box->addWidget(new Wt::WImage(w.GetImageRaspberryPiTopFilename().c_str()));
    box->addWidget(new Wt::WBreak);
    box->addWidget(new Wt::WAnchor( WtResources().GetImageRaspberryPiTopSource(), WtResources().GetImageRaspberryPiTopAttribute()));
  }
}

void WtMainDialog::OnClick(const int pin_number)
{
  std::vector<rpi::gpio::Pin>::iterator iter = std::find_if(m_pins.begin(),m_pins.end(),
    [pin_number](const rpi::gpio::Pin& pin)
    {
      return pin.GetPinNumber() == pin_number;
    }
  );

  if (iter != m_pins.end())
  {
    (*iter).Toggle();
  }
}

} //namespace ToolRasper

