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
#include "qtconceptmapnode.h"

#include <cassert>
#include <climits>

#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

#include <QCursor>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>

#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "container.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapratestrategy.h"
#include "qtitemdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtNode::QtNode(
  const boost::shared_ptr<Node> node
  //const boost::shared_ptr<QtItemDisplayStrategy> concept_item
)
  : QtConceptMapElement(),
    //m_signal_display_changed{},
    m_signal_base_changed{},
    m_signal_node_changed{},
    //m_signal_node_requests_rate_concept{},
    //m_signal_node_requests_rate_examples{},
    //m_display_strategy(concept_item),
    //m_contour_pen(concept_item->GetContourPen()),
    //m_focus_pen(concept_item->GetFocusPen()),
    m_node{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(node);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  this->SetPadding(Base::Padding(1.0,6.0,1.0,2.0));

  this->setAcceptHoverEvents(true);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );


  SetNode(node);

  m_signal_pos_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnPosChanged,this,boost::lambda::_1)
  );

  this->m_signal_text_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnTextChanged,this,boost::lambda::_1)
  );

  /*

  m_display_strategy->m_signal_item_has_updated.connect(
    boost::bind(
      &ribi::cmap::QtNode::OnItemHasUpdated,this)
  );

  m_display_strategy->m_signal_request_scene_update.connect(
    boost::bind(
      &ribi::cmap::QtNode::OnRequestsSceneUpdate,
      this
    )
  );

  if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(m_display_strategy.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtConceptMapElement::OnConceptRequestsEdit,
        this
      )
    );
  }

  if (QtRateStrategy * rate_concept = dynamic_cast<QtRateStrategy*>(m_display_strategy.get()))
  {
    rate_concept->m_signal_request_rate_concept.connect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateConcept,
        this
      )
    );
    rate_concept->m_signal_request_rate_examples.connect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateExamples,
        this
      )
    );
  }
  */

  CheckMe();
}

ribi::cmap::QtNode::~QtNode() noexcept
{
  /*
  m_display_strategy->m_signal_position_changed.disconnect(
    boost::bind(&ribi::cmap::QtNode::SetPos,this,boost::lambda::_1,boost::lambda::_2)
  );

  m_node->m_signal_concept_changed.disconnect(
    boost::bind(&ribi::cmap::QtNode::OnNodeChanged,this,boost::lambda::_1)
  );
  m_node->m_signal_x_changed.disconnect(
    boost::bind(&ribi::cmap::QtNode::OnXchanged,this,boost::lambda::_1)
  );
  m_node->m_signal_y_changed.disconnect(
    boost::bind(&ribi::cmap::QtNode::OnYchanged,this,boost::lambda::_1)
  );

  m_display_strategy->m_signal_item_has_updated.disconnect(
    boost::bind(
      &ribi::cmap::QtNode::OnItemHasUpdated,this)
  );

  m_display_strategy->m_signal_request_scene_update.disconnect(
    boost::bind(
      &ribi::cmap::QtNode::OnRequestsSceneUpdate,
      this
    )
  );

  if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(m_display_strategy.get()))
  {
    edit_concept->m_signal_request_edit.disconnect(
      boost::bind(
        &QtConceptMapElement::OnConceptRequestsEdit,
        this
      )
    );
  }

  if (QtRateStrategy * rate_concept = dynamic_cast<QtRateStrategy*>(m_display_strategy.get()))
  {
    rate_concept->m_signal_request_rate_concept.disconnect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateConcept,
        this
      )
    );
    rate_concept->m_signal_request_rate_examples.disconnect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateExamples,
        this
      )
    );
  }
  */
}

/*
QRectF ribi::cmap::QtNode::boundingRect() const
{
  //TRACE(m_concept_item->boundingRect().width());
  //TRACE(QtConceptMapItem::boundingRect().width());

  //Cannot check here
  //assert(m_concept_item->boundingRect() == QtConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
  return m_display_strategy->boundingRect();
  //return QtConceptMapItem::boundingRect(); //Bypassed going via m_concept_item
}
*/
/*
QBrush ribi::cmap::QtNode::brush() const
{
  return m_display_strategy->brush();
}
*/

