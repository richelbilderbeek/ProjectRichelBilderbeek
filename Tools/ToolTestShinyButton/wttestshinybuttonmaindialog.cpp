//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "rainbow.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "testshinybuttonmenudialog.h"
#include "wtaboutdialog.h"
#include "wtdialwidget.h"
#include "wtshinybuttonwidget.h"
#include "wttestshinybuttonmaindialog.h"
#pragma GCC diagnostic pop

ribi::WtTestShinyButtonMainDialog::Ui::Ui()
  : m_dial_color(new WtDialWidget),
    m_dial_gradient(new WtDialWidget),
    m_edit(new Wt::WLineEdit),
    m_label_color(new Wt::WLabel),
    m_shiny_button(new WtShinyButtonWidget(0.5,1.0))
{

}

ribi::WtTestShinyButtonMainDialog::WtTestShinyButtonMainDialog()
  : m_dialog(new TestShinyButtonMenuDialog),
    ui{}
{
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_shiny_button);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_label_color);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_edit);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WLabel("Change the shiny button its color:"));
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_dial_color);
  this->addWidget(ui.m_dial_gradient);

  ui.m_edit->setMinimumSize(400,Wt::WLength::Auto);
  ui.m_edit->keyWentUp().connect(this,&ribi::WtTestShinyButtonMainDialog::OnEditChanged);
  ui.m_shiny_button->GetWidget()->SetGeometry(0,0,200,100);

  ui.m_shiny_button->GetWidget()->GetShinyButton()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::WtTestShinyButtonMainDialog::OnShinyButtonColorChanged,
      this));

  ui.m_dial_color->GetWidget()->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::WtTestShinyButtonMainDialog::OnDialChanged,
      this));
  ui.m_dial_gradient->GetWidget()->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::WtTestShinyButtonMainDialog::OnDialChanged,
      this));

  ui.m_dial_color->GetWidget()->GetDial()->SetPosition(0.5);
  ui.m_dial_gradient->GetWidget()->GetDial()->SetPosition(0.5);
  ui.m_edit->setText("Welcome");
  OnEditChanged();
}

void ribi::WtTestShinyButtonMainDialog::OnDialChanged()
{
  const double c = ui.m_dial_color->GetWidget()->GetDial()->GetPosition();
  const double g = ui.m_dial_gradient->GetWidget()->GetDial()->GetPosition();

  ui.m_shiny_button->GetWidget()->GetShinyButton()->SetColor(c,g);
}

void ribi::WtTestShinyButtonMainDialog::OnEditChanged()
{
  const std::string s = ui.m_edit->text().toUTF8();

  ui.m_shiny_button->GetWidget()->GetShinyButton()->SetText(s);
}

void ribi::WtTestShinyButtonMainDialog::OnShinyButtonColorChanged()
{
  const double c = ui.m_shiny_button->GetWidget()->GetShinyButton()->GetColor();
  const double g = ui.m_shiny_button->GetWidget()->GetShinyButton()->GetGradient();

  const std::string text
    = std::string("Color: (")
    + boost::lexical_cast<std::string>(c)
    + std::string(",")
    + boost::lexical_cast<std::string>(g)
    + std::string(") (color,gradient)");
  ui.m_label_color->setText(text);
}

