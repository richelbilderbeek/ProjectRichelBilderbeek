//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef QTASCIIARTERDIALOG_H
#define QTASCIIARTERDIALOG_H


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include "qthideandshowdialog.h"

#include "asciiartermaindialog.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtAsciiArterMainDialog;
}

struct QImage;

namespace ribi {

class QtAsciiArterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAsciiArterMainDialog(QWidget *parent = 0);
  QtAsciiArterMainDialog(const QtAsciiArterMainDialog&) = delete;
  QtAsciiArterMainDialog& operator=(const QtAsciiArterMainDialog&) = delete;
  ~QtAsciiArterMainDialog() noexcept;

  const std::string& GetFilename() const noexcept { return m_filename; }
  int GetWidth() const noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtAsciiArterMainDialog *ui;
  boost::scoped_ptr<AsciiArterMainDialog> m_dialog;
  std::string m_filename;
  void OnAnyChange();

private slots:
  void on_button_load_clicked();
  void on_box_width_valueChanged(int);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTASCIIARTERDIALOG_H
