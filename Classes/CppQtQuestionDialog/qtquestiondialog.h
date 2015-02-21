//---------------------------------------------------------------------------
/*
QtQuestionDialog, Qt dialog for QuestionDialog
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
//From http://www.richelbilderbeek.nl/CppQtQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QTQUESTIONDIALOG_H
#define QTQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Question;
struct QuestionDialog;

///Qt dialog for QuestionDialog
struct QtQuestionDialog : public QtHideAndShowDialog
{
  explicit QtQuestionDialog(QWidget *parent = 0);
  virtual ~QtQuestionDialog() noexcept {}

  virtual boost::shared_ptr<const QuestionDialog> GetDialog() const = 0;
  virtual void SetDialog(const boost::shared_ptr<QuestionDialog>& dialog) = 0;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // CPPQTQUESTIONDIALOG_H
