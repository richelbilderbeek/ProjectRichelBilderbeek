//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSMAINDIALOG
#define QTPYLOSMAINDIALOG
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <QDialog>

#include "qtpylosgamewidget.h"
//---------------------------------------------------------------------------
namespace Ui {
  class QtPylosMainDialog;
}
//---------------------------------------------------------------------------
class QtPylosMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtPylosMainDialog(
  QtPylosGameWidget * const pylos_widget = 0,
    QWidget *parent = 0);
  ~QtPylosMainDialog();

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtPylosMainDialog *ui;
  QtPylosGameWidget * const m_pylos_widget;

private slots:
  void OnWinner();
};
//---------------------------------------------------------------------------
#endif // QTPYLOSMAINDIALOG
