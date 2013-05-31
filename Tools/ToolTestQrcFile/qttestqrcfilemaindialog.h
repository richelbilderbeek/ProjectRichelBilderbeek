//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQRCFILEMAINDIALOG_H
#define QTTESTQRCFILEMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtTestQrcFileMainDialog;
}

class QtTestQrcFileMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQrcFileMainDialog(QWidget *parent = 0);
  ~QtTestQrcFileMainDialog();

private slots:
  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtTestQrcFileMainDialog *ui;
};

#endif // QTTESTQRCFILEMAINDIALOG_H
