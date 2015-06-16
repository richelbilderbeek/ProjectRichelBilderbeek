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
#ifndef QTPVDBCLUSTERDIALOG_H
#define QTPVDBCLUSTERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtpvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbClusterDialog; }

namespace ribi {
namespace pvdb {

///The Dialog in which the user clusters concepts and examples
///If the file supplied has no cluster, this dialog creates a cluster
///because the widget needs something to work on
class QtPvdbClusterDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPvdbClusterDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  QtPvdbClusterDialog(const QtPvdbClusterDialog&) = delete;
  QtPvdbClusterDialog& operator=(const QtPvdbClusterDialog&) = delete;
  ~QtPvdbClusterDialog() noexcept;

  ///Do some random stuff, e.g. adding some concepts with examples
  void DoRandomStuff();

  ///Obtain the widget
  QtPvdbClusterWidget * GetWidget();
  const QtPvdbClusterWidget * GetWidget() const;

  ///Does the dialog want to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  //Save to disk
  void Save(const std::string& filename);


protected:
  ///Respond to the following keys:
  ///F2: edit current item
  ///Delete: remove current item
  ///CTRL-SHIFT-T: translate to English
  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_add_clicked();
  void on_button_next_clicked();
  void on_edit_textChanged(const QString &arg1);

  void on_button_save_clicked();

private:
  Ui::QtPvdbClusterDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  ///The file
  const boost::shared_ptr<pvdb::File> m_file;

  ///The cluster widget
  QtPvdbClusterWidget * const m_widget;

  ///Add a Cluster to the file if it is not yet present,
  ///Create a QtPvdbClusterWidget from the file its cluster
  static QtPvdbClusterWidget * BuildWidget(const boost::shared_ptr<pvdb::File> file);

  //Start saving procedure, with request of filename
  void Save();

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBCLUSTERDIALOG_H
