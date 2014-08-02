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
#include "qtconceptmapqtedgedialog.h"

#include <cassert>
#include <sstream>

#include <boost/lambda/lambda.hpp>

#include <QVBoxLayout>

#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "qtconceptmapedgedialog.h"
#include "qtconceptmapedge.h"
#include "conceptmapnodefactory.h"
#include "qtitemdisplaystrategy.h"
#include "qtroundededitrectitemdialog.h"
#include "qtconceptmapqtnodefactory.h"
#include "testtimer.h"
#include "trace.h"

#include "ui_qtconceptmapqtedgedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtQtEdgeDialog::QtQtEdgeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtQtEdgeDialog),
  m_qtedge{},
  m_qtedgedialog{},
  m_qtroundededitrectitem_dialog{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  {
    assert(!this->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    this->setLayout(my_layout);
  }
  {
    assert(this->layout());
    const boost::shared_ptr<QtEdgeDialog> d{new QtEdgeDialog};
    assert(d);
    m_qtedgedialog = d;
    this->layout()->addWidget(m_qtedgedialog.get());
  }
  {
    assert(this->layout());
    const boost::shared_ptr<QtRoundedEditRectItemDialog> d{new QtRoundedEditRectItemDialog};
    m_qtroundededitrectitem_dialog = d;
    this->layout()->addWidget(m_qtroundededitrectitem_dialog.get());
  }
}

ribi::cmap::QtQtEdgeDialog::~QtQtEdgeDialog()
{
  delete ui;
}

void ribi::cmap::QtQtEdgeDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  //Check if its subdialogs match
  const boost::shared_ptr<QtEdgeDialog> lhs = m_qtedgedialog;
  const boost::shared_ptr<QtRoundedEditRectItemDialog> rhs = m_qtroundededitrectitem_dialog;
  lhs->CheckMe();
  rhs->CheckMe();
  #ifdef DISABLE_TEST_TEMP_20140729
  if (std::abs(lhs->GetUiX() - rhs->GetUiX()) >= 1.0)
  {
    TRACE("ERROR");
    TRACE(lhs->GetUiX());
    TRACE(rhs->GetUiX());
    TRACE("BREAK");
  }

  assert(std::abs(lhs->GetUiX() - rhs->GetUiX()) < 1.0);
  assert(std::abs(lhs->GetUiY() - rhs->GetUiY()) < 1.0);
  #endif // DISABLE_TEST_TEMP_20140729
  #endif
}

int ribi::cmap::QtQtEdgeDialog::GetMinimumHeight(const QtEdge& qtedge) noexcept
{
  const int margin = 16;
  return
    QtEdgeDialog::GetMinimumHeight(*qtedge.GetEdge())
  + margin
  + QtRoundedEditRectItemDialog::GetMinimumHeight(qtedge)
  ;
}

void ribi::cmap::QtQtEdgeDialog::OnEdgeChanged(QtEdge * const qtedge) noexcept
{
  assert( qtedge ==  m_qtedge.get());
  assert(*qtedge == *m_qtedge);
  m_qtroundededitrectitem_dialog->SetItem(m_qtedge);

  m_qtroundededitrectitem_dialog->CheckMe();
  m_qtedgedialog->CheckMe();
}

void ribi::cmap::QtQtEdgeDialog::OnQtRoundedRectItemChanged(QtEdge * const qtedge) noexcept
{
  //Emit
  m_qtedgedialog->SetEdge(qtedge->GetEdge());
  m_qtedgedialog->CheckMe();
  m_qtroundededitrectitem_dialog->CheckMe();

  /*
  if (edge == m_edge) return;
  if (*edge == *m_edge) return;
  assert(std::abs(m_edge->GetX() - this->GetPos().x()) < 2.0); //Allow two maximal rounding off errors
  assert(std::abs(m_edge->GetY() - this->GetPos().y()) < 2.0); //Allow two maximal rounding off errors
  //if (edge->GetX() != m_edge->GetX())
  {
    //const double new_x = edge->GetX();
    //m_edge->SetX(new_x);
    this->SetPos(edge->GetX(),this->GetPos().y());
  }
  //if (edge->GetY() != m_edge->GetY())
  {
    //const double new_y = edge->GetY();
    //m_edge->SetY(new_y);
    this->SetPos(this->GetPos().x(),edge->GetY());
  }
  //if (edge->GetConcept()->GetName() != m_edge->GetConcept()->GetName())
  {
    //const auto new_text = edge->GetConcept()->GetName();
    //m_edge->GetConcept()->SetName(new_text);
    this->SetText(Container().SeperateString(edge->GetConcept()->GetName(),'\n'));
  }
  */
}

