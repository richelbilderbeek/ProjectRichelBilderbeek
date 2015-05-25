//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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

#include <QDesktopWidget>
#include <QVBoxLayout>

#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapqtnode.h"
#include "qtitemdisplaystrategy.h"
#include "qtroundededitrectitemdialog.h"

#include "testtimer.h"
#include "trace.h"

#include "ui_qtconceptmapqtnodedialog.h"
//#include "ui_qtconceptmapnodedialog.h"
//#include "ui_qtroundededitrectitemdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtQtNodeDialog::QtQtNodeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtQtNodeDialog),
  m_qtnode{},
  m_qtnodedialog{},
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
    const boost::shared_ptr<QtNodeDialog> d{new QtNodeDialog};
    assert(d);
    m_qtnodedialog = d;
    this->layout()->addWidget(m_qtnodedialog.get());
  }
  {
    assert(this->layout());
    const boost::shared_ptr<QtRoundedEditRectItemDialog> d{new QtRoundedEditRectItemDialog};
    m_qtroundededitrectitem_dialog = d;
    this->layout()->addWidget(m_qtroundededitrectitem_dialog.get());
  }

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
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

std::string ribi::cmap::QtQtNodeDialog::GetUiName() const noexcept
{
  return m_qtnodedialog->GetUiName();
}

double ribi::cmap::QtQtNodeDialog::GetUiX() const noexcept
{
  return m_qtnodedialog->GetUiX();
}

double ribi::cmap::QtQtNodeDialog::GetUiY() const noexcept
{
  return m_qtnodedialog->GetUiY();
}

void ribi::cmap::QtQtNodeDialog::OnNodeChanged(QtNode * const
#ifndef NDEBUG
  qtnode
#endif // NDEBUG
) noexcept
{
  assert( qtnode ==  m_qtnode.get());
  assert(*qtnode == *m_qtnode);
  m_qtroundededitrectitem_dialog->SetItem(m_qtnode);
}

void ribi::cmap::QtQtNodeDialog::OnQtRoundedRectItemChanged(QtNode * const qtnode) noexcept
{
  //Emit
  m_qtnodedialog->SetNode(qtnode->GetNode());

  /*
  if (node == m_node) return;
  if (*node == *m_node) return;
  assert(std::abs(m_node->GetX() - this->GetPos().x()) < 2.0); //Allow two maximal rounding off errors
  assert(std::abs(m_node->GetY() - this->GetPos().y()) < 2.0); //Allow two maximal rounding off errors
  //if (node->GetX() != m_node->GetX())
  {
    //const double new_x = node->GetX();
    //m_node->SetX(new_x);
    this->SetPos(node->GetX(),this->GetPos().y());
  }
  //if (node->GetY() != m_node->GetY())
  {
    //const double new_y = node->GetY();
    //m_node->SetY(new_y);
    this->SetPos(this->GetPos().x(),node->GetY());
  }
  //if (node->GetConcept()->GetName() != m_node->GetConcept()->GetName())
  {
    //const auto new_text = node->GetConcept()->GetName();
    //m_node->GetConcept()->SetName(new_text);
    this->SetText(Container().SeperateString(node->GetConcept()->GetName(),'\n'));
  }
  */
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

void ribi::cmap::QtQtNodeDialog::SetUiName(const std::string& name) noexcept
{
  m_qtnodedialog->SetUiName(name);
}

void ribi::cmap::QtQtNodeDialog::SetUiX(const double x) noexcept
{
  m_qtnodedialog->SetUiX(x);
}

void ribi::cmap::QtQtNodeDialog::SetUiY(const double y) noexcept
{
  m_qtnodedialog->SetUiY(y);
}

#ifndef NDEBUG
void ribi::cmap::QtQtNodeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtNodeFactory();
    QtNodeFactory().GetTest(1);
    QtNodeDialog();
    QtRoundedEditRectItemDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  QtQtNodeDialog dialog;
  const auto node = NodeFactory().GetTest(1);
  const boost::shared_ptr<QtNode> qtnode{new QtNode(node)};
  dialog.SetQtNode(qtnode);
  if (verbose) { TRACE("SetUiX and GetUiX must be symmetric"); }
  {
    const double old_x{dialog.GetUiX()};
    const double new_x{old_x + 10.0};
    dialog.SetUiX(new_x);
    assert(std::abs(dialog.GetUiX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetUiY and GetUiY must be symmetric"); }
  {
    const double old_y{dialog.GetUiY()};
    const double new_y{old_y + 10.0};
    dialog.SetUiY(new_y);
    assert(std::abs(dialog.GetUiY() - new_y) < 2.0);
  }
}
#endif
