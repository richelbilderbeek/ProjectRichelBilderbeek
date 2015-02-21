//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtshowwinnerdialog.h"
#include <QKeyEvent>
#include "ui_qtshowwinnerdialog.h"
#pragma GCC diagnostic pop

ribi::con3::QtShowWinnerDialog::QtShowWinnerDialog(
  const std::string& filename,
  const std::string& winner_text,
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtShowWinnerDialog)
{
  ui->setupUi(this);
  ui->label_image->setPixmap(QPixmap(filename.c_str()));
  ui->label_footer->setText(winner_text.c_str());
  ui->label_title->setText(winner_text.c_str());
  this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

ribi::con3::QtShowWinnerDialog::~QtShowWinnerDialog() noexcept
{
  delete ui;
}

void ribi::con3::QtShowWinnerDialog::keyPressEvent(QKeyEvent * e) noexcept
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
}
