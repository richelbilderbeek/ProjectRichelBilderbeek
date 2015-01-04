//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#ifndef QTCREATEQTPROJECTZIPFILEMAINDIALOG_H
#define QTCREATEQTPROJECTZIPFILEMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtCreateQtProjectZipFileMainDialog;
}

namespace ribi {

class QtCreateQtProjectZipFileMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCreateQtProjectZipFileMainDialog(QWidget *parent = 0) noexcept;
  QtCreateQtProjectZipFileMainDialog(const QtCreateQtProjectZipFileMainDialog&) = delete;
  QtCreateQtProjectZipFileMainDialog& operator=(const QtCreateQtProjectZipFileMainDialog&) = delete;
  ~QtCreateQtProjectZipFileMainDialog() noexcept;


private slots:
  void on_lineEdit_textChanged(const QString &arg1) noexcept;

private:
  Ui::QtCreateQtProjectZipFileMainDialog *ui;

  ///Create a script from a valid folder
  void CreateScript(const std::string source_folder) noexcept;

  void keyPressEvent(QKeyEvent *) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTCREATEQTPROJECTZIPFILEMAINDIALOG_H