void ribi::cmap::QtNode::CheckMe() const noexcept
{
  #ifndef NDEBUG
  const double epsilon = 2.0;

  assert(std::abs(GetPos().x() - GetNode()->GetX()) < epsilon);
  assert(std::abs(GetPos().y() - GetNode()->GetY()) < epsilon);

  assert(GetText().size() == 1);

  if (GetNode())
  {
    const auto s = this->GetNode()->GetConcept()->GetName();
    const std::vector<std::string> w{GetText()};
    assert(w[0] == s);
  }

  assert(flags() & QGraphicsItem::ItemIsFocusable);
  assert(flags() & QGraphicsItem::ItemIsSelectable);
  assert(flags() & QGraphicsItem::ItemIsMovable);
  assert(this->acceptHoverEvents()); //Must remove the 's' in Qt5?
  #endif
}


void ribi::cmap::QtNode::DisableAll()
{
  this->setEnabled(false);
  this->setVisible(false);
  //this->m_display_strategy->setEnabled(false);
  //this->m_display_strategy->setVisible(false);
}

void ribi::cmap::QtNode::EnableAll()
{
  this->setEnabled(true);
  this->setVisible(true);
  //this->m_display_strategy->setEnabled(true);
  //this->m_display_strategy->setVisible(true);
}

void ribi::cmap::QtNode::focusInEvent(QFocusEvent*)
{
  //m_display_strategy->SetContourPen(m_display_strategy->GetFocusPen()); //Updates itself
  //assert(!m_display_strategy->hasFocus());
  ///?maybe update?
  assert(hasFocus());
}

void ribi::cmap::QtNode::focusOutEvent(QFocusEvent*)
{
  //m_display_strategy->SetContourPen(m_display_strategy->GetContourPen()); //Updates itself
  //m_signal_item_has_updated(0); //causes Examples to get hidden
  ///?maybe update?
  assert(!hasFocus());
}

boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::QtNode::GetNode() const noexcept
{
  const auto p = m_node;
  assert(p);
  return p;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::QtNode::GetNode() noexcept
{
  const auto p = m_node;
  assert(p);
  return p;
}

/*
void ribi::cmap::QtNode::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
  //m_concept_item->hoverMoveEvent(e);
  //Won't cause a hover, because the concept item
  //is not visible??
}
*/


void ribi::cmap::QtNode::keyPressEvent(QKeyEvent *event) noexcept
{
  //assert(m_display_strategy);
  //assert(m_display_strategy->GetConcept());
  //m_display_strategy->keyPressEvent(event);
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_F2:
    return;
  }
  QtConceptMapElement::keyPressEvent(event);
}

void ribi::cmap::QtNode::OnItemHasUpdated()
{
  //this->setRect(m_display_strategy->boundingRect());

  //Cannot check here, as setRect triggers this member function
  //assert(m_concept_item->boundingRect() == QtConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
  this->update();
  //this->m_signal_item_has_updated(this);
}

/*
void ribi::cmap::QtNode::OnItemRequestsRateConcept()
{
  m_signal_node_requests_rate_concept(this);
}

void ribi::cmap::QtNode::OnItemRequestsRateExamples()
{
  m_signal_node_requests_rate_examples(this);
}
*/

void ribi::cmap::QtNode::OnConceptChanged(Node * const node) noexcept
{
  //Node changed, sync QtRoundedRectItem
  assert(node);
  assert(node == m_node.get());
  const std::string new_str = node->GetConcept()->GetName();
  const std::vector<std::string> new_text{new_str};
  assert(new_text.size() == 1);
  this->SetText(new_text);
  assert(GetText() == new_text);
}

void ribi::cmap::QtNode::OnPosChanged(const QtRoundedRectItem * const item) noexcept
{
  //QtRoundedRectItem changed, sync Node
  assert(item);
  const auto new_pos = item->GetPos();
  m_node->SetPos(new_pos.x(),new_pos.y());
}

void ribi::cmap::QtNode::OnTextChanged(const QtRoundedRectItem * const item) noexcept
{
  //QtRoundedRectItem changed, sync Node
  assert(item);
  assert(item == this);
  const std::vector<std::string> new_text{GetText()};
  assert((new_text.size() == 1 || new_text.size() != 1)
    && "new_text can be of any number of lines, as QtRoundedEditRect supports this"
  );
  const std::string s{Container().Concatenate(new_text)};
  assert(std::count(std::begin(s),std::end(s),'\n') ==  0 && "Keep it single-line");
  m_node->GetConcept()->SetName(s);
}


void ribi::cmap::QtNode::OnXchanged(Node * const node) noexcept
{
  //Node changed, sync QtRoundedRectItem
  assert(node);
  SetX(node->GetX());
}

