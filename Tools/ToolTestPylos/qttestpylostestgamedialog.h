//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPYLOSTESTGAMEDIALOG_H
#define QTTESTPYLOSTESTGAMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QLabel;
struct QTimer;

namespace Ui {
  class QtTestPylosTestGameDialog;
}


namespace ribi {
namespace pylos {

struct QtPylosGameWidget;

class QtTestPylosTestGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPylosTestGameDialog(QWidget *parent = 0);
  QtTestPylosTestGameDialog(const QtTestPylosTestGameDialog&) = delete;
  QtTestPylosTestGameDialog& operator=(const QtTestPylosTestGameDialog&) = delete;
  ~QtTestPylosTestGameDialog() noexcept;

protected:
  

private:
  Ui::QtTestPylosTestGameDialog *ui;
  boost::shared_ptr<QtPylosGameWidget> m_widget;
  QTimer * m_timer;

private slots:
  ///OnTimer is called when the auto-play/demo mode clicks randomly
  void OnTimer();

  ///When something changes, the log must be updated
  void UpdateLog();

  void on_button_play_visual_clicked();
  void on_radio_advanced_clicked();
  void on_radio_basic_clicked();
  void on_radio_bw_clicked();
  void on_radio_rb_clicked();

};

} //~namespace pylos
} //~namespace ribi

#endif // QTTESTPYLOSTESTGAMEDIALOG_H
