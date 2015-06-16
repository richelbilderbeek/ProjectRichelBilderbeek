//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef QTPVDBVIEWFILESDIALOG_H
#define QTPVDBVIEWFILESDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbViewFilesDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbViewFilesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewFilesDialog(QWidget* parent = 0);
  QtPvdbViewFilesDialog(const QtPvdbViewFilesDialog&) = delete;
  QtPvdbViewFilesDialog& operator=(const QtPvdbViewFilesDialog&) = delete;
  ~QtPvdbViewFilesDialog() noexcept;
  
private slots:
  void on_button_left_clicked();
  void keyPressEvent(QKeyEvent* event);
  void OnTimerLeft();
  void OnTimerRight();

  void on_button_right_clicked();

private:
  Ui::QtPvdbViewFilesDialog *ui;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBVIEWFILESDIALOG_H
