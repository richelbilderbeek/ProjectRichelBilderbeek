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
    m_qtconceptdialog{new QtConceptDialog},
    m_qtnodedialog_from{new QtNodeDialog},
    m_qtnodedialog_to{new QtNodeDialog}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  {
    assert(layout());
    layout()->addWidget(m_qtconceptdialog.get());
    {
      QLabel * const label = new QLabel("From");
      layout()->addWidget(label);
    }
    layout()->addWidget(m_qtnodedialog_from.get());
    {
      QLabel * const label = new QLabel("To");
      layout()->addWidget(label);
    }
    layout()->addWidget(m_qtnodedialog_to.get());
  }
}

ribi::cmap::QtEdgeDialog::~QtEdgeDialog()
{
  delete ui;
}

void ribi::cmap::QtEdgeDialog::SetEdge(const boost::shared_ptr<Edge>& edge)
{
  const bool verbose = true;

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
  const auto concept_after = edge->GetConcept();
  const auto x_after = edge->GetX();
  const auto y_after = edge->GetY();


  bool concept_changed  = true;
  bool x_changed  = true;
  bool y_changed = true;

  if (m_edge)
  {
    const auto concept_before = m_edge->GetConcept();
    const auto x_before = m_edge->GetX();
    const auto y_before = m_edge->GetY();

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
    m_edge->m_signal_concept_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnConceptChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_x_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnXchanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_y_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdgeDialog::OnYchanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_edge = edge;

  assert(m_edge->GetConcept() == concept_after );
  assert(m_edge->GetX()  == x_after );
  assert(m_edge->GetY() == y_after);

  m_edge->m_signal_concept_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnConceptChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_x_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnXchanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_y_changed.connect(
    boost::bind(&ribi::cmap::QtEdgeDialog::OnYchanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (concept_changed)
  {
    m_edge->m_signal_concept_changed(m_edge.get());
  }
  if (x_changed)
  {
    m_edge->m_signal_x_changed(m_edge.get());
  }
  if (y_changed)
  {
    m_edge->m_signal_y_changed(m_edge.get());
  }

  assert( edge ==  m_edge);
  assert(*edge == *m_edge);
}

void ribi::cmap::QtEdgeDialog::OnConceptChanged(Node * const node)
{
  const bool verbose = true;
  assert(node);

  const auto concept_before = m_qtconceptdialog->GetConcept();
  const boost::shared_ptr<Concept> concept_after = node->GetConcept();

  if (verbose)
  {
    std::stringstream s;
    s << "Change concept from "
    << (concept_before ? concept_before->ToStr() : "[NONE]")
    << " to " << concept_after->ToStr();
    TRACE(s.str());
  }

  m_qtconceptdialog->SetConcept(concept_after);

  assert(m_qtconceptdialog->GetConcept() == concept_after);
}

void ribi::cmap::QtEdgeDialog::OnXchanged(Node * const node)
{
  assert(node);
  ui->box_x->setValue(node->GetX());
}

void ribi::cmap::QtEdgeDialog::OnYchanged(Node * const node)
{
  assert(node);
  ui->box_y->setValue(node->GetY());
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

void ribi::cmap::QtEdgeDialog::on_box_x_valueChanged(double arg1)
{
  m_edge->SetX(arg1);
}

void ribi::cmap::QtEdgeDialog::on_box_y_valueChanged(double arg1)
{
  m_edge->SetY(arg1);
}
