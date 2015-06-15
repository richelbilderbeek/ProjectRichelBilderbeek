//---------------------------------------------------------------------------
/*
TestSelectFileDialog, tool to test the SelectFileDialog class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestSelectFileDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/signals2.hpp>

#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WEnvironment>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WFileResource>

#include "fileio.h"
#include "wtaboutdialog.h"
#include "wttestselectfiledialogmaindialog.h"
#include "wtselectfiledialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtTestSelectFileDialogMainDialog::WtTestSelectFileDialogMainDialog()
  : ui{}
{
  {
    std::vector<std::string> v;
    v.push_back("ToolTestSelectFileDialogWelcome.png");
    for(const std::string& s: v)
    {
      if (!(QFile::exists(s.c_str())))
      {
        QFile f( (std::string(":/ToolTestSelectFileDialog/images/") + s).c_str() );
        f.copy(s.c_str());
      }
      if (!(QFile::exists(s.c_str())))
      {
        std::cerr << "Missing file " << s << std::endl;
      }
      assert(QFile::exists(s.c_str()));
    }
  }

  Show();
}

void ribi::WtTestSelectFileDialogMainDialog::OnSelect()
{
  ui.m_anchor->setText((std::string("Download ") + ui.m_dialog->GetSelectedFile()).c_str() );
  ui.m_anchor->setResource(new Wt::WFileResource(ui.m_dialog->GetSelectedFile(),ui.m_dialog->GetSelectedFile()));
}

void ribi::WtTestSelectFileDialogMainDialog::Show()
{
  clear();
  setContentAlignment(Wt::AlignCenter);

  ui.m_anchor = new Wt::WAnchor;
  ui.m_dialog = new WtSelectFileDialog;

  this->addWidget(ui.m_dialog);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_anchor);

  ui.m_dialog->m_signal_selected.connect(
    boost::bind(&ribi::WtTestSelectFileDialogMainDialog::OnSelect,this));
}
