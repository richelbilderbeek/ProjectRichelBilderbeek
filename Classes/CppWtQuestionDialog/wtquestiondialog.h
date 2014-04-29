//---------------------------------------------------------------------------
/*
WtQuestionDialog, Wt dialog for QuestionDialog
Copyright (C) 2011-2014 Richel Bilderbeek

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct Question;
struct QuestionDialog;

///Qt dialog for QuestionDialog
struct WtQuestionDialog : public Wt::WContainerWidget
{
  explicit WtQuestionDialog();

  ///Obtain the dialog
  virtual boost::shared_ptr<const QuestionDialog> GetDialog() const noexcept = 0;

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///This signal is emitted when the client submits an answer, where
  ///the boolean indicates if a correct answer was given
  mutable boost::signals2::signal<void (bool)> m_signal_submitted;

  protected:
  virtual ~WtQuestionDialog() {}
};

} //~namespace ribi

#endif // WTQUESTIONDIALOG_H
