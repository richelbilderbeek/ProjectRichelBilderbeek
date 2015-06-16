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
#ifndef QTPVDBMENUDIALOG_H
#define QTPVDBMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbMenuDialog; }

namespace ribi {

namespace pvdb {

class QtPvdbMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbMenuDialog(QWidget* parent = 0);
  QtPvdbMenuDialog(const QtPvdbMenuDialog&) = delete;
  QtPvdbMenuDialog& operator=(const QtPvdbMenuDialog&) = delete;
  ~QtPvdbMenuDialog() noexcept;


  ///Test this class and all other QDialogs
  static void Test() noexcept;

public slots:
  void on_button_about_clicked() noexcept;
  void on_button_assessor_clicked() noexcept;
  void on_button_create_test_files_clicked() noexcept;
  void on_button_modify_stylesheet_clicked() noexcept;
  void on_button_overview_clicked() noexcept;
  void on_button_print_concept_map_clicked() noexcept;
  void on_button_print_rating_clicked() noexcept;
  void on_button_rate_concept_auto_clicked() noexcept;
  void on_button_rate_concept_clicked() noexcept;
  void on_button_rate_concept_map_clicked() noexcept;
  void on_button_rate_examples_clicked() noexcept;
  void on_button_rating_clicked() noexcept;
  void on_button_student_clicked() noexcept;
  void on_button_test_conceptmap_clicked();
  void on_button_test_arrowitems_clicked() noexcept;
  void on_button_test_cluster_clicked() noexcept;
  void on_button_test_conceptmaps_clicked();
  void on_button_test_create_sub_concept_map_clicked() noexcept;
  void on_button_test_qtroundededitrectitem_clicked() noexcept;
  void on_button_view_files_clicked() noexcept;

private slots:
  void keyPressEvent(QKeyEvent* e) noexcept;

  void on_button_test_qtroundedrectitem_clicked();

private:
  Ui::QtPvdbMenuDialog *ui;

  ///The file to work on
  boost::shared_ptr<pvdb::File> m_file;

  ///The mode at which the child dialogs are displayed
  bool m_show_child_dialogs_modal;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBMENUDIALOG_H
