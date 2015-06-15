//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2015  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameRubiksClock.htm
//---------------------------------------------------------------------------
#include "wtrubiksclockmaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>

#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WPushButton>

#include "dial.h"
#include "dialwidget.h"
#include "rubiksclock.h"
#include "rubiksclockwidget.h"
#include "widget.h"
#include "wtdialwidget.h"
#include "wtrubiksclockwidget.h"
#pragma GCC diagnostic pop

ribi::ruco::WtRubiksClockMainDialog::Ui::Ui()
  : m_button_flip(new Wt::WPushButton("Flip clock")),
    m_dial_size(new WtDialWidget),
    m_label_size(new Wt::WLabel),
    m_widget(new WtClockWidget)
{
}

ribi::ruco::WtRubiksClockMainDialog::WtRubiksClockMainDialog()
  : m_ui{}
{
  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_ui.m_widget);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_ui.m_button_flip);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_ui.m_label_size);
  this->addWidget(m_ui.m_dial_size);

  m_ui.m_button_flip->clicked().connect(
    this,
    &ribi::ruco::WtRubiksClockMainDialog::OnFlip);

  m_ui.m_dial_size->GetWidget()->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::ruco::WtRubiksClockMainDialog::OnSizeChanged,
      this));

  m_ui.m_dial_size->GetWidget()->SetGeometry(0,0,32,32);
  m_ui.m_label_size->setText("Size: ?x? (width x height)");
  m_ui.m_widget->GetWidget()->SetGeometry(0,0,300,300);

  m_ui.m_dial_size->GetWidget()->GetDial()->SetPosition(0.5);
}

void ribi::ruco::WtRubiksClockMainDialog::OnFlip()
{
  m_ui.m_widget->GetWidget()->Flip();
}

void ribi::ruco::WtRubiksClockMainDialog::OnSizeChanged()
{
  const int size = boost::numeric_cast<int>(
    500.0 * m_ui.m_dial_size->GetWidget()->GetDial()->GetPosition());
  m_ui.m_widget->GetWidget()->SetGeometry(0,0,size,size);
  std::string text
    = std::string("Size: ")
    + boost::lexical_cast<std::string>(size)
    + std::string("x")
    + boost::lexical_cast<std::string>(size)
    + std::string(" (width x height)");
  m_ui.m_label_size->setText(text.c_str());
}

