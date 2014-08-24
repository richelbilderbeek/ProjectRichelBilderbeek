#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtedgedialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapedge.h"
#include "conceptmapnode.h"
#include "grabber.h"
#include "qtimage.h"
#include "qtconceptmapedgefactory.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtedgedialog.h"
#include "qtconceptmapqtedgefactory.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "testtimer.h"
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
  m_from->SetCenterPos(0.0,0.0);
  m_to->SetCenterPos(10.0,100.0);

  {
    QGraphicsScene * const my_scene = new QGraphicsScene(this);
    m_view_left->setScene(my_scene);
    m_view_right->setScene(my_scene);

    my_scene->addItem(m_from.get()); //Remove in destructor
    my_scene->addItem(m_to.get()); //Remove in destructor
  }

  assert(!this->ui->here->layout());
  QGridLayout * const my_layout = new QGridLayout;
  ui->here->setLayout(my_layout);

  my_layout->addWidget(ui->widget_top,0,0,1,4);

  m_view_left->setMinimumWidth(300);
  m_view_right->setMinimumWidth(300);
  m_view_left->setMaximumHeight(300);
  m_view_right->setMaximumHeight(300);
  my_layout->addWidget(m_view_left.get(),1,0,1,1,Qt::AlignTop);
  my_layout->addWidget(m_view_right.get(),1,1,1,1,Qt::AlignTop);
  my_layout->addWidget(m_dialog_left.get(),1,2);
  my_layout->addWidget(m_dialog_right.get(),1,3);

  //my_layout->addItem(new QSpacerItem(1,1),2,0);
  //my_layout->addItem(new QSpacerItem(1,1),2,1);



  ui->box_test_index->setMinimum(0);
  ui->box_test_index->setMaximum(QtEdgeFactory().GetNumberOfTests() - 1); //-1 because first index has [0]
  ui->box_test_index->setValue(0);
  this->on_button_load_clicked();

  this->m_dialog_left->GetQtEdge()->GetFrom()->GetNode()->GetConcept()->SetName("From");
  this->m_dialog_left->GetQtEdge()->GetTo()->GetNode()->GetConcept()->SetName("To");
}

