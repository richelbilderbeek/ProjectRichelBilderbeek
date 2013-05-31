//---------------------------------------------------------------------------
/*
HtmlValidator, tool to validate all HTML files in a folder
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHtmlValidator.htm
//---------------------------------------------------------------------------
#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H
//---------------------------------------------------------------------------
#include <ctime>
#include <string>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogMain;
}
//---------------------------------------------------------------------------
class DialogMain : public QDialog
{
  Q_OBJECT

public:
  explicit DialogMain(QWidget *parent = 0);
  ~DialogMain();
  static const std::string GetVersion() { return "1.0"; }

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogMain *ui;
  const boost::shared_ptr<QTimer> m_timer;
  std::vector<std::string> m_files_correct;
  std::vector<std::string> m_files_incorrect;
  std::vector<std::string> m_files_to_check;
  static const std::string GetFilesCorrectFilename() { return "correct.txt"; }
  static const std::string GetFilesIncorrectFilename() { return "incorrect.txt"; }

private slots:
  void OnAbout();
  void OnEditChange();
  void OnStart();
  void OnTick();
};
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName);
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> GetFilesInFolder(const std::string& folder);
//---------------------------------------------------------------------------
///GetHtmlFilesInFolder returns the filenames of *.htm and *.html
///in folder given.
///From http://www.richelbilderbeek.nl/CppGetHtmlFilesInFolder.htm
const std::vector<std::string> GetHtmlFilesInFolder(const std::string& folder);
//---------------------------------------------------------------------------
///GetLastModifiedTime returns the last time when a file is modified.
///From http://www.richelbilderbeek.nl/CppGetLastModifiedTime.htm
std::time_t GetLastModifiedTime(const std::string& filename);
//---------------------------------------------------------------------------
///IsValidHtml returns is a certain HTML file is valid HTML
///From http://www.richelbilderbeek.nl/CppIsValidHtml.htm
bool IsValidHtml(const std::string& filename);
//---------------------------------------------------------------------------
///TimeToStr converts std::time_t to std::string.
///From http://www.richelbilderbeek.nl/CppTimeToStr.htm
const std::string TimeToStr(const std::time_t& time);
//---------------------------------------------------------------------------
#endif // DIALOGMAIN_H
