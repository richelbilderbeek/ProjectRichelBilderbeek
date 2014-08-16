//---------------------------------------------------------------------------
/*
WtSelectFileDialog, Wt dialog for selecting a file
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtSelectFileDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wtselectfiledialog.h"

#include <boost/xpressive/xpressive.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WSelectionBox>

#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

///The path this dialog starts at
std::string ribi::WtSelectFileDialog::m_path = "";

ribi::WtSelectFileDialog::Ui::Ui()
 : m_edit_filter(new Wt::WLineEdit(".*")),
   m_label_filter(new Wt::WLabel("File filter: ")),
   m_selection_box(new Wt::WSelectionBox)
{

}

ribi::WtSelectFileDialog::WtSelectFileDialog()
  : m_signal_selected{},
    m_ui{}
{
  assert(!m_path.empty()
    && "Path must be set from argv[0]:"
    && "ribi::WtSelectFileDialog::SetPath(boost::filesystem::path(argv[0]).parent_path().string());");
  clear();
  setContentAlignment(Wt::AlignCenter);

  this->addWidget(m_ui.m_selection_box);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_ui.m_label_filter);
  this->addWidget(m_ui.m_edit_filter);

  m_ui.m_edit_filter->changed().connect(this,
    &ribi::WtSelectFileDialog::OnUpdateDialog);
  m_ui.m_edit_filter->enterPressed().connect(this,
    &ribi::WtSelectFileDialog::OnUpdateDialog);
  m_ui.m_edit_filter->keyWentUp().connect(this,
    &ribi::WtSelectFileDialog::OnUpdateDialog);
  m_ui.m_selection_box->activated().connect(this,
    &ribi::WtSelectFileDialog::OnSelect);
  m_ui.m_selection_box->clicked().connect(this,
    &ribi::WtSelectFileDialog::OnSelect);
  m_ui.m_selection_box->doubleClicked().connect(this,
    &ribi::WtSelectFileDialog::OnSelect);
  m_ui.m_selection_box->setSelectionMode(Wt::SingleSelection);
  m_ui.m_selection_box->resize(400,Wt::WLength::Auto);
  OnUpdateDialog();
}

void ribi::WtSelectFileDialog::DoRefresh()
{
  OnUpdateDialog();
}

//const std::vector<std::string> ribi::WtSelectFileDialog::GetFilesInFolder(const std::string& folder)
//{
//  assert(!m_path.empty() && "Path must be set from argv[0]");
//  return fileio::FileIo().GetFilesInFolder(m_path);
//}

std::string ribi::WtSelectFileDialog::GetSelectedFile() const
{
  if (m_ui.m_selection_box->currentIndex() == -1) return std::string();
  return m_ui.m_selection_box->itemText(m_ui.m_selection_box->currentIndex()).toUTF8();
}

std::string ribi::WtSelectFileDialog::GetVersion()
{
  return "1.5";
}

std::vector<std::string> ribi::WtSelectFileDialog::GetVersionHistory()
{
  return {
    "2011-07-01: version 1.0: initial version",
    "2011-07-01: version 1.1: added support for setting the regex filter",
    "2011-07-03: version 1.2: added support for setting the regex filter to readonly",
    "2011-07-15: version 1.3: added GetPath method, removed \'Select\' Wt::WPushButton",
    "2011-10-16: version 1.4: put UI elements in Ui struct, added virtual SelectFiles method (for Hometrainer)",
    "2011-10-24: version 1.5: added DoRefresh method"
  };
}

void ribi::WtSelectFileDialog::OnUpdateDialog()
{
  m_ui.m_selection_box->clear();

  const std::vector<std::string> v = SelectFiles();

  for(const auto s: v)
  {
    m_ui.m_selection_box->addItem(s.c_str());
  }
}

void ribi::WtSelectFileDialog::OnSelect()
{
  if (m_ui.m_selection_box->currentIndex() == -1) return;
  m_signal_selected();
}

std::vector<std::string> ribi::WtSelectFileDialog::SelectFiles() const noexcept
{
  try
  {
    boost::xpressive::sregex::compile(m_ui.m_edit_filter->text().toUTF8());
  }
  catch(boost::xpressive::regex_error& e)
  {
    return std::vector<std::string>();
  }
  catch (...)
  {
    assert(!"Should not get here");
  }

  //Get all filenames
  const std::vector<std::string> v = fileio::FileIo().GetFilesInFolder(m_path);

  //Create the regex for a correct text file
  const boost::xpressive::sregex txt_file_regex
    = boost::xpressive::sregex::compile(m_ui.m_edit_filter->text().toUTF8());

  std::vector<std::string> w;
  //Copy_if(v.begin(),v.end(),
  //  std::back_inserter(w),
  //    boost::regex_match(boost::bind(boost::lambda::_1),txt_file_regex));

  //Copy all filenames matching the regex in the resulting std::vector
  for(const auto s: v)
  {
    if (boost::xpressive::regex_match(s,txt_file_regex))
    {
      w.push_back(s);
    }
  }

  std::sort(w.begin(),w.end());
  return w;
}

void ribi::WtSelectFileDialog::SetFilter(const std::string& filename_filter)
{
  m_ui.m_edit_filter->setText(filename_filter.c_str());
  OnUpdateDialog();
}

void ribi::WtSelectFileDialog::SetFilterReadOnly(const bool readonly)
{
  m_ui.m_edit_filter->setReadOnly(readonly);
}

void ribi::WtSelectFileDialog::SetPath(const std::string& path)
{
  m_path = path;
}

