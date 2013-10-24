//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
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
//From http://www.richelbilderbeek.nl/CppQtOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QTOPENQUESTIONDIALOG_H
#define QTOPENQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "questiondialog.h"
#include "qtquestiondialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtOpenQuestionDialog;
}

namespace ribi {

struct Question;
struct OpenQuestion;
struct OpenQuestionDialog;

class QtOpenQuestionDialog : public QtQuestionDialog
{
  Q_OBJECT

public:
  explicit QtOpenQuestionDialog(QWidget *parent = 0);

  ///Will trrow if the QuestionDialog is not an OpenQuestionDialog
  explicit QtOpenQuestionDialog(
    const boost::shared_ptr<OpenQuestionDialog> dialog,
    QWidget *parent = 0);
  QtOpenQuestionDialog(const QtOpenQuestionDialog&) = delete;
  QtOpenQuestionDialog& operator=(const QtOpenQuestionDialog&) = delete;
  ~QtOpenQuestionDialog() noexcept;

  const boost::shared_ptr<const QuestionDialog> GetDialog() const;

  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the Question
  ///Will throw if the question type does not match the dialog its type
  //void SetQuestion(const boost::shared_ptr<const Question> question);

private slots:
  void on_button_submit_clicked() noexcept;

private:
  Ui::QtOpenQuestionDialog *ui;
  const boost::shared_ptr<OpenQuestionDialog> m_dialog;
};

} //~namespace ribi

#endif // QTOPENQUESTIONDIALOG_H
