//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#ifndef QTPICTOCODEDIALOG_H
#define QTPICTOCODEDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#include "pictocodemaindialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPicToCodeMainDialog;
}

struct QImage;

namespace ribi {

class QtPicToCodeMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPicToCodeMainDialog(QWidget *parent = 0);
  QtPicToCodeMainDialog(const QtPicToCodeMainDialog&) = delete;
  QtPicToCodeMainDialog& operator=(const QtPicToCodeMainDialog&) = delete;
  ~QtPicToCodeMainDialog() noexcept;

private:
  Ui::QtPicToCodeMainDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_convert_clicked();
  void on_button_select_file_clicked();

public:
  static const PicToCodeMainDialog::YxImage ImageToImage(const QImage& image);

  const std::vector<std::string>
    PicToNdsCode(const QImage& image) const;
  const std::vector<std::string>
    PicToQtCode(const QImage& image) const;
};

} //~namespace ribi

#endif // QTPICTOCODEDIALOG_H
