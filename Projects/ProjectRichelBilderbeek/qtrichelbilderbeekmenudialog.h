//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef QTRICHELBILDERBEEKMENUDIALOG_H
#define QTRICHELBILDERBEEKMENUDIALOG_H

#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/function.hpp>
#include "qthideandshowdialog.h"
#include "richelbilderbeekprogramtype.h"
#include "about.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtRichelBilderbeekMenuDialog;
}

namespace ribi {

struct ShinyButtonWidget;

class QtRichelBilderbeekMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRichelBilderbeekMenuDialog(QWidget *parent = 0);
  QtRichelBilderbeekMenuDialog(const QtRichelBilderbeekMenuDialog&) = delete;
  QtRichelBilderbeekMenuDialog& operator=(const QtRichelBilderbeekMenuDialog&) = delete;
  ~QtRichelBilderbeekMenuDialog() noexcept;

  static About GetAbout() noexcept;

private slots:
  void OnAbout();

private:
  Ui::QtRichelBilderbeekMenuDialog *ui;

  void keyPressEvent(QKeyEvent *);

  //void OnShow(const std::string text);
  void OnShow(const ProgramType program_type);


  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKMENUDIALOG_H
