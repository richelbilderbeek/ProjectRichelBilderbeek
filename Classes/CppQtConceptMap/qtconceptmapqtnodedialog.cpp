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

#include <boost/lambda/lambda.hpp>

#include "conceptmapnode.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapnode.h"
#include "qtitemdisplaystrategy.h"
#include "qtroundededitrectitemdialog.h"
#include "trace.h"
#include "ui_qtconceptmapqtnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtQtNodeDialog::QtQtNodeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtQtNodeDialog),
  m_qtnode{},
  m_qtnodedialog{},
  m_qtroundededitrectitem_dialog{}
{
  ui->setupUi(this);
}

ribi::cmap::QtQtNodeDialog::~QtQtNodeDialog()
{
  delete ui;
}

int ribi::cmap::QtQtNodeDialog::GetMinimumHeight(const QtNode& qtnode) noexcept
{
  const int margin = 16;
  return
    QtNodeDialog::GetMinimumHeight(*qtnode.GetNode())
  + margin
  + QtRoundedEditRectItemDialog::GetMinimumHeight(qtnode)
  ;
}

void ribi::cmap::QtQtNodeDialog::OnNodeChanged(QtNode * const qtnode) noexcept
{
  assert( qtnode ==  m_qtnode.get());
  assert(*qtnode == *m_qtnode);
  boost::shared_ptr<QtRoundedEditRectItem> base(qtnode);
  this->m_qtroundededitrectitem_dialog->SetItem(base);
}

void ribi::cmap::QtQtNodeDialog::OnQtRoundedRectItemChanged(QtNode * const qtnode) noexcept
{
  this->m_qtnodedialog->SetNode(qtnode->GetNode());
}

void ribi::cmap::QtQtNodeDialog::SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept
{
  const bool verbose{false};

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

  const auto qtroundededitrectitem_after = qtnode.get();
  const auto node_after = qtnode->GetNode();

  bool qtroundededitrectitem_changed = true;
  bool node_changed = true;

  if (m_qtnode)
  {
    const auto qtroundededitrectitem_before = m_qtnode.get();
    const auto node_before = m_qtnode->GetNode();

    qtroundededitrectitem_changed = qtroundededitrectitem_before != qtroundededitrectitem_after;
    node_changed = node_before != node_after;


    if (verbose)
    {
      if (qtroundededitrectitem_changed)
      {
        std::stringstream s;
        s
          << "DisplayStrategy will change from "
          << qtroundededitrectitem_before->ToStr()
          << " to "
          << qtroundededitrectitem_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (node_changed)
      {
        std::stringstream s;
        s << "QtNode will change from " << (*node_before)
          << " to " << (*node_after) << '\n';
        TRACE(s.str());
      }
    }
    //Disconnect m_concept
    m_qtnode->m_signal_base_changed.disconnect(
      boost::bind(&ribi::cmap::QtQtNodeDialog::OnQtRoundedRectItemChanged,this,boost::lambda::_1)
    );
    m_qtnode->m_signal_node_changed.disconnect(
      boost::bind(&ribi::cmap::QtQtNodeDialog::OnNodeChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_qtnode = qtnode;

  assert(m_qtnode->GetNode() == node_after);

  m_qtnode->m_signal_base_changed.connect(
    boost::bind(&ribi::cmap::QtQtNodeDialog::OnQtRoundedRectItemChanged,this,boost::lambda::_1)
  );
  m_qtnode->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtQtNodeDialog::OnNodeChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (qtroundededitrectitem_changed)
  {
    m_qtnode->m_signal_base_changed(m_qtnode.get());
  }
  if (node_changed)
  {
    m_qtnode->m_signal_node_changed(m_qtnode.get());
  }

  this->setMinimumHeight(
    this->GetMinimumHeight(
      *m_qtnode
    )
  );

  assert( qtnode ==  m_qtnode);
  assert(*qtnode == *m_qtnode);
}
