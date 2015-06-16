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
#ifndef QTPVDBSTUDENTMENUDIALOG_H
#define QTPVDBSTUDENTMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbStudentMenuDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbStudentMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbStudentMenuDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  QtPvdbStudentMenuDialog(const QtPvdbStudentMenuDialog&) = delete;
  QtPvdbStudentMenuDialog& operator=(const QtPvdbStudentMenuDialog&) = delete;
  ~QtPvdbStudentMenuDialog() noexcept;

  ///Get the student his/her name
  std::string GetName() const noexcept;

  ///Save to file
  void Save(const std::string& filename) const;

  ///Set the student his/her name
  void SetName(const std::string& name);

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

  void on_edit_name_textChanged(const QString &arg1);

  void on_button_save_clicked();

private:
  Ui::QtPvdbStudentMenuDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBSTUDENTMENUDIALOG_H
