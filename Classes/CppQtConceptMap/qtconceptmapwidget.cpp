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
#include "qtconceptmapwidget.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lambda/lambda.hpp>
#include <QMouseEvent>

#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeletefocusnode.h"
#include "conceptmapcommanddeletenode.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommandsetfocusrandom.h"
#include "conceptmapcommandsetselectedwithcoordinat.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapwidget.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmap.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtdisplayconceptmap.h"
#include "qteditconceptmap.h"
#include "qtrateconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapWidget::QtConceptMapWidget(
  const boost::shared_ptr<QtConceptMap> qtconceptmap)
  : m_qtconceptmap(qtconceptmap),
    m_widget(new Widget(qtconceptmap->GetConceptMap()))
{
  #ifndef NDEBUG
  Test();
  #endif
  this->setScene(m_qtconceptmap->GetScene());

  //Without this line, mouseMoveEvent won't be called
  this->setMouseTracking(true);

  //m_widget->m_signal_set_focus.connect(
  //  boost::bind(&ribi::cmap::QtConceptMapWidget::OnSetFocusNode,this,boost::lambda::_1)
  //);
  m_widget->m_signal_concept_map_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnConceptMapChanged,this)
  );
  m_widget->m_signal_add_edge.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnAddEdge,this,boost::lambda::_1)
  );
  m_widget->m_signal_add_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnAddNode,this,boost::lambda::_1)
  );
  m_widget->m_signal_delete_edge.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnDeleteEdge,this,boost::lambda::_1)
  );
  m_widget->m_signal_delete_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnDeleteNode,this,boost::lambda::_1)
  );
  //m_widget->m_signal_lose_focus.connect(
  //  boost::bind(&ribi::cmap::QtConceptMapWidget::OnLoseFocus,this,boost::lambda::_1)
  //);
  m_widget->m_signal_lose_selected.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnLoseSelected,this,boost::lambda::_1)
  );
  m_widget->m_signal_set_selected.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnSetSelected,this,boost::lambda::_1,boost::lambda::_2)
  );
}


bool ribi::cmap::QtConceptMapWidget::CanDoCommand(
  const boost::shared_ptr<const Command> command) const noexcept
{
  assert(command);
  assert(m_widget.get());
  return command->CanDoCommand(m_widget.get());
}

bool ribi::cmap::QtConceptMapWidget::CanUndo() const noexcept
{
  assert(m_widget);
  return m_widget->CanUndo();
}

void ribi::cmap::QtConceptMapWidget::DoCommand(
  const boost::shared_ptr<Command> command) noexcept
{
  assert(CanDoCommand(command));
  m_widget->DoCommand(command);
  //m_widget->AddAndDoCommand(command);
  //command->DoCommand(m_widget.get());
  assert(CanUndo());
}

const ribi::cmap::Widget& ribi::cmap::QtConceptMapWidget::GetWidget() const noexcept
{
  assert(m_widget);
  return *(m_widget.get());
}

void ribi::cmap::QtConceptMapWidget::keyPressEvent(QKeyEvent * e) noexcept
{
  if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier)
  {
    if (m_widget->CanUndo()) { m_widget->Undo(); }
  }
}

void ribi::cmap::QtConceptMapWidget::mouseDoubleClickEvent(QMouseEvent * e) noexcept
{
  //TRACE(e);
  if (!e) throw std::exception(); //To satisfy the compiler
}

void ribi::cmap::QtConceptMapWidget::mouseMoveEvent(QMouseEvent * e) noexcept
{
  this->setCursor(QCursor(Qt::ArrowCursor));
  //Can focus be set here?
  {
    const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());
    const boost::shared_ptr<const CommandSetSelectedWithCoordinat> cmd {
      new CommandSetSelectedWithCoordinat(pos.x(),pos.y())
    };
    if (cmd->CanDoCommand(m_widget))
    {
      this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
      //Nothing
    }
  }
}


void ribi::cmap::QtConceptMapWidget::mousePressEvent(QMouseEvent * e) noexcept
{
  {
    const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());
    const boost::shared_ptr<CommandSetSelectedWithCoordinat> cmd {
      new CommandSetSelectedWithCoordinat(pos.x(),pos.y())
    };
    if (cmd->CanDoCommand(m_widget))
    {
      cmd->DoCommand(m_widget);
    }
  }
}

void ribi::cmap::QtConceptMapWidget::OnAddEdge(const boost::shared_ptr<Edge> edge) noexcept
{
  //TRACE_FUNC();
  assert(edge);
  if (!edge)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    /*
    #ifndef NDEBUG
    const std::size_t qtedge_before { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_before { m_widget->GetConceptMap()->GetEdges().size() };
    #endif
    */
    //#ifdef FIX_ISSUE_281
    QtEdge * const qtedge { m_qtconceptmap->AddEdge(edge) };
    assert(m_qtconceptmap->FindQtEdge(qtedge));
    m_qtconceptmap->FindQtEdge(qtedge)->setFocus();
    //#endif // FIX_ISSUE_281
    /*
    #ifndef NDEBUG
    const std::size_t qtedges_after { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_after { m_widget->GetConceptMap()->GetEdges().size() };
    assert(qtedges_after > qtedge_before);
    assert(edges_after == edges_before && "These edges are already added to the Widget");
    if(m_qtconceptmap->GetQtEdges().size() != m_widget->GetConceptMap()->GetEdges().size())
    {
      TRACE(qtedge_before);
      TRACE(edges_before);
      TRACE(qtedges_after);
      TRACE(edges_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtEdges().size() == m_widget->GetConceptMap()->GetEdges().size());
    #endif
    */
  }
}

