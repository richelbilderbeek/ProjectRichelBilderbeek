//---------------------------------------------------------------------------
/*
WtQuestionDialog, Wt dialog for QuestionDialog
Copyright (C) 2011-2015 Richel Bilderbeek

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
#include "wtquestiondialog.h"


ribi::WtQuestionDialog::WtQuestionDialog()
  : m_signal_submitted{}
{

}

std::string ribi::WtQuestionDialog::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::WtQuestionDialog::GetVersionHistory()
{
  return {
    "2011-06-30: version 1.0: initial version"
  };
}


