//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtcreateqtprojectzipfilemaindialog.h"

#include <fstream>

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QMessageBox>

#include "createqtprojectzipfilemenudialog.h"
#include "createqtprojectzipfilemaindialog.h"
#include "fileio.h"
#include "qtcreatorprofilezipscript.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtcreateqtprojectzipfilemaindialog.h"

#pragma GCC diagnostic pop

ribi::QtCreateQtProjectZipFileMainDialog::QtCreateQtProjectZipFileMainDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtCreateQtProjectZipFileMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->lineEdit->setText("Tools/ToolCreateQtProjectZipFile");
}

ribi::QtCreateQtProjectZipFileMainDialog::~QtCreateQtProjectZipFileMainDialog() noexcept
{
  delete ui;
}

void ribi::QtCreateQtProjectZipFileMainDialog::CreateScript(const std::string source_folder) noexcept
{
  const std::string text = QtCreatorProFileZipScript::CreateScript(source_folder);
  ui->text->setPlainText(text.c_str());
}

void ribi::QtCreateQtProjectZipFileMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtCreateQtProjectZipFileMainDialog::on_lineEdit_textChanged(const QString &arg1) noexcept
{
  const std::string source_folder = "../../" + arg1.toStdString();

  if (!QFile::exists(source_folder.c_str()))
  {
    const std::string text = "Folder '" + source_folder + "' does not exist.";
    ui->text->setPlainText(text.c_str());
    return;
  }
  CreateScript(source_folder);
}

#ifndef NDEBUG
void ribi::QtCreateQtProjectZipFileMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const std::string pro_filename{"../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro"};
    const boost::shared_ptr<const QtCreatorProFile> pro_file(
      new QtCreatorProFile(pro_filename));
    assert(pro_file);
    assert(fileio::FileIo().IsRegularFile(pro_filename));
    const boost::shared_ptr<const QtCreatorProFileZipScript> script(
      new QtCreatorProFileZipScript(pro_file));
    assert(script);

  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test basic functions on this project with going two folders down
  const bool verbose{false};
  const std::vector<std::string> pro_filenames
    =
    {
      "../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro",
      "../../Tools/ToolCodeToHtml/ToolCodeToHtmlDesktop.pro",
      "../../Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro",
      "../../Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro"
    };
  const int n_tests = std::count_if(
    pro_filenames.begin(), pro_filenames.end(),
      [](const std::string& filename)
      { return fileio::FileIo().IsRegularFile(filename); }
    );
  if (verbose)
  {
    const std::string s = "Testing "
      + boost::lexical_cast<std::string>(n_tests)
      + " / "
      + boost::lexical_cast<std::string>(pro_filenames.size());
    TRACE(s);
  }
  for (const std::string& pro_filename: pro_filenames)
  {
    if (!fileio::FileIo().IsRegularFile(pro_filename)) continue;
    if (!fileio::FileIo().IsFolder(pro_filename)) continue;
    const CreateQtProjectZipFileMainDialog d(pro_filename);
    assert(!d.GetScript().empty());
  }

  for (const std::string& pro_filename: pro_filenames)
  {
    if (!fileio::FileIo().IsRegularFile(pro_filename)) continue;
    const boost::shared_ptr<const QtCreatorProFile> pro_file(
      new QtCreatorProFile(pro_filename));
    assert(pro_file);
    assert(fileio::FileIo().IsRegularFile(pro_filename));
    const boost::shared_ptr<const QtCreatorProFileZipScript> script(
      new QtCreatorProFileZipScript(pro_file));
    assert(script);
    std::stringstream s;
    s << (*script);
    assert(!s.str().empty());
  }
}
#endif

