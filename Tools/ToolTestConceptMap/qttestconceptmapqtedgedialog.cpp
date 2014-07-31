#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtedgedialog.h"

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
#include "qtconceptmapedgefactory.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapqtedgedialog.h"
#include "qtconceptmapqtedgefactory.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "trace.h"
#include "ui_qttestconceptmapqtedgedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestQtEdgeDialog::QtTestQtEdgeDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtEdgeDialog),
    m_dialog_left{new QtQtEdgeDialog},
    m_dialog_right{new QtQtEdgeDialog},
    m_from{QtNodeFactory().GetTest(1)},
    m_to{QtNodeFactory().GetTest(1)},
    m_view_left{new QtKeyboardFriendlyGraphicsView},
    m_view_right{new QtKeyboardFriendlyGraphicsView}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  m_from->SetPos(0.0,0.0);
  m_to->SetPos(10.0,100.0);
  {
    QGraphicsScene * const my_scene = new QGraphicsScene(this);
    m_view_left->setScene(my_scene);
    m_view_right->setScene(my_scene);

    my_scene->addItem(m_from.get());
    my_scene->addItem(m_to.get());
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
  ui->box_test_index->setMaximum(QtEdgeFactory().GetNumberOfTests() - 1); //-1 because first index has [0]
  ui->box_test_index->setValue(0);
  this->on_button_load_clicked();

  this->m_dialog_left->GetQtEdge()->GetFrom()->GetNode()->GetConcept()->SetName("From");
  this->m_dialog_left->GetQtEdge()->GetTo()->GetNode()->GetConcept()->SetName("To");
}

ribi::cmap::QtTestQtEdgeDialog::~QtTestQtEdgeDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestQtEdgeDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  assert(std::abs(m_view_left->scene()->items()[0]->x() - m_dialog_left->GetQtEdge()->GetX()) < 1.0);
  assert(std::abs(m_view_left->scene()->items()[0]->y() - m_dialog_left->GetQtEdge()->GetY()) < 1.0);
  #endif
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtTestQtEdgeDialog::GetQtEdge() const noexcept
{
  assert(m_dialog_left->GetQtEdge() == m_dialog_right->GetQtEdge());
  return m_dialog_left->GetQtEdge();
}

int ribi::cmap::QtTestQtEdgeDialog::GetUiTestIndex() const noexcept
{
  return ui->box_test_index->value();
}

void ribi::cmap::QtTestQtEdgeDialog::SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept
{
  assert(qtedge);
  assert(m_view_left);
  assert(m_view_left->scene());
  assert(m_view_right);
  assert(m_view_right->scene());
  assert(m_view_left->scene() == m_view_right->scene());
  assert(m_dialog_left->GetQtEdge() == m_dialog_right->GetQtEdge());
  const auto old_qtedge = m_dialog_left->GetQtEdge();

  //if (!m_view_left->scene()->items().isEmpty())
  if (old_qtedge)
  {
    //const QList<QGraphicsItem *> qlist = m_view_left->scene()->items();
    //const int old_index = qlist.indexOf(m_edge.get());
    //qlist.removeAt(old_index);
    //m_view_left->scene()->removeItem(v[0]);
    m_view_left->scene()->removeItem(old_qtedge.get());
  }
  m_dialog_left->SetQtEdge(qtedge);
  m_dialog_right->SetQtEdge(qtedge);
  this->m_view_left->scene()->addItem(qtedge.get());

  m_dialog_left->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));
  m_dialog_right->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));

}

void ribi::cmap::QtTestQtEdgeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestQtEdgeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtTestQtEdgeDialog::Test started");
  const bool verbose{false};
  QtTestQtEdgeDialog d;
  const int n = d.ui->box_test_index->maximum();
  if (verbose) { TRACE("Number of tests in GUI must be equal to the number of actual tests"); }
  {
    assert(n == QtEdgeFactory().GetNumberOfTests() - 1
      && "If there are x tests, the maximum test index is x-1");
  }
  if (verbose) { TRACE("Test index in GUI must be lower than the number of actual tests"); }
  {    
    for (int i=0; i!=10; ++i)
    {
      d.ui->box_test_index->setValue(i);
      assert(d.GetUiTestIndex() < QtEdgeFactory().GetNumberOfTests());
    }
  }
  if (verbose) { TRACE("Setting all test edges, multiple times"); }
  {
    for (int i=0; i!=10; ++i)
    {
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
      d.ui->box_test_index->setValue(i);
      d.on_button_load_clicked();
    }
  }

  TRACE("ribi::cmap::QtTestQtEdgeDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtTestQtEdgeDialog::on_button_load_clicked() noexcept
{
  const int index = ui->box_test_index->value();
  assert(m_from);
  assert(m_to);
  assert(index >= 0);
  assert(index < QtEdgeFactory().GetNumberOfTests());
  const auto qtedge = QtEdgeFactory().GetTest(index,m_from,m_to);

  SetQtEdge(qtedge);
}
