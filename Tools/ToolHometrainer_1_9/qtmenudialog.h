//---------------------------------------------------------------------------
/*
Hometrainer, tool to make exercises and tests
Copyright (C) 2009-2011  Richl Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolHometrainer
//---------------------------------------------------------------------------
#ifndef QTMENUDIALOG_H
#define QTMENUDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
    class QtMenuDialog;
}
//---------------------------------------------------------------------------
struct MenuDialog;
//---------------------------------------------------------------------------
///Qt GUI of MenuDialog
class QtMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMenuDialog(QWidget *parent = 0);
  ~QtMenuDialog();

private slots:
  void on_button_load_exercise_clicked();
  void on_button_start_exercise_clicked();
  void on_button_load_test_clicked();
  void on_button_start_test_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtMenuDialog *ui;
  boost::scoped_ptr<MenuDialog> m_dialog;
};
//---------------------------------------------------------------------------
#endif // QTMENUDIALOG_H
