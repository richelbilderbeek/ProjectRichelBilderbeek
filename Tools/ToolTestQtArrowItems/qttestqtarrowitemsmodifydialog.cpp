#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtarrowitemsmodifydialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>
#include <QTimer>

#include "qtquadbezierarrowitem.h"
#include "qtquadbezierarrowdialog.h"
#include "ribi_random.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestqtarrowitemsmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtArrowItemsModifyDialog::QtTestQtArrowItemsModifyDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtArrowItemsModifyDialog),
    m_dialog_left(new QtQuadBezierArrowDialog),
    m_dialog_right(new QtQuadBezierArrowDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  for (const auto& widget: { ui->widget_left,ui->widget_right })
  {
    if (!widget->layout())
    {
      QVBoxLayout * const layout = new QVBoxLayout;
      widget->setLayout(layout);
    }
  }
  ui->widget_left->layout()->addWidget(m_dialog_left.get());
  ui->widget_right->layout()->addWidget(m_dialog_right.get());

  {
    QTimer * const timer = new QTimer(this);
    QObject::connect(timer,&QTimer::timeout,this,&ribi::QtTestQtArrowItemsModifyDialog::DoSomethingRandom);
    timer->setInterval(100);
    timer->start();
  }

  {
    auto from = new QGraphicsSimpleTextItem("From");
    const bool tail = false;
    auto mid = new QGraphicsSimpleTextItem("Mid");
    const bool head = true;
    const auto to = new QGraphicsSimpleTextItem("To");

    boost::shared_ptr<QtQuadBezierArrowItem> item{new QtQuadBezierArrowItem(from,tail,mid,head,to)};
    item->SetFromPos(0.0,0.0);
    item->SetMidPos(75.0,50.0);
    item->SetToPos(100.0,100.0);
    SetArrow(item);
  }

}

ribi::QtTestQtArrowItemsModifyDialog::~QtTestQtArrowItemsModifyDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::QtQuadBezierArrowItem> ribi::QtTestQtArrowItemsModifyDialog::GetArrow() const noexcept
{
  assert(m_dialog_left->GetArrow() == m_dialog_right->GetArrow());
  return m_dialog_left->GetArrow();
}

void ribi::QtTestQtArrowItemsModifyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

boost::shared_ptr<ribi::QtQuadBezierArrowItem> ribi::QtTestQtArrowItemsModifyDialog::CreateRandomArrow() noexcept
{

  auto from = new QGraphicsSimpleTextItem("From");
  const bool tail{Random().GetBool()};
  auto mid = new QGraphicsSimpleTextItem("Mid");
  const bool head{Random().GetBool()};
  auto to = new QGraphicsSimpleTextItem("To");
  boost::shared_ptr<QtQuadBezierArrowItem> item{new QtQuadBezierArrowItem(from,tail,mid,head,to)};
  item->SetFromPos(Random().GetFraction() * 100.0,Random().GetFraction() * 100.0);
  item->SetMidPos(Random().GetFraction() * 100.0,Random().GetFraction() * 100.0);
  item->SetToPos(Random().GetFraction() * 100.0,Random().GetFraction() * 100.0);
  return item;
}

void ribi::QtTestQtArrowItemsModifyDialog::DoSomethingRandom() noexcept
{

}

void ribi::QtTestQtArrowItemsModifyDialog::on_button_set_item_clicked()
{
  const auto item = CreateRandomArrow();
  assert(item);
  SetArrow(item);
}

void ribi::QtTestQtArrowItemsModifyDialog::SetArrow(const boost::shared_ptr<QtQuadBezierArrowItem>& arrow) noexcept
{
  m_dialog_left->SetArrow(arrow);
  m_dialog_right->SetArrow(arrow);

  if (!ui->view_left->scene())
  {
    assert(!ui->view_left->scene());
    assert(!ui->view_right->scene());
    QGraphicsScene * const scene = new QGraphicsScene;
    ui->view_left->setScene(scene);
    ui->view_right->setScene(scene);
  }
  assert(ui->view_left->scene());
  assert(ui->view_right->scene());
  assert(ui->view_left->scene() == ui->view_right->scene());
  ui->view_left->scene()->clear();
  ui->view_left->scene()->addItem(arrow.get());

}

#ifndef NDEBUG
void ribi::QtTestQtArrowItemsModifyDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Random();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  QtTestQtArrowItemsModifyDialog d;
  d.show();
  if (verbose) { TRACE("Must get after set"); }
  {
    const auto arrow = CreateRandomArrow();
    d.SetArrow(arrow);
    assert(d.GetArrow() == arrow);
  }
  if (verbose) { TRACE("Changing the mid X via UI, must change the arrow"); }
  {
    const auto arrow = CreateRandomArrow();
    d.SetArrow(arrow);
    const double old_x{arrow->GetMidX()};
    const double new_x{old_x + 10.0};
    assert(new_x != old_x);
    d.m_dialog_left->SetUiMidX(new_x);
    assert(std::abs(arrow->GetMidX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("Changing the mid X via arrow, must change the UI"); }
  {
    const auto arrow = CreateRandomArrow();
    d.SetArrow(arrow);
    const double old_x{arrow->GetMidX()};
    const double new_x{old_x + 10.0};
    assert(new_x != old_x);
    arrow->SetMidX(new_x);
    assert(std::abs(d.m_dialog_left->GetUiMidX() - new_x) < 2.0);
  }
}
#endif
