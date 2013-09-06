//---------------------------------------------------------------------------
/*
WtQuestionDialog, Wt dialog for QuestionDialog
Copyright (C) 2011-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef WTQUESTIONDIALOG_H
#define WTQUESTIONDIALOG_H

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>

namespace ribi {

struct Question;
struct QuestionDialog;

///Qt dialog for QuestionDialog
struct WtQuestionDialog : public Wt::WContainerWidget
{
  explicit WtQuestionDialog(const boost::shared_ptr<QuestionDialog>& dialog);

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
  virtual ~WtQuestionDialog() {}

  boost::shared_ptr<QuestionDialog> m_dialog;
};

} //~namespace ribi

#endif // WTQUESTIONDIALOG_H
