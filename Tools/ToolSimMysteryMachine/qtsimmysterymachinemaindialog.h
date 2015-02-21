//---------------------------------------------------------------------------
/*
SimMysteryMachine, simulator of my mystery machine
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
//From http://www.richelbilderbeek.nl/ToolSimMysteryMachine.htm
//---------------------------------------------------------------------------
#ifndef QTMYSTERYMACHINEDIALOG_H
#define QTMYSTERYMACHINEDIALOG_H

#include <boost/scoped_ptr.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimMysteryMachineMainDialog;
}

namespace ribi {

struct QtMysteryMachineWidget;

class QtSimMysteryMachineMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSimMysteryMachineMainDialog(QWidget *parent = 0) noexcept;
  QtSimMysteryMachineMainDialog(const QtSimMysteryMachineMainDialog&) = delete;
  QtSimMysteryMachineMainDialog& operator=(const QtSimMysteryMachineMainDialog&) = delete;
  ~QtSimMysteryMachineMainDialog() noexcept;

private:
  Ui::QtSimMysteryMachineMainDialog *ui;
  boost::scoped_ptr<QtMysteryMachineWidget> m_machine;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTMYSTERYMACHINEDIALOG_H
