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

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <QDialog>

#include "questiondialog.h"
#include "qtquestiondialog.h"

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


  QtOpenQuestionDialog(
    const boost::shared_ptr<QuestionDialog>& dialog,
    QWidget *parent = 0);

  ~QtOpenQuestionDialog();

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  ///Set the Question
  void SetQuestion(const boost::shared_ptr<Question>& question);

private slots:
  void on_button_submit_clicked();

private:
  Ui::QtOpenQuestionDialog *ui;
  //boost::scoped_ptr<OpenQuestionDialog> m_dialog;
};

} //~namespace ribi

#endif // QTOPENQUESTIONDIALOG_H
