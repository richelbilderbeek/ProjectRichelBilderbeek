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
#ifndef NDEBUG
#include "qtconceptmapwidget.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lambda/lambda.hpp>
#include <QMouseEvent>

#include "conceptmapcommandaddselectedrandom.h"
#include "conceptmapcommandcreatenewedge.h"
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

void ribi::cmap::QtConceptMapWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("AddNode: Test creation of node from empty concept map, undo via widget"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    assert(m);
    assert(m->GetNodes().empty() && "An empty concept map must not have nodes");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    assert(c);
    assert(c->GetQtNodes().empty() && "An empty QtConceptMap must not have nodes");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    assert(!w->CanUndo());
    const boost::shared_ptr<CommandCreateNewNode> cmd(
      new CommandCreateNewNode
    );

    assert(m->GetNodes().empty() && "The concept map must be empty");
    assert(c->GetQtNodes().empty() && "The QtConceptMap must be empty");
    assert(w->CanDoCommand(cmd));
    w->DoCommand(cmd);
    assert(!m->GetNodes().empty() && "After creation a new node, the previously empty concept map must have a node");
    assert(!c->GetQtNodes().empty() && "After creation a new node, the previously empty QtConceptMap must have a node");
    TRACE(m->GetNodes().size());
    TRACE(c->GetQtNodes().size());
    assert(m->GetNodes().size() == c->GetQtNodes().size());


    assert(w->CanUndo());
    w->Undo(); //Route #1
    //cmd->Undo(); //Route #2
    assert(m->GetNodes().empty() && "After undoing the creation of a new node, the concept map must be empty again");
    assert(c->GetQtNodes().empty() && "After undoing the creation of a new node, the QtConceptMap must be empty again");
    assert(!w->CanUndo());
  }
  if (verbose) { TRACE("AddNode: Test creation of node from empty concept map, undo via command"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    assert(m);
    assert(m->GetNodes().empty() && "An empty concept map must not have nodes");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    assert(c);
    assert(c->GetQtNodes().empty() && "An empty QtConceptMap must not have nodes");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    assert(!w->CanUndo());
    const boost::shared_ptr<CommandCreateNewNode> cmd(
      new CommandCreateNewNode
    );

    assert(m->GetNodes().empty() && "The concept map must be empty");
    assert(c->GetQtNodes().empty() && "The QtConceptMap must be empty");
    assert(w->CanDoCommand(cmd));
    w->DoCommand(cmd);
    assert(!m->GetNodes().empty() && "After creation a new node, the previously empty concept map must have a node");
    assert(!c->GetQtNodes().empty() && "After creation a new node, the previously empty QtConceptMap must have a node");
    assert(w->CanUndo());
    //w->Undo(); //Route #1
    cmd->Undo(); //Route #2
    assert(m->GetNodes().empty() && "After undoing the creation of a new node, the concept map must be empty again");
    assert(c->GetQtNodes().empty() && "After undoing the creation of a new node, the QtConceptMap must be empty again");
    assert(!w->CanUndo());
  }

  if (verbose) { TRACE("DeleteNode: Test deletion of node from concept map"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    assert(m);
    assert(m->GetNodes().empty() && "An empty concept map must not have nodes");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    assert(c);
    assert(c->GetQtNodes().empty() && "An empty QtConceptMap must not have nodes");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node(
      new CommandCreateNewNode
    );

    assert(m->GetNodes().empty() && "Tthe concept map must be empty");
    assert(c->GetQtNodes().empty() && "The QtConceptMap must be empty");
    w->DoCommand(cmd_add_node);
    assert(m->GetNodes().size()   == 1 && "After creation a new node, the previously empty concept map must have a node");
    assert(c->GetQtNodes().size() == 1 && "After creation a new node, the previously empty QtConceptMap must have a node");

    const boost::shared_ptr<CommandDeleteNode> cmd_delete_node(
      new CommandDeleteNode(m->GetNodes()[0])
    );
    w->DoCommand(cmd_delete_node);
    assert(m->GetNodes().size()   == 0 && "After deleting the new node, the concept map must be empty");
    assert(c->GetQtNodes().size() == 0 && "After deleting the new node, the QtConceptMap must be empty");
    cmd_delete_node->Undo();
    assert(m->GetNodes().size()   == 1 && "After undoing the deletion of the only node, the previously empty concept map must have a node");
    assert(c->GetQtNodes().size() == 1 && "After undoing the deletion of the only node, the previously empty QtConceptMap must have a node");
  }
  if (verbose) { TRACE("Create two nodes and undo"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    const boost::shared_ptr<QtConceptMapWidget> w(new QtConceptMapWidget(c));
    const boost::shared_ptr<CommandCreateNewNode> cmd1(new CommandCreateNewNode);
    const boost::shared_ptr<CommandCreateNewNode> cmd2(new CommandCreateNewNode);

    assert(m->GetNodes().size() == 0);
    assert(c->GetQtNodes().size() == 0);
    w->DoCommand(cmd1);
    assert(m->GetNodes().size() == 1);
    assert(c->GetQtNodes().size() == 1);
    w->DoCommand(cmd2);
    assert(m->GetNodes().size() == 2);
    assert(c->GetQtNodes().size() == 2);
    w->Undo();
    assert(m->GetNodes().size() == 1);
    assert(c->GetQtNodes().size() == 1);
    w->Undo();
    assert(m->GetNodes().size() == 0);
    assert(c->GetQtNodes().size() == 0);
  }
  if (verbose) { TRACE("Create two nodes, selecting both (which is done automatically)"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    const boost::shared_ptr<QtConceptMapWidget> w(new QtConceptMapWidget(c));
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node1(new CommandCreateNewNode);
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node2(new CommandCreateNewNode);

    assert(c->GetScene()->selectedItems().size() == 0);
    assert(w->GetWidget().GetSelectedNodes().size() == 0);
    w->DoCommand(cmd_add_node1); //Adding a Node also selects it
    assert(c->GetScene()->selectedItems().size() == 1);
    assert(w->GetWidget().GetSelectedNodes().size() == 1);
    w->DoCommand(cmd_add_node2); //Adding a Node also selects it
    TRACE(c->GetScene()->selectedItems().size());
    TRACE(w->GetWidget().GetSelectedNodes().size());
    assert(c->GetScene()->selectedItems().size() == 2);
    assert(w->GetWidget().GetSelectedNodes().size() == 2);
  }
  if (verbose) { TRACE("Create two nodes and add an edge"); }
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory().Create() };
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    c->SetConceptMap(m);
    const boost::shared_ptr<QtConceptMapWidget> w(new QtConceptMapWidget(c));
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node1(new CommandCreateNewNode);
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node2(new CommandCreateNewNode);
    const boost::shared_ptr<CommandCreateNewEdge> cmd_add_edge(new CommandCreateNewEdge);
    assert(!w->CanDoCommand(cmd_add_edge));
    w->DoCommand(cmd_add_node1); //Adding a Node also selects it
    assert(!w->CanDoCommand(cmd_add_edge));
    w->DoCommand(cmd_add_node2); //Adding a Node also selects it
    assert(w->CanDoCommand(cmd_add_edge));
    assert(w->GetWidget().GetConceptMap()->GetEdges().size() == 0);
    w->DoCommand(cmd_add_edge); //Adding an Edge, deselects the rest
    assert(w->GetWidget().GetSelectedNodes().size() == 0);
    assert(w->GetWidget().GetSelectedEdges().size() == 1);
    assert(c->GetScene()->selectedItems().size() == 1); //The edge should be selected
    assert(dynamic_cast<QtEdge*>(c->GetScene()->selectedItems()[0]));
    assert(w->GetWidget().GetConceptMap()->GetEdges().size() == 1);
    assert(!w->CanDoCommand(cmd_add_edge));
  }
}
#endif
