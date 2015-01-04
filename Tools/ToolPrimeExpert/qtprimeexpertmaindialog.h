//---------------------------------------------------------------------------
/*
PrimeExpert, tool to test if a number is prime
Copyright (C) 2008-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPrimeExpert.htm
//---------------------------------------------------------------------------
#ifndef QTTOOLPRIMEEXPERTMAINDIALOG_H
#define QTTOOLPRIMEEXPERTMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#include <boost/scoped_ptr.hpp>
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolPrimeExpertMainDialog;
}

namespace ribi {

struct PrimeExpert;

class QtToolPrimeExpertMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolPrimeExpertMainDialog(QWidget *parent = 0);
  QtToolPrimeExpertMainDialog(const QtToolPrimeExpertMainDialog&) = delete;
  QtToolPrimeExpertMainDialog& operator=(const QtToolPrimeExpertMainDialog&) = delete;
  ~QtToolPrimeExpertMainDialog() noexcept;

private:
  Ui::QtToolPrimeExpertMainDialog *ui;
  boost::scoped_ptr<PrimeExpert> m_expert;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
    void on_edit_value_textChanged(QString );
};

} //~namespace ribi

#endif // QTTOOLPRIMEEXPERTMAINDIALOG_H

