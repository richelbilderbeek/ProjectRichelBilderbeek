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
#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
//---------------------------------------------------------------------------
#include <QFile>
#include <QTimer>
//---------------------------------------------------------------------------
#include "dialogabout.h"
#include "dialogmain.h"
#include "ui_dialogmain.h"
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void SaveContainer(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<typename Container::value_type>(f,"\n"));
}
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::DialogMain),
    m_timer(new QTimer)
{
  ui->setupUi(this);
  QObject::connect(ui->button_about,SIGNAL(clicked()),
    this,SLOT(OnAbout()));
  QObject::connect(ui->edit_path,SIGNAL(textChanged(QString)),
    this,SLOT(OnEditChange()));
  QObject::connect(ui->button_start,SIGNAL(clicked()),
    this,SLOT(OnStart()));
  QObject::connect(m_timer.get(),SIGNAL(timeout()),
    this,SLOT(OnTick()));


  //Set timer interval to 10 seconds or 5 minutes
  #ifndef NDEBUG
  m_timer->setInterval(1000);
  #else
  m_timer->setInterval(300000);
  #endif

  if (boost::filesystem::exists("correct.txt"))
  {
    std::vector<std::string> m_files_correct
      = FileToVector("correct.txt");
  }
  if (boost::filesystem::exists("incorrect.txt"))
  {
    std::vector<std::string> m_files_incorrect
      = FileToVector("incorrect.txt");
  }


  //this->resize(this->size());
  this->OnEditChange();
}
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
void DialogMain::OnAbout()
{
  DialogAbout d;
  d.exec();
}
//---------------------------------------------------------------------------
void DialogMain::OnEditChange()
{
  ui->button_start->setEnabled(false);

  const std::string path = ui->edit_path->text().toStdString();
  std::clog << "Path: " << path << '\n';
  m_files_to_check = GetHtmlFilesInFolder(path);
  //std::sort(m_files.begin(),m_files.end());

  std::clog << "Number of HTML files found to check: " << m_files_to_check.size() << '\n';
  if (! m_files_to_check.empty())
    ui->button_start->setEnabled(true);
}
//---------------------------------------------------------------------------
void DialogMain::OnStart()
{
  if (m_timer->isActive())
  {
    m_timer->stop();
    std::clog << "Timer stopped\n";
  }
  else
  {
    m_timer->start();
    std::clog << "Timer started\n";
  }
}
//---------------------------------------------------------------------------
void DialogMain::OnTick()
{
  if (m_files_to_check.empty()) return;
  const std::string f = m_files_to_check.back();
  std::clog << "Checking file " << f << '\n';
  assert(boost::filesystem::exists(f));
  m_files_to_check.pop_back();

  //s is the search string
  const std::string s = f + std::string(" ") + TimeToStr(GetLastModifiedTime(f));

  //Check if file was already validates as correct
  if ( std::find(m_files_correct.begin(),m_files_correct.begin(),s)
    != m_files_correct.end())
  {
    //File is unchanged and validated as correct
    return;
  }

  //Check if file was already validates as correct
  if ( std::find(m_files_incorrect.begin(),m_files_incorrect.begin(),s)
    != m_files_incorrect.end())
  {
    //File is unchanged and known to be incorrect
    ui->text->appendHtml("Invalid (known): " + QString(f.c_str()));
    return;
  }
  if (IsValidHtml(f))
  {
    m_files_correct.push_back(f);
    SaveContainer(m_files_correct,GetFilesCorrectFilename());
    //File is new and found out to be valid
    ui->text->appendHtml("Valid (new): " + QString(f.c_str()));
  }
  else
  {
    m_files_incorrect.push_back(f);
    SaveContainer(m_files_incorrect,GetFilesIncorrectFilename());
    //File is new and found out to be invalid
    ui->text->appendHtml("Invalid (new): " + QString(f.c_str()));
  }
  if (m_files_to_check.empty()) ui->label_out->setText("Done");
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
{
  assert(QFile::exists(fileName.c_str()));
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> GetFilesInFolder(const std::string& folder)
{
  std::vector<std::string> v;

  const boost::filesystem::path my_folder
    = boost::filesystem::system_complete(
        boost::filesystem::path(folder));

  if (!boost::filesystem::is_directory(my_folder)) return v;

  const boost::filesystem::directory_iterator j;
  for ( boost::filesystem::directory_iterator i(my_folder);
        i != j;
        ++i)
  {
    if ( boost::filesystem::is_regular_file( i->status() ) )
    {
      const std::string filename = i->path().filename().string();
      //const std::string full_filename = folder + "/" + filename;
      v.push_back(filename);
    }
  }
  return v;
}
//---------------------------------------------------------------------------
///GetHtmlFilesInFolder returns the filenames of *.htm and *.html
///in folder given.
///From http://www.richelbilderbeek.nl/CppGetHtmlFilesInFolder.htm
const std::vector<std::string> GetHtmlFilesInFolder(const std::string& folder)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a correct HTML filename
  const boost::regex html_file_regex(".*\\.(html|htm)\\z");

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  BOOST_FOREACH(const std::string& s, v)
  {
    if (boost::regex_match(s,html_file_regex)) w.push_back(s);
  }
  return w;
}
//---------------------------------------------------------------------------
///GetLastModifiedTime returns the last time when a file is modified.
///From http://www.richelbilderbeek.nl/CppGetLastModifiedTime.htm
std::time_t GetLastModifiedTime(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  return boost::filesystem::last_write_time(filename);
}
//---------------------------------------------------------------------------
///IsValidHtml returns is a certain HTML file is valid HTML
///From http://www.richelbilderbeek.nl/CppIsValidHtml.htm
bool IsValidHtml(const std::string& filename)
{
  #ifndef NDEBUG
  return (std::rand() >> 4) % 2;
  #endif

  assert(boost::filesystem::exists((filename)));
  const std::string command
    = "surfraw -t w3html http://www.richelbilderbeek.nl/"
    + filename + " > output.txt";
  std::clog << "Issuing command " << command << '\n';
  std::system(command.c_str());

  //Read output file
  const std::vector<std::string> result = FileToVector("output.txt");
  if (result.size() > 5)
  {
    if (result[5].find("Congratulations")!=std::string::npos)
    {
      return true;
    }
    std::clog << "[5] " << result[5] << '\n';
  }
  else
  {
    std::clog << "[5] does not exist\n";
  }
  return false;
}
//---------------------------------------------------------------------------
///TimeToStr converts std::time_t to std::string.
///From http://www.richelbilderbeek.nl/CppTimeToStr.htm
const std::string TimeToStr(const std::time_t& time)
{
  return std::ctime( &time);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
