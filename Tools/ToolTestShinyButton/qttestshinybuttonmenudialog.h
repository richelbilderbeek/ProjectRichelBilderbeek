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
#ifndef QTTESTSHINYBUTTONMENUDIALOG_H
#define QTTESTSHINYBUTTONMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestShinyButtonMenuDialog;
}

namespace ribi {

struct QtShinyButtonWidget;

class QtTestShinyButtonMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestShinyButtonMenuDialog(QWidget *parent = 0);
  QtTestShinyButtonMenuDialog(const QtTestShinyButtonMenuDialog&) = delete;
  QtTestShinyButtonMenuDialog& operator=(const QtTestShinyButtonMenuDialog&) = delete;
  ~QtTestShinyButtonMenuDialog() noexcept;

protected:
  

private:
  Ui::QtTestShinyButtonMenuDialog *ui;

  const boost::scoped_ptr<QtShinyButtonWidget> m_button_start;
  const boost::scoped_ptr<QtShinyButtonWidget> m_button_about;
  const boost::scoped_ptr<QtShinyButtonWidget> m_button_quit;
  void OnButtonStartClicked();
  void OnButtonAboutClicked();
  void OnButtonQuitClicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTSHINYBUTTONMENUDIALOG_H
