//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
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
//From http://www.richelbilderbeek.nl/CppQtOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QTOPENQUESTIONDIALOG_H
#define QTOPENQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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
  ///Will throw if the QuestionDialog is not an OpenQuestionDialog
  //explicit QtOpenQuestionDialog(QWidget *parent = 0);
  QtOpenQuestionDialog(const QtOpenQuestionDialog&) = delete;
  QtOpenQuestionDialog& operator=(const QtOpenQuestionDialog&) = delete;
  ~QtOpenQuestionDialog() noexcept;

  boost::shared_ptr<const QuestionDialog> GetDialog() const;
  void SetDialog(const boost::shared_ptr<QuestionDialog>& dialog);

  void SetOpenQuestionDialog(const boost::shared_ptr<OpenQuestionDialog>& dialog) noexcept;


  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

private slots:
  void on_button_submit_clicked() noexcept;

  void on_edit_answer_textChanged(const QString &arg1);

private:
  Ui::QtOpenQuestionDialog *ui;
  boost::shared_ptr<OpenQuestionDialog> m_openquestiondialog;

  void OnOpenQuestionDialogChanged(OpenQuestionDialog * const open_question_dialog) noexcept;
  void OnOpenQuestionChanged(const boost::shared_ptr<OpenQuestion>& open_question) noexcept;
  void OnQuit() noexcept;
  void OnSubmit(const bool was_answer_correct) noexcept;
};

} //~namespace ribi

#endif // QTOPENQUESTIONDIALOG_H
