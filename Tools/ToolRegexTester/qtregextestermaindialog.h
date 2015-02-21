//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
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
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#ifndef QTREGEXTESTERMAINDIALOG_H
#define QTREGEXTESTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtRegexTesterMainDialog;
}

namespace ribi {

struct RegexTesterMainDialog;

class QtRegexTesterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRegexTesterMainDialog(
  const boost::shared_ptr<RegexTesterMainDialog> dialog,
    QWidget *parent = 0);
  QtRegexTesterMainDialog(const QtRegexTesterMainDialog&) = delete;
  QtRegexTesterMainDialog& operator=(const QtRegexTesterMainDialog&) = delete;
  ~QtRegexTesterMainDialog() noexcept;

protected:


private:
  Ui::QtRegexTesterMainDialog *ui;

  const boost::shared_ptr<RegexTesterMainDialog> m_dialog;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onAnyChange();
};

} //~namespace ribi

#endif //QTREGEXTESTERMAINDIALOG_H
