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
#include "qtconceptmapedgedialog.h"

#include <cassert>
#include <boost/bind/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QLabel>

#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "qtconceptmapconceptdialog.h"
#include "qtconceptmapnodedialog.h"
#include "ui_qtconceptmapedgedialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::cmap::QtEdgeDialog::QtEdgeDialog(QWidget *parent)
  : ribi::QtHideAndShowDialog(parent),
    ui(new Ui::QtEdgeDialog),
    m_edge{},
    m_qtnodedialog{new QtNodeDialog},
    m_qtnodedialog_from{new QtNodeDialog},
    m_qtnodedialog_to{new QtNodeDialog}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  {
    assert(layout());
    {
      QLabel * const label = new QLabel("Center node:");
      layout()->addWidget(label);
    }
    layout()->addWidget(m_qtnodedialog.get());
    {
      QLabel * const label = new QLabel("From node:");
      layout()->addWidget(label);
    }
    layout()->addWidget(m_qtnodedialog_from.get());
    {
      QLabel * const label = new QLabel("To node:");
      layout()->addWidget(label);
    }
    layout()->addWidget(m_qtnodedialog_to.get());
  }
}

ribi::cmap::QtEdgeDialog::~QtEdgeDialog()
{
  delete ui;
}

int ribi::cmap::QtEdgeDialog::GetMinimumHeight(const Edge& edge) noexcept
{
  return
      QtNodeDialog::GetMinimumHeight(*edge.GetFrom())
    + QtNodeDialog::GetMinimumHeight(*edge.GetNode())
    + QtNodeDialog::GetMinimumHeight(*edge.GetTo())
    + 68
  ;
}

