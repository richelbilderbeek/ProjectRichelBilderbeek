//---------------------------------------------------------------------------
/*
QtHideAndShowDialog, Qt dialog to display children modally while hidden
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
//From http://www.richelbilderbeek.nl/CppQtHideAndShowDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"

#include <cassert>
#include <QKeyEvent>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtHideAndShowDialog::QtHideAndShowDialog(QWidget* parent) noexcept
  : QDialog(parent),
    m_show_child { false }
{

}

//ribi::QtHideAndShowDialog::~QtHideAndShowDialog() noexcept
//{
//
//}

void ribi::QtHideAndShowDialog::close_child()
{
  m_show_child = false;
}

void ribi::QtHideAndShowDialog::closeEvent(QCloseEvent*)
{
  //QDialog::closeEvent(event); //Not needed
  emit close_me();
  //QDialog::closeEvent(event); //Not needed
}

std::string ribi::QtHideAndShowDialog::GetVersion() noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::QtHideAndShowDialog::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2012-11-13: version 1.0: initial version",
    "2012-11-18: version 1.1: added ShowModal member function",
    "2012-11-18: version 1.2: added ",
    "2012-12-31: version 1.3: added keyPressEvent to close on escape"
    "2013-09-16: version 1.4: noexcept"
  };
  return v;
}

void ribi::QtHideAndShowDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
  QDialog::keyPressEvent(event);
}

void ribi::QtHideAndShowDialog::ShowChild(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->hide();
  QObject::connect(dialog,&ribi::QtHideAndShowDialog::close_me,this,&ribi::QtHideAndShowDialog::close_child);
  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
  }
  this->show();
}

void ribi::QtHideAndShowDialog::ShowModal(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->setEnabled(false);
  QObject::connect(dialog,&ribi::QtHideAndShowDialog::close_me,this,&ribi::QtHideAndShowDialog::close_child);
  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
  }
  this->setEnabled(true);
}
