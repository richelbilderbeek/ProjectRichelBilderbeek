//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapqtnodedialog.h"

#include <cassert>
#include <sstream>

#include "qtconceptmapnode.h"
#include "ui_qtconceptmapqtnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtQtNodeDialog::QtQtNodeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtQtNodeDialog),
  m_qtnode{},
  m_qtnodedialog{}
{
  ui->setupUi(this);
}

ribi::cmap::QtQtNodeDialog::~QtQtNodeDialog()
{
  delete ui;
}

void ribi::cmap::QtQtNodeDialog::SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept
{
  const bool verbose = false;

  assert(qtnode);
  if (m_qtnode == qtnode)
  {
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting node '" << qtnode->ToStr() << "'\n";
  }

  const auto concept_after = qtnode->GetConcept();
  const auto x_after = qtnode->GetX();
  const auto y_after = qtnode->GetY();

  bool concept_changed  = true;
  bool x_changed  = true;
  bool y_changed = true;

  if (m_qtnode)
  {
    const auto concept_before = m_qtnode->GetConcept();
    const auto x_before = m_qtnode->GetX();
    const auto y_before = m_qtnode->GetY();

    concept_changed = concept_before != concept_after;
    x_changed = x_before != x_after;
    y_changed = y_before != y_after;


    if (verbose)
    {
      if (concept_changed)
      {
        std::stringstream s;
        s
          << "Concept will change from "
          << concept_before->ToStr()
          << " to "
          << concept_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (x_changed)
      {
        std::stringstream s;
        s << "X will change from " << x_before
          << " to " << x_after << '\n';
        TRACE(s.str());
      }
      if (y_changed)
      {
        std::stringstream s;
        s << "Y will change from " << y_before
          << " to " << y_after << '\n';
        TRACE(s.str());
      }
    }
    //Disconnect m_concept
    m_qtnode->m_signal_concept_changed.disconnect(
      boost::bind(&ribi::cmap::QtNodeDialog::OnConceptChanged,this,boost::lambda::_1)
    );
    m_qtnode->m_signal_x_changed.disconnect(
      boost::bind(&ribi::cmap::QtNodeDialog::OnXchanged,this,boost::lambda::_1)
    );
    m_qtnode->m_signal_y_changed.disconnect(
      boost::bind(&ribi::cmap::QtNodeDialog::OnYchanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_qtnode = qtnode;


  assert(m_qtnode->GetConcept() == concept_after );
  assert(m_qtnode->GetX() == x_after );
  assert(m_qtnode->GetY() == y_after);

  m_qtnode->m_signal_concept_changed.connect(
    boost::bind(&ribi::cmap::QtNodeDialog::OnConceptChanged,this,boost::lambda::_1)
  );
  m_qtnode->m_signal_x_changed.connect(
    boost::bind(&ribi::cmap::QtNodeDialog::OnXchanged,this,boost::lambda::_1)
  );
  m_qtnode->m_signal_y_changed.connect(
    boost::bind(&ribi::cmap::QtNodeDialog::OnYchanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (concept_changed)
  {
    m_qtnode->m_signal_concept_changed(m_qtnode.get());
  }
  if (x_changed)
  {
    m_qtnode->m_signal_x_changed(m_qtnode.get());
  }
  if (y_changed)
  {
    m_qtnode->m_signal_y_changed(m_qtnode.get());
  }

  this->setMinimumHeight(
    this->GetMinimumHeight(
      *m_qtnode
    )
  );

  assert( qtnode ==  m_qtnode);
  assert(*qtnode == *m_qtnode);
}
