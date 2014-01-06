//---------------------------------------------------------------------------
/*
QtHideAndShowDialog, Qt dialog to display children modally while hidden
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtHideAndShowDialog.htm
//---------------------------------------------------------------------------
#ifndef QTHIDEANDSHOWDIALOG_H
#define QTHIDEANDSHOWDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace ribi {

///Dialog that lets parent dialog display children dialogs while being hidden
///from http://richelbilderbeek.nl/CppQtHideAndShowDialog.htm
class QtHideAndShowDialog : public QDialog
{
    Q_OBJECT
    
public:
  explicit QtHideAndShowDialog(QWidget* parent = 0) noexcept;

  ///Virtual destructor as this is a base class
  virtual ~QtHideAndShowDialog() noexcept {}

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Hide the parent, show a child, show the parent
  void ShowChild(QtHideAndShowDialog * const dialog);

  ///Disable the parent, show a child, enable the parent
  void ShowModal(QtHideAndShowDialog * const dialog);

protected:
  ///Shows a child until it emits a close_me signal
  bool m_show_child;

  ///closeEvent that emits the close_me signal
  void closeEvent(QCloseEvent *);

  ///Close on escape key
  virtual void keyPressEvent(QKeyEvent* event);

signals:
  ///Emit the closeEvent of this dialog
  void close_me();

protected slots:
  ///Slot that needs to be called when a child signals close_me
  void close_child();

};

} //~namespace ribi

#endif // QTHIDEANDSHOWDIALOG_H
