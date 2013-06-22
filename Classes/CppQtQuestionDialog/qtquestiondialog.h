//---------------------------------------------------------------------------
/*
QtQuestionDialog, Qt dialog for QuestionDialog
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QTQUESTIONDIALOG_H
#define QTQUESTIONDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <QDialog>
struct Question;
struct QuestionDialog;

///Qt dialog for QuestionDialog
struct QtQuestionDialog : public QDialog
{
  explicit QtQuestionDialog(QWidget *parent = 0);

  virtual ~QtQuestionDialog() {}

  QtQuestionDialog(
    const boost::shared_ptr<QuestionDialog>& dialog,
    QWidget *parent = 0);

  ///Obtain a read-only pointer to the dialog
  const QuestionDialog * GetDialog() const { return m_dialog.get(); }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///This signal is emitted when the client submits an answer, where
  ///the boolean indicates if a correct answer was given
  mutable boost::signals2::signal<void (bool)> m_signal_submitted;

  protected:

  boost::shared_ptr<QuestionDialog> m_dialog;
};

#endif // CPPQTQUESTIONDIALOG_H
