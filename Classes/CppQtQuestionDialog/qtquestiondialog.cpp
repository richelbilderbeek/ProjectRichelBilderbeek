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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtquestiondialog.h"
#include "questiondialog.h"
#pragma GCC diagnostic pop


ribi::QtQuestionDialog::QtQuestionDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    m_dialog{}
{

}

ribi::QtQuestionDialog::QtQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    m_dialog(dialog)
{
  assert(m_dialog);
}

const std::string ribi::QtQuestionDialog::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::QtQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-30: version 1.0: initial version",
    "2013-10-23: version 1.1: moved m_signal_submitted to QuestionDialog"
  };
}


