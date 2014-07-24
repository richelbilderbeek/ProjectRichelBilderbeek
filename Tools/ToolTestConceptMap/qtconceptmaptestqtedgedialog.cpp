#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptestqtedgedialog.h"

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
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapqtedgedialog.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "trace.h"
#include "ui_qtconceptmaptestqtedgedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestQtEdgeDialog::QtConceptMapTestQtEdgeDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConceptMapTestQtEdgeDialog),
    m_dialog_left{new QtQtEdgeDialog},
    m_dialog_right{new QtQtEdgeDialog},
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

ribi::cmap::QtConceptMapTestQtEdgeDialog::~QtConceptMapTestQtEdgeDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtConceptMapTestQtEdgeDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  assert(std::abs(m_view_left->scene()->items()[0]->x() - m_dialog_left->GetQtEdge()->GetX()) < 1.0);
  assert(std::abs(m_view_left->scene()->items()[0]->y() - m_dialog_left->GetQtEdge()->GetY()) < 1.0);
  #endif
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtConceptMapTestQtEdgeDialog::GetQtEdge() const noexcept
{
  assert(m_dialog_left->GetQtEdge() == m_dialog_right->GetQtEdge());
  return m_dialog_left->GetQtEdge();
}

void ribi::cmap::QtConceptMapTestQtEdgeDialog::SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept
{
  assert(qtedge);
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
  m_dialog_left->SetQtEdge(qtedge);
  m_dialog_right->SetQtEdge(qtedge);
  this->m_view_left->scene()->addItem(qtedge.get());

  m_dialog_left->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));
  m_dialog_right->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));

}

void ribi::cmap::QtConceptMapTestQtEdgeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapTestQtEdgeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtConceptMapTestQtEdgeDialog::Test started");
  QtConceptMapTestQtEdgeDialog d;
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

  TRACE("ribi::cmap::QtConceptMapTestQtEdgeDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtConceptMapTestQtEdgeDialog::on_button_load_clicked() noexcept
{
  const int index = ui->box_test_index->value();
  const auto qtedge = boost::make_shared<QtEdge>(
    QtEdgeFactory().GetTest(index)
  );
  SetQtEdge(qtedge);


}
