//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2012  Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrubiksclockmaindialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "ui_qtrubiksclockmaindialog.h"

QtRubiksClockMainDialog::QtRubiksClockMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRubiksClockMainDialog)
{
  ui->setupUi(this);

  for (int i=0; i!=10000; ++i)
  {
    const int x = (std::rand() >> 4);
    switch (x % 8)
    {
      case 0: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(RubiksClock::topLeft); break;
      case 1: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(RubiksClock::topRight); break;
      case 2: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(RubiksClock::bottomLeft); break;
      case 3: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(RubiksClock::bottomRight); break;
      case 4: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(RubiksClock::topLeft,(x >> 4) % 11); break;
      case 5: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(RubiksClock::topRight,(x >> 4) % 11); break;
      case 6: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(RubiksClock::bottomLeft,(x >> 4) % 11); break;
      case 7: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(RubiksClock::bottomRight,(x >> 4) % 11); break;
    }
  }

}

QtRubiksClockMainDialog::~QtRubiksClockMainDialog()
{
  delete ui;
}

void QtRubiksClockMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void QtRubiksClockMainDialog::on_button_flip_clicked()
{
  ui->clock->GetWidget()->Flip();
}

void QtRubiksClockMainDialog::resizeEvent(QResizeEvent *)
{
  //const QRectF r(ui->widget_hold_clock->geometry().adjusted(0.0,0.0,-16.0,-16.0));
  const QRectF r(ui->clock->geometry());
  ui->clock->GetWidget()->SetGeometry(Rect(r.x(),r.y(),r.width(),r.height()));
}
