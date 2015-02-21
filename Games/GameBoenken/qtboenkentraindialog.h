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
#ifndef QTBOENKENTRAINDIALOG_H
#define QTBOENKENTRAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenTrainDialog;
}

namespace ribi {

class QtBoenkenTrainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenTrainDialog(QWidget *parent = 0);
  QtBoenkenTrainDialog(const QtBoenkenTrainDialog&) = delete;
  QtBoenkenTrainDialog& operator=(const QtBoenkenTrainDialog&) = delete;
  ~QtBoenkenTrainDialog() noexcept;

private:
  Ui::QtBoenkenTrainDialog *ui;
};

} //~namespace ribi

#endif // QTBOENKENTRAINDIALOG_H
