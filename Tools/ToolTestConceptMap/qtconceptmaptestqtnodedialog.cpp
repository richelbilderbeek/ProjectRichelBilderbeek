#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptestqtnodedialog.h"

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
#include "ui_qtconceptmaptestqtnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestQtNodeDialog::QtConceptMapTestQtNodeDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConceptMapTestQtNodeDialog),
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

ribi::cmap::QtConceptMapTestQtNodeDialog::~QtConceptMapTestQtNodeDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtConceptMapTestQtNodeDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  assert(std::abs(m_view_left->scene()->items()[0]->x() - m_dialog_left->GetQtNode()->GetX()) < 1.0);
  assert(std::abs(m_view_left->scene()->items()[0]->y() - m_dialog_left->GetQtNode()->GetY()) < 1.0);
  #endif
}

boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtConceptMapTestQtNodeDialog::GetQtNode() const noexcept
{
  assert(m_dialog_left->GetQtNode() == m_dialog_right->GetQtNode());
  return m_dialog_left->GetQtNode();
}

void ribi::cmap::QtConceptMapTestQtNodeDialog::SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept
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

void ribi::cmap::QtConceptMapTestQtNodeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapTestQtNodeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtConceptMapTestQtNodeDialog::Test started");
  QtConceptMapTestQtNodeDialog d;
  const int n = d.ui->box_test_index->maximum();
  for (int i=0; i!=n; ++i)
  {
    d.ui->box_test_index->setValue(i);
    d.on_button_load_clicked();
    d.ui->box_test_index->setValue(i);
    d.on_button_load_clicked();
    d.ui->box_test_index->setValue(i);
    d.on_button_load_clicked();
  }

  TRACE("ribi::cmap::QtConceptMapTestQtNodeDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtConceptMapTestQtNodeDialog::on_button_load_clicked() noexcept
{
  const int index = ui->box_test_index->value();
  const auto qtnode = boost::make_shared<QtNode>(
    NodeFactory().GetTest(index)
  );
  SetQtNode(qtnode);


}