ribi::cmap::QtTestQtEdgeDialog::~QtTestQtEdgeDialog() noexcept
{
  SetQtEdge(nullptr);
  m_view_left->scene()->removeItem(m_from.get()); //Remove in destructor
  m_view_left->scene()->removeItem(m_to.get());   //Remove in destructor
  delete ui;
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

QImage ribi::cmap::QtTestQtEdgeDialog::GetUiView() const noexcept
{
  const auto scene = this->m_view_left->scene();
  // Create the image with the exact size of the shrunk scene
  QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
  // Start all pixels transparent
  image.fill(Qt::transparent);
  QPainter painter(&image);
  scene->render(&painter);
  return image;
}

double ribi::cmap::QtTestQtEdgeDialog::GetUiX() const noexcept
{
  return m_dialog_left->GetUiX();
}

double ribi::cmap::QtTestQtEdgeDialog::GetUiY() const noexcept
{
  return m_dialog_left->GetUiX();
}

void ribi::cmap::QtTestQtEdgeDialog::SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept
{
  assert(m_view_left);
  assert(m_view_left->scene());
  assert(m_view_right);
  assert(m_view_right->scene());
  assert(m_view_left->scene() == m_view_right->scene());
  assert(m_dialog_left->GetQtEdge() == m_dialog_right->GetQtEdge());
  const auto old_qtedge = m_dialog_left->GetQtEdge();

  if (old_qtedge)
  {
    m_view_left->scene()->removeItem(old_qtedge.get());
  }
  if (qtedge)
  {
    m_dialog_left->SetQtEdge(qtedge);
    m_dialog_right->SetQtEdge(qtedge);
    this->m_view_left->scene()->addItem(qtedge.get());

    m_dialog_left->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));
    m_dialog_right->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));
  }
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
  {
    QtImage();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{true};
  QtTestQtEdgeDialog dialog;
  const boost::shared_ptr<QtEdge> qtedge{dialog.GetQtEdge()};
  const int n = dialog.ui->box_test_index->maximum();
  if (verbose) { TRACE("Number of tests in GUI must be equal to the number of actual tests"); }
  {
    assert(n == QtEdgeFactory().GetNumberOfTests() - 1
      && "If there are x tests, the maximum test index is x-1");
  }
  if (verbose) { TRACE("Test index in GUI must be lower than the number of actual tests"); }
  {    
    for (int i=0; i!=10; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      assert(dialog.GetUiTestIndex() < QtEdgeFactory().GetNumberOfTests());
    }
  }
  if (verbose) { TRACE("Setting all test edges"); }
  {
    //QtTestQtEdgeDialog dialog;
    const int n{QtEdgeFactory().GetNumberOfTests()};
    for (int i=0; i!=n; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
    }
  }
  dialog.SetQtEdge(qtedge); //Put QtEdge in back again
  if (verbose) { TRACE("If the text of an QtEdge its center QtNode is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge()->GetNode()->GetConcept()->SetName("A");
    assert( dialog.GetQtEdge()->GetQtNode()->GetText()[0] == "A");
    dialog.GetQtEdge()->GetEdge()->GetNode()->GetConcept()->SetName("B");
    assert( dialog.GetQtEdge()->GetQtNode()->GetText()[0] == "B");
  }
  if (verbose) { TRACE("There is one item in the QGraphicsView"); }
  {
    assert(dialog.m_view_left->items().size() == 3);
  }

  //X
  if (verbose) { TRACE("X of QtTestQtEdgeDialog and QtEdge must match at creation"); }
  {
    const double ui_x{dialog.m_dialog_left->GetUiX()};
    const double qtedge_x{qtedge->GetQtNode()->GetCenterX()};
    assert(std::abs(ui_x - qtedge_x) < 2.0);
  }
  if (verbose) { TRACE("If X is set via QtTestQtEdgeDialog, QtEdge must sync"); }
  {
    const double old_x{dialog.m_dialog_left->GetUiX()};
    const double new_x{old_x + 10.0};
    dialog.m_dialog_left->SetUiX(new_x);
    assert(std::abs(new_x - qtedge->GetQtNode()->GetCenterX()) < 2.0);
  }
  if (verbose) { TRACE("If X is set via QtEdge, QtTestQtEdgeDialog must sync"); }
  {
    const double old_x{dialog.m_dialog_left->GetUiX()};
    const double new_x{old_x + 10.0};
    qtedge->GetQtNode()->SetCenterX(new_x);
    assert(std::abs(new_x - dialog.m_dialog_left->GetUiX()) < 2.0);
  }
  if (verbose) { TRACE("Grabbing QtEdge of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    //const QImage image_tmp{dialog.GetUiView()}; //Needed to force something more thorough than update and repaint
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    assert(image_before == image_after);
  }
  if (verbose) { TRACE("If the text of an QtEdge its center QtNode is changed, the Item must be updated"); }
  {
    //If the line below is needed, update() is not called automatically
    //const QImage image_tmp{dialog.GetUiView()}; //Needed to force something more thorough than update and repaint
    dialog.GetQtEdge()->GetEdge()->GetNode()->GetConcept()->SetName("A");
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge()->GetNode()->GetConcept()->SetName("B");
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the head arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge()->SetHeadArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge()->SetHeadArrow(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the tail arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge()->SetTailArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge()->SetTailArrow(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_from->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_from->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_to->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_to->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the QtNode an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_dialog_left->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_dialog_left->GetQtEdge()->GetQtNode()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> from{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_from)
    };

    const QImage image_before{dialog.GetUiView()};
    from->setX(from->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a member function, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a drag event, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
  }

  //assert(!"Refactor");
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