void ribi::cmap::QtNode::OnYchanged(Node * const node) noexcept
{
  //Node changed, sync QtRoundedRectItem
  assert(node);
  SetY(node->GetY());
}


//void ribi::cmap::QtNode::OnRequestsSceneUpdate()
//{
  //this->m_signal_request_scene_update();
//}

void ribi::cmap::QtNode::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget
) noexcept
{

  //assert(m_display_strategy);
  //assert(!m_display_strategy->hasFocus());
  //assert(!m_display_strategy->isSelected());

  //this->m_display_strategy->SetName(this->GetNode()->GetConcept()->GetName());


  //Only QtEditStrategy actually modifies the position of the concept items
  /*
  if (dynamic_cast<QtEditStrategy*>(m_display_strategy.get()))
  {
    //Notifies the GUI-independent collaborators
    this->m_display_strategy->SetPos(x(),y());
  }
  */

  //assert(this->boundingRect() == m_display_strategy->boundingRect()
  //  && "Keep bounding rects in sync (but is this check still relevent?) 2013-07-06");

  //m_display_strategy->paint(painter,item,widget);
  Base::paint(painter,item,widget);
  /*
  if (!GetNode()->GetConcept()->GetExamples()->Get().empty())
  {
    painter->setBrush(m_display_strategy->GetIndicatorBrush());
    painter->setPen(m_display_strategy->GetIndicatorPen());
    //Draw indicator that a concept has examples in it
    painter->drawRect(
      GetRect().right() - 5.0,
      GetRect().top() + 3.0,
      3.0,
      3.0
      );
  }
  */

  //Check if item can move (as the center node cannot)
  #ifdef BRAINWEAVER_MOVE_ITEMS_ON_COLLISION
  if (this->flags() & QGraphicsItem::ItemIsMovable)
  {
    //Item can move, check for collision
    const QList<QGraphicsItem*> others = collidingItems();
    std::for_each(others.begin(),others.end(),
      [this](const QGraphicsItem* const other_item)
      {
        assert(other_item);
        if (const QtNode* const other_node = dynamic_cast<const QtNode*>(other_item))
        {
          const double dx = x() - other_node->x() > 0.0 ? 1.0 : -1.0;
          const double dy = y() - other_node->y() > 0.0 ? 1.0 : -1.0;
          //assert(this->flags() & QGraphicsItem::ItemIsMovable); //Not true for center node
          this->setPos( this->x()  + dx, this->y()  + dy);
        }
      }
    );
  }
  #endif
}

void ribi::cmap::QtNode::SetNode(const boost::shared_ptr<Node>& node)
{
  const bool verbose{false};

  assert(node);
  if (m_node == node)
  {
    CheckMe();
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting node '" << node->ToStr() << "'\n";
  }
  const auto concept_after = node->GetConcept();
  const auto x_after = node->GetX();
  const auto y_after = node->GetY();

  bool concept_changed{true};
  bool x_changed{true};
  bool y_changed{true};

  if (m_node)
  {
    const auto concept_before = m_node->GetConcept();
    const auto x_before = m_node->GetX();
    const auto y_before = m_node->GetY();

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
    m_node->m_signal_concept_changed.disconnect(
      boost::bind(&ribi::cmap::QtNode::OnConceptChanged,this,boost::lambda::_1)
    );
    m_node->m_signal_x_changed.disconnect(
      boost::bind(&ribi::cmap::QtNode::OnXchanged,this,boost::lambda::_1)
    );
    m_node->m_signal_y_changed.disconnect(
      boost::bind(&ribi::cmap::QtNode::OnYchanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_node = node;


  assert(m_node->GetConcept() == concept_after );
  assert(m_node->GetX() == x_after );
  assert(m_node->GetY() == y_after);

  //SetPos(m_node->GetX(),m_node->GetY());
  //assert(GetPos().x() == m_node->GetX());
  //assert(GetPos().y() == m_node->GetY());

  m_node->m_signal_concept_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnConceptChanged,this,boost::lambda::_1)
  );
  m_node->m_signal_x_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnXchanged,this,boost::lambda::_1)
  );
  m_node->m_signal_y_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnYchanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (concept_changed)
  {
    m_node->m_signal_concept_changed(m_node.get());
  }
  if (x_changed)
  {
    m_node->m_signal_x_changed(m_node.get());
  }
  if (y_changed)
  {
    m_node->m_signal_y_changed(m_node.get());
  }

  assert( node ==  m_node);
  assert(*node == *m_node);
  CheckMe();
}

