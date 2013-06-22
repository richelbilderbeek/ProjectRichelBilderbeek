//---------------------------------------------------------------------------
/*
QtHideAndShowDialog, Qt dialog to display children modally while hidden
Copyright (C) 2012 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qthideandshowdialog.h"

#include <cassert>
#include <QKeyEvent>

#include "trace.h"

QtHideAndShowDialog::QtHideAndShowDialog(QWidget* parent)
  : QDialog(parent),
    m_show_child(false)
{
  TRACE_FUNC();
}

void QtHideAndShowDialog::close_child()
{
  m_show_child = false;
}

void QtHideAndShowDialog::closeEvent(QCloseEvent*)
{
  //QDialog::closeEvent(event); //Not needed
  emit close_me();
  //QDialog::closeEvent(event); //Not needed
}

const std::string QtHideAndShowDialog::GetVersion()
{
  return "1.3";
}

const std::vector<std::string> QtHideAndShowDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-11-13: version 1.0: initial version");
  v.push_back("2012-11-18: version 1.1: added ShowModal member function");
  v.push_back("2012-11-18: version 1.2: added #undef __STRICT_ANSI__");
  v.push_back("2012-12-31: version 1.3: added keyPressEvent to close on escape");
  return v;
}

void QtHideAndShowDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(event);
}

void QtHideAndShowDialog::ShowChild(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->hide();
  QObject::connect(dialog,SIGNAL(close_me()),this,SLOT(close_child()));
  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
  }
  this->show();
}

void QtHideAndShowDialog::ShowModal(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->setEnabled(false);
  QObject::connect(dialog,SIGNAL(close_me()),this,SLOT(close_child()));
  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
  }
  this->setEnabled(true);
}