void ribi::cmap::QtQtEdgeDialog::SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept
{
  const bool verbose{false};

  assert(qtedge);

  if (m_qtedge == qtedge)
  {
    CheckMe();
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting edge '" << qtedge->ToStr() << "'\n";
  }

  const auto qtroundededitrectitem_after = qtedge.get();
  const auto edge_after = qtedge->GetEdge();

  bool qtroundededitrectitem_changed = true;
  bool edge_changed = true;

  if (m_qtedge)
  {
    const auto qtroundededitrectitem_before = m_qtedge.get();
    const auto edge_before = m_qtedge->GetEdge();

    qtroundededitrectitem_changed = qtroundededitrectitem_before != qtroundededitrectitem_after;
    edge_changed = edge_before != edge_after;


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
      if (edge_changed)
      {
        std::stringstream s;
        s << "QtEdge will change from " << (*edge_before)
          << " to " << (*edge_after) << '\n';
        TRACE(s.str());
      }
    }
    //Disconnect m_concept
    m_qtedge->m_signal_base_changed.disconnect(
      boost::bind(&ribi::cmap::QtQtEdgeDialog::OnQtRoundedRectItemChanged,this,boost::lambda::_1)
    );
    m_qtedge->m_signal_edge_changed.disconnect(
      boost::bind(&ribi::cmap::QtQtEdgeDialog::OnEdgeChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_qtedge = qtedge;

  assert(m_qtedge->GetEdge() == edge_after);

  m_qtedge->m_signal_base_changed.connect(
    boost::bind(&ribi::cmap::QtQtEdgeDialog::OnQtRoundedRectItemChanged,this,boost::lambda::_1)
  );
  m_qtedge->m_signal_edge_changed.connect(
    boost::bind(&ribi::cmap::QtQtEdgeDialog::OnEdgeChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (qtroundededitrectitem_changed)
  {
    m_qtedge->m_signal_base_changed(m_qtedge.get());
  }
  if (edge_changed)
  {
    m_qtedge->m_signal_edge_changed(m_qtedge.get());
  }



  this->setMinimumHeight(
    this->GetMinimumHeight(
      *m_qtedge
    )
  );

  assert( qtedge ==  m_qtedge);
  assert(*qtedge == *m_qtedge);
  CheckMe();
}

#ifndef NDEBUG
void ribi::cmap::QtQtEdgeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtQtEdgeDialog dialog;

  const auto from = NodeFactory().GetTest(1);
  const auto to = NodeFactory().GetTest(1);
  const auto edge = EdgeFactory().GetTest(1,from,to);
  const auto qtfrom = QtNodeFactory().Create(from);
  const auto qtto = QtNodeFactory().Create(to);
  const boost::shared_ptr<QtEdge> qtedge(new QtEdge(edge,qtfrom.get(),qtto.get()));
  dialog.SetQtEdge(qtedge);
  const boost::shared_ptr<QtEdgeDialog> lhs = dialog.m_qtedgedialog;
  const boost::shared_ptr<QtRoundedEditRectItemDialog> rhs = dialog.m_qtroundededitrectitem_dialog;
  lhs->CheckMe();
  rhs->CheckMe();
  dialog.CheckMe();
  assert(std::abs(lhs->GetUiX() - rhs->GetUiX()) < 1.0);
  assert(std::abs(lhs->GetUiY() - rhs->GetUiY()) < 1.0);
  ///LHS, setX
  {
    const double new_x{lhs->GetUiX() + 5.0};
    lhs->SetUiX(new_x);
    lhs->CheckMe();
    assert(std::abs(lhs->GetUiX() - new_x) < 1.0);
    dialog.CheckMe();
  }
  //RHS, setX
  {
    const double new_x{rhs->GetUiX() + 5.0};
    rhs->SetUiX(new_x);
    lhs->CheckMe();
    assert(std::abs(rhs->GetUiX() - new_x) < 1.0);
    dialog.CheckMe();
  }
  lhs->SetUiY(lhs->GetUiX() + 5.0);
  dialog.CheckMe();
  rhs->SetUiY(rhs->GetUiX() + 5.0);
  dialog.CheckMe();
}
#endif
