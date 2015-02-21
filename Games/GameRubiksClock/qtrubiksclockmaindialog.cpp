//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrubiksclockmaindialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "trace.h"
#include "testtimer.h"
#include "ui_qtrubiksclockmaindialog.h"
#pragma GCC diagnostic pop

ribi::ruco::QtRubiksClockMainDialog::QtRubiksClockMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRubiksClockMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  for (int i=0; i!=10000; ++i)
  {
    const int x = (std::rand() >> 4);
    switch (x % 8)
    {
      case 0: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::topLeft); break;
      case 1: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::topRight); break;
      case 2: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::bottomLeft); break;
      case 3: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::bottomRight); break;
      case 4: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::topLeft,(x >> 4) % 11); break;
      case 5: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::topRight,(x >> 4) % 11); break;
      case 6: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::bottomLeft,(x >> 4) % 11); break;
      case 7: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::bottomRight,(x >> 4) % 11); break;
    }
  }
}

ribi::ruco::QtRubiksClockMainDialog::~QtRubiksClockMainDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::ruco::QtRubiksClockMainDialog::on_button_flip_clicked()
{
  ui->clock->GetWidget()->Flip();
}

void ribi::ruco::QtRubiksClockMainDialog::resizeEvent(QResizeEvent *)
{
  //const QRectF r(ui->widget_hold_clock->geometry().adjusted(0.0,0.0,-16.0,-16.0));
  const QRectF r(ui->clock->geometry());
  ui->clock->GetWidget()->SetGeometry(r.x(),r.y(),r.width(),r.height());
}

#ifndef NDEBUG
void ribi::ruco::QtRubiksClockMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
