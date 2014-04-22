//---------------------------------------------------------------------------
/*
WtRichelBilderbeekGalleryDialog, gallery of Richel Bilderbeek's work
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtRichelBilderbeekGalleryDialog.htm
//---------------------------------------------------------------------------
#include "wtrichelbilderbeekgallerydialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WImage>

#include "about.h"
#include "qtrichelbilderbeekgalleryresources.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "wtaboutdialog.h"


ribi::RichelBilderbeek::WtGalleryDialog::Ui::Ui()
  : m_table(new Wt::WTable)
{

}

ribi::RichelBilderbeek::WtGalleryDialog::WtGalleryDialog()
  : m_ui{}
{
  this->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(this);
  new Wt::WLabel("Overview of Richel Bilderbeek's work",this);
  new Wt::WBreak(this);
  new Wt::WBreak(this);
  this->addWidget(m_ui.m_table);

  //table->setHeaderCount(1,Wt::Horizontal);
  //table->setHeaderCount(1,Wt::Vertical);
  m_ui.m_table->setMaximumSize(400,200);
  QtResources r;
  m_ui.m_table->elementAt(0,0)->addWidget(new Wt::WLabel("Program"));
  m_ui.m_table->elementAt(0,1)->addWidget(new Wt::WImage(r.GetCl()));
  m_ui.m_table->elementAt(0,2)->addWidget(new Wt::WImage(r.GetWindows()));
  m_ui.m_table->elementAt(0,3)->addWidget(new Wt::WImage(r.GetDesktop()));
  m_ui.m_table->elementAt(0,4)->addWidget(new Wt::WImage(r.GetWeb()));
  //ui.m_table->setPositionScheme(Wt::PositionScheme(Wt::CenterX | Wt::CenterY));

  const std::vector<boost::shared_ptr<Program> > v = RichelBilderbeek::Program::GetAllPrograms();
  const std::size_t n = v.size();
  for (std::size_t i=0; i!=n; ++i)
  {
    //Add a label
    {
      Wt::WLabel * const label = new Wt::WLabel(v[i]->GetName().c_str());
      //label->setMaximumSize(Wt::WLength::Auto,6);
      //label->setHeight(6);
      m_ui.m_table->elementAt(i+1,0)->addWidget(label);
      //ui.m_table->elementAt(i+1,0)->setMaximumSize(Wt::WLength::Auto,6);
    }
    for (int j=0; j!=4; ++j)
    {
      ProgramStatus p =  ProgramStatus::unk;
      switch (j)
      {
        case 0: p = v[i]->GetStatusConsole(); break;
        case 1: p = v[i]->GetStatusDesktopWindowsOnly(); break;
        case 2: p = v[i]->GetStatusDesktop(); break;
        case 3: p = v[i]->GetStatusWebApplication(); break;
      }
      std::string s;
      switch (p)
      {
        case ProgramStatus::yes: s = r.GetGreen(); break;
        case ProgramStatus::no: s = r.GetRed(); break;
        case ProgramStatus::nvr: s = r.GetBlack(); break;
        case ProgramStatus::n_a: s = r.GetBlack(); break;
        case ProgramStatus::wip: s = r.GetYellow(); break;
        case ProgramStatus::tbd: s = r.GetOrange(); break;
        case ProgramStatus::unk: s = r.GetBlack(); break;
      }
      m_ui.m_table->elementAt(i+1,j+1)->addWidget(new Wt::WImage(s.c_str()));
    }
  }
  {
    const int n_rows = m_ui.m_table->rowCount();
    for (int i=0; i!=n_rows; ++i)
    {
      //ui.m_table->rowAt(i)->elementAt(0)->set
    }
  }
  m_ui.m_table->clicked().connect(this,&ribi::RichelBilderbeek::WtGalleryDialog::OnClick);
}

void ribi::RichelBilderbeek::WtGalleryDialog::OnClick(const Wt::WMouseEvent&)
{
  //const int x = event.widget().x;
  //const int y = event.widget().y;
}

