//---------------------------------------------------------------------------
/*
Hometrainer, tool to make exercises and tests
Copyright (C) 2009-2011  Richl Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolHometrainer
//---------------------------------------------------------------------------
#include <stdexcept>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
#include <QFileDialog>
#include <QMessageBox>
//---------------------------------------------------------------------------
#include "menudialog.h"
#include "qtaboutdialog.h"
#include "qtmenudialog.h"
#include "qtquestionnairedialog.h"
#include "ui_qtmenudialog.h"
//---------------------------------------------------------------------------
QtMenuDialog::QtMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMenuDialog),
  m_dialog(new MenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtMenuDialog::~QtMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_load_exercise_clicked()
{
  const std::string file = QFileDialog::getOpenFileName(
    0,
    "Please select a hometrainer exercise file",
    QString(),
    "Text files (*.txt)").toStdString();

  //Respond to possibly incorrect parameter file
  try
  {
    m_dialog->OnButtonLoadClicked(file);
  }
  catch (std::runtime_error& e)
  {
     QMessageBox msgBox;
     msgBox.setText(e.what());
     msgBox.exec();
     return;
  }

  //Respond to possibly correct but empty parameter file
  if (m_dialog->GetQuestions().empty())
  {
    ui->button_start_exercise->setEnabled(false);
    return;
  }
  ui->button_start_exercise->setEnabled(true);
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_start_exercise_clicked()
{
  //
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_load_test_clicked()
{
  //
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_start_test_clicked()
{
  //
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_about_clicked()
{
 this->hide();
  About a = MenuDialog::GetAbout();
  //a.AddLibrary("QtLedDisplayWidget version: " + QtLedDisplayWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------

/*
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <assert>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "UnitMultipleChoiceQuestion.h"
#include "UnitOpenQuestion.h"
#include "UnitQuestion.h"
#include "UnitFormMenu.h"
#include "UnitFormMain.h"
#include "UnitFormAbout.h"
#include "UnitEncranger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
//---------------------------------------------------------------------------
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
 : TForm(Owner),
   signature("Hometrainer2 (C) 2009 Richel Bilderbeek"),
   m_key(0)
{
  RandomizeTimer();

  assert(GetPath("f.txt")=="f.txt");
  assert(GetPath("C:\\f.txt")=="C:");
  assert(GetPath("C:\\games\\f.txt")=="C:\\games");

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageStartExerciseClick(TObject *Sender)
{
  const std::string username = "";
  const int key = 0;
  assert(m_questions.empty() == false);
  boost::shared_ptr<TFormMain> f(new TFormMain(0,m_questions,false,key,username,"no_file.txt"));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageStartTestClick(TObject *Sender)
{
//  //Ask name
  String username_Vcl = "";
  const bool inputGiven = InputQuery(
    "Hometrainer2",
    "Please enter your full name",
    username_Vcl);
  if (!inputGiven) return;

  const std::string username = username_Vcl.c_str();

  SaveDialog1->FileName = String(username.c_str()) + ".txt";
  if (!SaveDialog1->Execute()) return;
  const std::string path = GetPath(SaveDialog1->FileName.c_str());
  const std::string filename = path + "\\" + username + ".txt";


  assert(m_questions.empty() == false);
  boost::shared_ptr<TFormMain> f(new TFormMain(0,m_questions,true,m_key,username,filename));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageLoadTestClick(TObject *Sender)
{
  //Ask for file
  if (!OpenDialog->Execute()) return;

  //Ask for key
  String userInput = "0";
  const bool inputGiven = InputQuery(
    "Hometrainer 2", //The caption of the InputBox
    "What is the encryption key?",
    userInput);

  if (!inputGiven) return;

  const int key_user = userInput.ToInt();

  boost::shared_ptr<TStringList> s(new TStringList);
  s->LoadFromFile(OpenDialog->FileName);

  const std::string path = GetPath(OpenDialog->FileName.c_str());

  if (s->Count == 0)
  {
    MessageDlg("File is empty and cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }
  if (s->Count == 1)
  {
    MessageDlg("File has only one line and thus cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }

  //Deencrypt file
  {
    //Need of new TStringList, because TStringList::operator[]()
    //does not seem to support writing, use TStringList::Add() instead
    boost::shared_ptr<TStringList> s_new(new TStringList);

    Encranger e(key_user);
    const int sz = s->Count;
    for (int i=0; i!=sz; ++i)
    {
      const String s1 = s->operator [](i).c_str();
      const String s2 = e.Deencrypt(s1.c_str()).c_str();
      s_new->Add(s2);
    }
    //Overwrite old TStringList
    s = s_new;
  }

  if (s->Count > 1 && s->operator [](0) != signature)
  {
    //ShowMessage(s->operator [](0));
    MessageDlg("Incorrect key given, therefore test is not loaded.",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }

  //Parsing the questions
  m_questions.clear();
  assert(m_questions.empty() == true);

  const int sz = s->Count;
  for (int i=1; i!=sz; ++i) //1, because first line is signature
  {
    const std::string str_to_split_original = s->operator [](i).c_str();
    if (str_to_split_original.empty() == true) continue;

    //Replace \, by {comma}
    const std::string str_to_split = ReplaceAll(str_to_split_original,"\\,","{comma}");

    const std::string debug_output = "MyDebug:" + str_to_split;
    OutputDebugString(debug_output.c_str());
    const std::vector<std::string> v_original = SeperateString(str_to_split,",");

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> v = ReplaceAll(v_original,"{comma}",",");

    if (v.empty()==true) continue;

    const std::string& filename = path + '\\' + v[0];
    const std::string& question = v[1];
    const std::string& answer   = v[2];
    const std::vector<std::string> false_answers(&v[3],v.end());

    if (false_answers.empty())
    {
      //Open question
      const std::vector<std::string> answers(SeperateString(answer,"/"));
      boost::shared_ptr<Question> q(
        new OpenQuestion(filename,question,answers));
      m_questions.push_back(q);
    }
    else
    {
      //Multiple choice question
      boost::shared_ptr<Question> q(
        new MultipleChoiceQuestion(filename,question,answer,false_answers));
      m_questions.push_back(q);
    }
  }


  if (m_questions.empty() == false)
  {
    m_key = key_user;
    ImageStartTest->Visible = true;
  }
}
//---------------------------------------------------------------------------



*/