void ribi::cmap::QtConceptMapWidget::OnAddNode(const boost::shared_ptr<Node> node) noexcept
{
  //TRACE_FUNC();
  assert(node);
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    #endif
    m_qtconceptmap->AddNode(node);
    assert(m_qtconceptmap->FindQtNode(node.get()));
    m_qtconceptmap->FindQtNode(node.get())->setSelected(true); //A new Node is also selected

    #ifndef NDEBUG
    const std::size_t qtnodes_after { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_after { m_widget->GetConceptMap()->GetNodes().size() };
    //TODO: If these tests fail, isolate that test and move this to a ::Test member function
    assert(qtnodes_after > qtnodes_before);
    assert(nodes_after == nodes_before && "These nodes are already added to the Widget");
    assert(m_qtconceptmap->GetQtNodes().size() == m_widget->GetConceptMap()->GetNodes().size());
    #endif
  }
}

void ribi::cmap::QtConceptMapWidget::OnConceptMapChanged() noexcept
{
  m_qtconceptmap->scene()->update();
  m_qtconceptmap->update();
  scene()->update();
}

void ribi::cmap::QtConceptMapWidget::OnDeleteEdge(const boost::shared_ptr<Edge> edge) noexcept
{
  if (!edge)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtedges_before { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_before { m_widget->GetConceptMap()->GetEdges().size() };
    #endif
    assert(m_qtconceptmap->FindQtEdge(edge));
    m_qtconceptmap->DeleteEdge(m_qtconceptmap->FindQtEdge(edge));
    assert(!m_qtconceptmap->FindQtEdge(edge));
    //m_qtconceptmap->FindQtEdge(node.get())->setFocus();
    m_qtconceptmap->clearFocus();

    #ifndef NDEBUG
    const std::size_t qtedges_after { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_after { m_widget->GetConceptMap()->GetEdges().size() };
    assert(qtedges_after < qtedges_before);
    assert(edges_after == edges_before && "These nodes are already added to the Widget");
    if(m_qtconceptmap->GetQtEdges().size() != m_widget->GetConceptMap()->GetEdges().size())
    {
      TRACE(qtedges_before);
      TRACE(edges_before);
      TRACE(qtedges_after);
      TRACE(edges_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtEdges().size() == m_widget->GetConceptMap()->GetEdges().size());
    #endif

  }
}

void ribi::cmap::QtConceptMapWidget::OnDeleteNode(const boost::shared_ptr<Node> node) noexcept
{
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    #endif
    assert(m_qtconceptmap->FindQtNode(node.get()));
    m_qtconceptmap->DeleteNode(m_qtconceptmap->FindQtNode(node.get()));
    assert(!m_qtconceptmap->FindQtNode(node.get()));
    //m_qtconceptmap->FindQtNode(node.get())->setFocus();
    m_qtconceptmap->clearFocus();

    #ifndef NDEBUG
    const std::size_t qtnodes_after { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_after { m_widget->GetConceptMap()->GetNodes().size() };
    assert(qtnodes_after < qtnodes_before);
    assert(nodes_after == nodes_before && "These nodes are already added to the Widget");
    if(m_qtconceptmap->GetQtNodes().size() != m_widget->GetConceptMap()->GetNodes().size())
    {
      TRACE(qtnodes_before);
      TRACE(nodes_before);
      TRACE(qtnodes_after);
      TRACE(nodes_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtNodes().size() == m_widget->GetConceptMap()->GetNodes().size());
    #endif

  }
}


void ribi::cmap::QtConceptMapWidget::OnLoseFocus(const boost::shared_ptr<Node> node) noexcept
{
  if (m_qtconceptmap->FindQtNode(node.get()))
  {
    m_qtconceptmap->FindQtNode(node.get())->clearFocus();
    //m_qtconceptmap->FindQtNode(node.get())->setSelected(false); //Would this be needed as well?
  }
}

/*
void ribi::cmap::QtConceptMapWidget::OnLoseSelected(const std::vector<boost::shared_ptr<Node>> nodes) noexcept
{
  for (const auto node: nodes) { OnLoseSelected(node); }
}
*/

void ribi::cmap::QtConceptMapWidget::OnLoseSelected(const std::vector<boost::shared_ptr<Node>> nodes) noexcept
{
  for (const auto node: nodes)
  {
    if (m_qtconceptmap->FindQtNode(node.get()))
    {
      m_qtconceptmap->FindQtNode(node.get())->setSelected(false);
    }
  }
}

void ribi::cmap::QtConceptMapWidget::OnSetSelected(
  const Edges& edges,
  const Nodes& nodes
) noexcept
{
  for (const auto edge: edges)
  {
    m_qtconceptmap->FindQtEdge(edge.get())->setSelected(true);
  }
  for (const auto node: nodes)
  {
    m_qtconceptmap->FindQtNode(node.get())->setSelected(true);
  }
}
/*
void ribi::cmap::QtConceptMapWidget::OnSetFocusNode(const boost::shared_ptr<Node> node) noexcept
{
  //TRACE_FUNC();
  assert(node);
}
*/
/*
void ribi::cmap::QtConceptMapWidget::showEvent(QShowEvent*) noexcept
{
  assert(this->isVisible());
  m_qtconceptmap->show();
  assert(this->m_qtconceptmap->isVisible());
}
*/

void ribi::cmap::QtConceptMapWidget::Undo() noexcept
{
  assert(m_widget);
  assert(CanUndo());
  m_widget->Undo();
}
