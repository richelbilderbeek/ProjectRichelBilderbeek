//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtboenkenpresskeydialog.h"

#include <cassert>

#include <QKeyEvent>

#include "ui_qtboenkenpresskeydialog.h"
#pragma GCC diagnostic pop

ribi::QtBoenkenPressKeyDialog::QtBoenkenPressKeyDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtBoenkenPressKeyDialog),
  m_key(0)
{
  ui->setupUi(this);
}

ribi::QtBoenkenPressKeyDialog::~QtBoenkenPressKeyDialog() noexcept
{
  delete ui;
}

void ribi::QtBoenkenPressKeyDialog::keyPressEvent(QKeyEvent * e)
{
  //According to the Qt doc, the assert below is always true
  assert(e->type() == QEvent::KeyPress);
  m_key = e->key();
  close();
}
