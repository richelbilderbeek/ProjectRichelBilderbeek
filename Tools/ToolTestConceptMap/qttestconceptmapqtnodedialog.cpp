#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtnodedialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QGraphicsView>
#include <QKeyEvent>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapqtnodedialog.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "trace.h"
#include "ui_qttestconceptmapqtnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestQtNodeDialog::QtTestQtNodeDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtNodeDialog),
    m_dialog_left{new QtQtNodeDialog},
    m_dialog_right{new QtQtNodeDialog},
    m_view_left{new QtKeyboardFriendlyGraphicsView},
    m_view_right{new QtKeyboardFriendlyGraphicsView}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  {
    QGraphicsScene * const my_scene = new QGraphicsScene(this);
    m_view_left->setScene(my_scene);
    m_view_right->setScene(my_scene);
  }

  assert(!this->ui->here->layout());
  QGridLayout * const my_layout = new QGridLayout;
  ui->here->setLayout(my_layout);

  my_layout->addWidget(ui->widget_top,0,0,1,4);

  my_layout->addWidget(m_view_left.get(),1,0);
  my_layout->addWidget(m_view_right.get(),1,1);
  my_layout->addWidget(m_dialog_left.get(),1,2);
  my_layout->addWidget(m_dialog_right.get(),1,3);


  ui->box_test_index->setMinimum(0);
  ui->box_test_index->setMaximum(NodeFactory().GetNumberOfTests());
  ui->box_test_index->setValue(0);
  this->on_button_load_clicked();

}

ribi::cmap::QtTestQtNodeDialog::~QtTestQtNodeDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestQtNodeDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  assert(std::abs(m_view_left->scene()->items()[0]->x() - m_dialog_left->GetQtNode()->GetX()) < 1.0);
  assert(std::abs(m_view_left->scene()->items()[0]->y() - m_dialog_left->GetQtNode()->GetY()) < 1.0);
  #endif
}

boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtTestQtNodeDialog::GetQtNode() const noexcept
{
  assert(m_dialog_left->GetQtNode() == m_dialog_right->GetQtNode());
  return m_dialog_left->GetQtNode();
}

void ribi::cmap::QtTestQtNodeDialog::SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept
{
  assert(qtnode);
  assert(m_view_left);
  assert(m_view_left->scene());
  assert(m_view_right);
  assert(m_view_right->scene());
  assert(m_view_left->scene() == m_view_right->scene());
  if (!m_view_left->scene()->items().isEmpty())
  {
    const auto v = m_view_left->scene()->items();
    assert(v.count() == 1);
    m_view_left->scene()->removeItem(v[0]);
  }
  assert(m_view_left->scene()->items().isEmpty());
  m_dialog_left->SetQtNode(qtnode);
  m_dialog_right->SetQtNode(qtnode);
  this->m_view_left->scene()->addItem(qtnode.get());

  m_dialog_left->setMinimumHeight(QtQtNodeDialog::GetMinimumHeight(*qtnode));
  m_dialog_right->setMinimumHeight(QtQtNodeDialog::GetMinimumHeight(*qtnode));

}

void ribi::cmap::QtTestQtNodeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestQtNodeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtTestQtNodeDialog::Test started");
  const bool verbose{false};
  QtTestQtNodeDialog d;

  if (verbose) {TRACE("Loading all tests, three times");}
  {
    const int n{d.ui->box_test_index->maximum()};
    for (int i=0; i!=n; ++i)
    {
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
    }
  }
  if (verbose) {TRACE("QtNode must be the same in both dialogs");}
  {
    assert(d.m_dialog_left->GetQtNode());
    assert(d.m_dialog_left->GetQtNode() == d.m_dialog_right->GetQtNode());
  }
  if (verbose) {TRACE("QGraphicsView must contain exactly one item");}
  {
    assert(d.m_view_left->scene()->items().size() == 1);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtRoundedEditRectItem");}
  {
    const QGraphicsItem * const item = d.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    assert(qtitem);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtNode");}
  {
    const QGraphicsItem * const item = d.m_view_left->scene()->items()[0];
    const QtNode * qtnode = dynamic_cast<const QtNode*>(item);
    assert(qtnode);
  }
  if (verbose) {TRACE("QtNode its base class in the QGraphicsView must contain one line of text");}
  {
    const QGraphicsItem * const item = d.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    const auto v = qtrectitem->GetText();
    if (v.size() != 1)
    {
      TRACE(v.size());
      for (const auto& s: v) { TRACE(s); }
    }
    assert(v.size() == 1);
  }
  if (verbose) {TRACE("Text of Node must be equal to that of the QtNode in the QGraphicsView");}
  {
    const std::string s = d.m_dialog_left->GetQtNode()->GetNode()->GetConcept()->GetName();
    const QGraphicsItem * const item = d.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    const auto v = qtrectitem->GetText();
    const auto t = v[0];
    assert(s == t);
  }
  if (verbose) {TRACE("When changing the concept's name via Node, the QtNode must be changed as well");}
  {
    const std::string old_name{d.m_dialog_left->GetQtNode()->GetNode()->GetConcept()->GetName()};
    const std::string new_name{old_name + " (modified)"};
    d.m_dialog_left->GetQtNode()->GetNode()->GetConcept()->SetName(new_name);
    const QGraphicsItem * const item = d.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    const auto v = qtrectitem->GetText();
    const auto t = v[0];
    if (t != new_name)
    {
      TRACE(old_name);
      TRACE(t);
      TRACE(new_name);
    }
    assert(t == new_name);
  }
  assert(!"Yay");
  TRACE("ribi::cmap::QtTestQtNodeDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtTestQtNodeDialog::on_button_load_clicked() noexcept
{
  const int index = ui->box_test_index->value();
  const auto qtnode = boost::make_shared<QtNode>(
    NodeFactory().GetTest(index)
  );
  SetQtNode(qtnode);


}
