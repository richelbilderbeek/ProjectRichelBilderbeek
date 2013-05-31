//---------------------------------------------------------------------------
/*
QmakeWatcher, tool to watch qmake's .pro to Makefile conversion
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
//From http://www.richelbilderbeek.nl/ToolQmakeWatcher.htm
//---------------------------------------------------------------------------
#ifndef QTQMAKEWATCHERMAINDIALOG_H
#define QTQMAKEWATCHERMAINDIALOG_H

#include <string>
#include <vector>

#include <QDialog>

namespace Ui {
  class QtQmakeWatcherMainDialog;
}

class QtQmakeWatcherMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtQmakeWatcherMainDialog(QWidget *parent = 0);
  ~QtQmakeWatcherMainDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtQmakeWatcherMainDialog *ui;

private slots:
  void OnQmake();

  //From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& fileName);

};

#endif // QTQMAKEWATCHERMAINDIALOG_H
