//---------------------------------------------------------------------------
/*
WtSelectFileDialog, Wt dialog for selecting a file
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
//From http://www.richelbilderbeek.nl/CppWtSelectFileDialog.htm
//---------------------------------------------------------------------------
#ifndef WTSELECTFILEDIALOG_H
#define WTSELECTFILEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt
{
  struct WLineEdit;
  struct WPushButton;
  struct WSelectionBox;
}


namespace ribi {

///WtSelectFileDialog is a Wt dialog to select a file
struct WtSelectFileDialog : public Wt::WContainerWidget
{
  WtSelectFileDialog();
  WtSelectFileDialog(const WtSelectFileDialog&) = delete;
  WtSelectFileDialog& operator=(const WtSelectFileDialog&) = delete;
  virtual ~WtSelectFileDialog() {}

  ///Check the folder for files again
  void DoRefresh();

  ///Get the path in which this class will look for files
  static const std::string& GetPath() { return m_path; }

  ///Get the currently selected file
  std::string GetSelectedFile() const;

  ///Get the version of this class
  static std::string GetVersion();

  ///Get the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Set the regex filter filenames are selected for
  void SetFilter(const std::string& filename_filter);

  ///Set if the regex filter is readonly
  void SetFilterReadOnly(const bool readonly);

  ///Set the path in which this class will look for files
  static void SetPath(const std::string& path);

  ///The signal that is emitted when a file is selected
  boost::signals2::signal<void ()> m_signal_selected;

protected:

  ///The path this dialog starts at
  static std::string m_path;

  ///The user interface of this class
  struct Ui
  {
    Ui();
    Ui(const Ui&) = delete;
    Ui& operator=(const Ui&) = delete;
    Wt::WLineEdit * const m_edit_filter;
    Wt::WLabel * const m_label_filter;
    Wt::WSelectionBox * const m_selection_box;
  } m_ui;

  ///Get all the files in a folder
  //From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
  //static std::vector<std::string> GetFilesInFolder(const std::string& folder);

  ///\brief
  ///The method how to select files from a folder
  ///
  ///default behavior: select all files in the folder m_path that match the regex in m_edit_filter
  virtual std::vector<std::string> SelectFiles() const noexcept;

  ///\brief
  ///OnUpdateDialog updates the list of filenames in the m_selection_box
  ///
  ///OnUpdateDialog is called automatically when the selection filter is changed
  void OnUpdateDialog();

private:


  ///OnSelect is called when a client selected a file
  void OnSelect();
};

} //~namespace ribi

#endif // WTSELECTFILEDIALOG_H
