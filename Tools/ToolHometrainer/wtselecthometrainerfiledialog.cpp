//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#include "wtselecthometrainerfiledialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <Wt/WLabel>
#include <Wt/WLineEdit>

#include "fileio.h"
#pragma GCC diagnostic pop

ribi::WtSelectHometrainerFileDialog::WtSelectHometrainerFileDialog()
{
  m_ui.m_edit_filter->hide();
  m_ui.m_label_filter->hide();
  OnUpdateDialog();
}

std::string ribi::WtSelectHometrainerFileDialog::GetFirstLineFromFile(
  const std::string& filename)
{

  assert(fileio::FileIo().IsRegularFile(filename));
  std::ifstream in(filename.c_str());
  for (int i=0; !in.eof(); ++i)
  {
    std::string s;
    std::getline(in,s);
    if (!s.empty())
    {
      return boost::algorithm::trim_copy(s);
    }
  }
  return "";
}

std::vector<std::string> ribi::WtSelectHometrainerFileDialog::SelectFiles() const noexcept
{
  //Get all filenames
  const std::vector<std::string> all_files = fileio::FileIo().GetFilesInFolder(m_path);

  //Create the regex for a correct text file
  const boost::xpressive::sregex file_regex
    = boost::xpressive::sregex::compile("(.*.txt)");

  std::vector<std::string> r;
  //Copy_if(v.begin(),v.end(),
  //  std::back_inserter(w),
  //    boost::regex_match(boost::bind(boost::lambda::_1),txt_file_regex));

  //Copy all filenames matching the regex in the resulting std::vector
  for(const auto file: all_files)
  {
    if (boost::xpressive::regex_match(file,file_regex))
    {
      //File matches regex
      const std::string s = GetFirstLineFromFile(file);
      if (s == "Hometrainer2 (C) 2009 Richel Bilderbeek"
       || s == "Hometrainer (C) 2009 Richel Bilderbeek")
      {
        r.push_back(file);
      }
    }
  }

  std::sort(r.begin(),r.end());
  return r;
}