/*
void ribi::cmap::QtNode::SetName(const std::string& name) noexcept
{
  m_node->GetConcept()->SetName(name);
}
*/




#ifndef NDEBUG
void ribi::cmap::QtNode::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtNode::Test");
  const bool verbose{false};
  const double max_error = 2.0;

  if (verbose) { TRACE("QtNode can be converted to QtRoundedEditRectItem") }
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> edit_rect{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    assert(edit_rect);
    assert(qtnode == edit_rect);
  }

  if (verbose) { TRACE("Test X coordinat in Node and QtRoundedEditRectItem being equal at creation") }
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> edit_rect{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    const auto node = qtnode->GetNode();
    const double node_x = node->GetX();
    const double edit_rect_x = edit_rect->GetX();
    assert(std::abs(node_x - edit_rect_x) < max_error);
  }
  if (verbose) { TRACE("Test Y coordinat in Node and QtRoundedEditRectItem being equal at creation") }
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> edit_rect{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    const auto node = qtnode->GetNode();
    const double node_y = node->GetY();
    const double edit_rect_y = edit_rect->GetY();
    assert(std::abs(node_y - edit_rect_y) < max_error);
  }
  if (verbose) { TRACE("Test text in Node and QtRoundedEditRectItem being equal at creation") }
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> edit_rect{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    const auto node = qtnode->GetNode();
    const std::string node_text{node->GetConcept()->GetName()};
    const std::string edit_rect_text{Container().Concatenate(edit_rect->GetText())};
    if (node_text != edit_rect_text)
    {
      TRACE(node_text);
      TRACE(edit_rect_text);
    }
    assert(node_text == edit_rect_text);
  }
  if (verbose) {TRACE("When changing the concept's name via Node, the QtNode must be changed as well");}
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> qtrectitem{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    const std::string old_name{qtnode->GetNode()->GetConcept()->GetName()};
    const std::string new_name{old_name + " (modified)"};
    qtnode->GetNode()->GetConcept()->SetName(new_name);
    const auto v = qtrectitem->GetText();
    const auto t = v[0];
    assert(t == new_name);
  }
  if (verbose) {TRACE("When changing the concept's name via QtNode, the Node must be changed as well");}
  {
    const auto qtnode = QtNodeFactory().GetTest(1);
    const boost::shared_ptr<QtRoundedEditRectItem> qtrectitem{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtnode)};
    const std::string old_name = qtrectitem->GetText()[0];
    const std::string new_name{old_name + " (modified)"};
    qtrectitem->SetText( { new_name } );
    const std::string new_name_again{qtnode->GetNode()->GetConcept()->GetName()};
    assert(new_name_again == new_name);
  }


  #ifdef DISABLED_FOR_NOW_20140730
  {
    {
      const double new_x = 12.34;
      const double new_y = 43.21;

      //Change via node
      assert(node);
      node->SetX(new_x);
      node->SetY(new_y);

      const double node_x = node->GetX();
      const double qtnode_x = qtnode->GetPos().x();

      if (std::abs(node_x - qtnode_x) >= max_error)
      {
        TRACE(node_x);
        TRACE(qtnode_x);
      }
      assert(std::abs(node_x - qtnode_x) < max_error
       && "X coordinat must be in sync");
      const double node_y = node->GetY();
      const double qtnode_y = qtnode->GetPos().y();

      assert(node_y == qtnode_y
       && "Y coordinat must be in sync");
    }
    //Change via Qt node
    {
      const double new_x = 123.456;
      const double new_y = 654.321;

      qtnode->SetPos(new_x,new_y);

      const double node_x = node->GetX();
      const double qtnode_x = qtnode->GetPos().x();

      assert(std::abs(node_x - qtnode_x) < max_error
       && "X coordinat must be in sync");
      const double node_y = node->GetY();
      const double qtnode_y = qtnode->GetPos().y();

      assert(std::abs(node_y - qtnode_y) < max_error
       && "Y coordinat must be in sync");
    }

  }
  #endif

  TRACE("Finished ribi::cmap::QtNode::Test successfully");
}
#endif

std::string ribi::cmap::QtNode::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
}

std::ostream& ribi::cmap::operator<<(std::ostream& os, const QtNode& qtnode) noexcept
{
  os
    << (*qtnode.GetNode())
    //<< " (" << (*qtnode.GetDisplayStrategy()) << ")"
  ;
  return os;
}