void ribi::cmap::QtEdgeDialog::SetEdge(const boost::shared_ptr<Edge>& edge)
{
  const bool verbose = false;

  assert(edge);
  if (m_edge == edge)
  {
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting edge '" << edge->ToStr() << "'\n";
  }
  const auto from_after = edge->GetFrom();
  const auto head_arrow_after = edge->HasHeadArrow();
  const auto node_after = edge->GetNode();
  const auto tail_arrow_after = edge->HasTailArrow();
  const auto to_after = edge->GetTo();

  bool from_changed  = true;
  bool head_arrow_changed  = true;
  bool node_changed  = true;
  bool tail_arrow_changed  = true;
  bool to_changed  = true;

  if (m_edge)
  {
    const auto from_before = m_edge->GetFrom();
    const auto head_arrow_before = m_edge->HasHeadArrow();
    const auto node_before = m_edge->GetNode();
    const auto tail_arrow_before = m_edge->HasTailArrow();
    const auto to_before = m_edge->GetTo();


    from_changed = from_before != from_after;
    head_arrow_changed = head_arrow_before != head_arrow_after;
    node_changed = node_before != node_after;
    tail_arrow_changed = tail_arrow_before != tail_arrow_after;
    to_changed = to_before != to_after;


    if (verbose)
    {
      if (from_changed)
      {
        std::stringstream s;
        s
          << "From will change from "
          << from_before->ToStr()
          << " to "
          << from_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (head_arrow_changed)
      {
        std::stringstream s;
        s
          << "Head arrow will change from "
          << head_arrow_before
          << " to "
          << head_arrow_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (node_changed)
      {
        std::stringstream s;
        s
          << "Node will change from "
          << node_before->ToStr()
          << " to "
          << node_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (tail_arrow_changed)
      {
        std::stringstream s;
        s
          << "Tail arrow will change from "
          << tail_arrow_before
          << " to "
          << tail_arrow_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (to_changed)
      {
        std::stringstream s;
        s
          << "To will change from "
          << to_before->ToStr()
          << " to "
          << to_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
    }
    //Disconnect
    m_edge->m_signal_from_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnFromChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_head_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnHeadArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_node_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnNodeChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_tail_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnTailArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_to_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnToChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_edge = edge;

  assert(m_edge->GetFrom() == from_after );
  assert(m_edge->HasHeadArrow() == head_arrow_after );
  assert(m_edge->GetNode() == node_after );
  assert(m_edge->HasTailArrow() == tail_arrow_after );
  assert(m_edge->GetTo() == to_after );

  //Connect
  m_edge->m_signal_from_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnFromChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_head_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnHeadArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnNodeChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_tail_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnTailArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_to_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnToChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (from_changed)
  {
    m_edge->m_signal_from_changed(m_edge.get());
  }
  if (head_arrow_changed)
  {
    m_edge->m_signal_head_arrow_changed(m_edge.get());
  }
  if (node_changed)
  {
    m_edge->m_signal_node_changed(m_edge.get());
  }
  if (tail_arrow_changed)
  {
    m_edge->m_signal_tail_arrow_changed(m_edge.get());
  }
  if (to_changed)
  {
    m_edge->m_signal_to_changed(m_edge.get());
  }

  setMinimumHeight(GetMinimumHeight(*m_edge));

  assert( edge ==  m_edge);
  assert(*edge == *m_edge);
}

void ribi::cmap::QtEdgeDialog::OnFromChanged(Edge * const edge)
{
  const bool verbose = false;
  assert(edge);

  const auto from_before = m_qtnodedialog_from->GetNode();
  const auto from_after = edge->GetFrom();

  if (verbose)
  {
    std::stringstream s;
    s << "Change from from "
    << (from_before ? from_before->ToStr() : "[NONE]")
    << " to " << from_after->ToStr();
    TRACE(s.str());
  }

  m_qtnodedialog_from->SetNode(from_after);

  assert(m_qtnodedialog_from->GetNode() == from_after);
}

void ribi::cmap::QtEdgeDialog::OnHeadArrowChanged(Edge * const edge)
{
  const bool verbose = false;
  assert(edge);

  const auto head_arrow_before = ui->box_head_arrow->isChecked();
  const auto head_arrow_after = edge->HasHeadArrow();

  if (verbose)
  {
    std::stringstream s;
    s << "Change head arrow from "
      << head_arrow_before
      << " to " << head_arrow_after
    ;
    TRACE(s.str());
  }

  ui->box_head_arrow->setChecked(head_arrow_after);

  assert(ui->box_head_arrow->isChecked() == head_arrow_after);
}

void ribi::cmap::QtEdgeDialog::OnNodeChanged(Edge * const edge)
{
  const bool verbose = false;
  assert(edge);

  const auto node_before = m_qtnodedialog->GetNode();
  const auto node_after = edge->GetNode();

  if (verbose)
  {
    std::stringstream s;
    s << "Change center node from "
    << (node_before ? node_before->ToStr() : "[NONE]")
    << " to " << node_after->ToStr();
    TRACE(s.str());
  }

  m_qtnodedialog->SetNode(node_after);

  assert(m_qtnodedialog->GetNode() == node_after);
}


void ribi::cmap::QtEdgeDialog::OnTailArrowChanged(Edge * const edge)
{
  const bool verbose = false;
  assert(edge);

  const auto tail_arrow_before = ui->box_tail_arrow->isChecked();
  const auto tail_arrow_after = edge->HasTailArrow();

  if (verbose)
  {
    std::stringstream s;
    s << "Change tail arrow from "
      << tail_arrow_before
      << " to " << tail_arrow_after
    ;
    TRACE(s.str());
  }

  ui->box_tail_arrow->setChecked(tail_arrow_after);

  assert(ui->box_tail_arrow->isChecked() == tail_arrow_after);
}


void ribi::cmap::QtEdgeDialog::OnToChanged(Edge * const edge)
{
  const bool verbose = false;
  assert(edge);

  const auto to_before = m_qtnodedialog_to->GetNode();
  const auto to_after = edge->GetTo();

  if (verbose)
  {
    std::stringstream s;
    s << "Change to from "
    << (to_before ? to_before->ToStr() : "[NONE]")
    << " to " << to_after->ToStr();
    TRACE(s.str());
  }

  m_qtnodedialog_to->SetNode(to_after);

  assert(m_qtnodedialog_to->GetNode() == to_after);
}


#ifndef NDEBUG
void ribi::cmap::QtEdgeDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtEdgeDialog::Test");
  //QtEdgeDialog d;
  TRACE("ribi::cmap::QtEdgeDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtEdgeDialog::on_box_head_arrow_stateChanged(int)
{
  m_edge->SetHeadArrow(ui->box_head_arrow->isChecked());
}

void ribi::cmap::QtEdgeDialog::on_box_tail_arrow_stateChanged(int)
{
  m_edge->SetTailArrow(ui->box_tail_arrow->isChecked());
}
