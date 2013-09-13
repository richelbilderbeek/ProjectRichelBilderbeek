//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTCREATORPROFILEMAINDIALOG_H
#define QTTESTQTCREATORPROFILEMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestQtCreatorProFileMainDialog;
}

namespace ribi {

class QtTestQtCreatorProFileMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtCreatorProFileMainDialog(QWidget *parent = 0);
  QtTestQtCreatorProFileMainDialog(const QtTestQtCreatorProFileMainDialog&) = delete;
  QtTestQtCreatorProFileMainDialog& operator=(const QtTestQtCreatorProFileMainDialog&) = delete;
  ~QtTestQtCreatorProFileMainDialog();

private slots:
  void on_button_select_clicked();

private:
  Ui::QtTestQtCreatorProFileMainDialog *ui;
};

} //~namespace ribi

#endif // QTTESTQTCREATORPROFILEMAINDIALOG_H
