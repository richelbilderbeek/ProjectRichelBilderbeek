#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtnodedialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
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
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodedialog.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtimage.h"
#include "testtimer.h"
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

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }


  this->on_button_load_clicked();

}

ribi::cmap::QtTestQtNodeDialog::~QtTestQtNodeDialog() noexcept
{
  delete ui;
}


boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtTestQtNodeDialog::GetQtNode() const noexcept
{
  assert(m_dialog_left->GetQtNode() == m_dialog_right->GetQtNode());
  return m_dialog_left->GetQtNode();
}

QImage ribi::cmap::QtTestQtNodeDialog::GetUiView() const noexcept
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
  QtRoundedEditRectItem();
  QtImage();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  QtTestQtNodeDialog dialog;

  if (verbose) {TRACE("Loading all tests, three times");}
  {
    const int n{dialog.ui->box_test_index->maximum()};
    for (int i=0; i!=n; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
    }
  }
  if (verbose) {TRACE("QtNode must be the same in both dialogs");}
  {
    assert(dialog.m_dialog_left->GetQtNode());
    assert(dialog.m_dialog_left->GetQtNode() == dialog.m_dialog_right->GetQtNode());
  }
  if (verbose) {TRACE("QGraphicsView must contain exactly one item");}
  {
    assert(dialog.m_view_left->scene()->items().size() == 1);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtRoundedEditRectItem");}
  {
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    assert(qtitem);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtNode");}
  {
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtNode * qtnode = dynamic_cast<const QtNode*>(item);
    assert(qtnode);
  }
  if (verbose) {TRACE("QtNode its base class in the QGraphicsView must contain one line of text");}
  {
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
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
    const std::string s = dialog.m_dialog_left->GetQtNode()->GetNode()->GetConcept()->GetName();
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    const auto v = qtrectitem->GetText();
    const auto t = v[0];
    assert(s == t);
  }
  if (verbose) {TRACE("When changing the concept's name via QtNode, the QtNodeDialog must be changed as well");}
  {
    const auto qtnode = dialog.m_dialog_left->GetQtNode();
    const std::string old_name{qtnode->GetNode()->GetConcept()->GetName()};
    const std::string new_name{old_name + " (modified)"};
    qtnode->GetNode()->GetConcept()->SetName(new_name);
    const auto t = dialog.m_dialog_left->GetUiName();
    assert(t == new_name);
  }
  if (verbose) {TRACE("When changing the concept's name via QtNodeDialog, the QtNode must be changed as well");}
  {
    const auto old_name = dialog.m_dialog_left->GetUiName();
    const std::string new_name{old_name + " (modified)"};
    dialog.m_dialog_left->SetUiName(new_name);
    QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    QtRoundedEditRectItem * const qtrectitem = dynamic_cast<QtRoundedEditRectItem*>(item);
    const std::string new_name_again = qtrectitem->GetText()[0];
    assert(new_name_again == new_name);
  }
  if (verbose) { TRACE("Grabbing QtNode of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    assert(image_before == image_after);
  }
  if (verbose) { TRACE("If the text of an QtNode its center QtNode is changed, the Item must be updated"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_before{dialog.GetUiView()};

    dialog.GetQtNode()->GetNode()->GetConcept()->SetName("A");
    dialog.GetQtNode()->GetNode()->GetConcept()->SetName("B");

    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("QGraphicsScene must have one item"); }
  {
    assert(dialog.m_view_left->scene()->items().size() == 1);
  }
  if (verbose) { TRACE("Setting X via UI should result in an update of the QtRoundedEditRectItem in the QGraphicsScene"); }
  {
    const double old_x{dialog.m_dialog_left->GetUiX()};
    const double new_x{old_x + 10.0};
    dialog.m_dialog_left->SetUiX(new_x);
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    assert(std::abs(qtrectitem->GetCenterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("Setting Y via UI should result in an update of the QtRoundedEditRectItem in the QGraphicsScene"); }
  {
    const double old_y{dialog.m_dialog_left->GetUiY()};
    const double new_y{old_y + 10.0};
    dialog.m_dialog_left->SetUiY(new_y);
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    assert(std::abs(qtrectitem->GetCenterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("Setting Name via UI should result in an update of the QtRoundedEditRectItem in the QGraphicsScene"); }
  {
    const std::string old_name{dialog.m_dialog_left->GetUiName()};
    const std::string new_name{old_name + " (modified)"};
    dialog.m_dialog_left->SetUiName(new_name);
    const QGraphicsItem * const item = dialog.m_view_left->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    assert(qtrectitem->GetText()[0] == new_name);
  }
}
#endif

void ribi::cmap::QtTestQtNodeDialog::on_button_load_clicked() noexcept
{
  const int index{ui->box_test_index->value()};
  const auto qtnode = boost::make_shared<QtNode>(
    NodeFactory().GetTest(index)
  );
  SetQtNode(qtnode);
}
