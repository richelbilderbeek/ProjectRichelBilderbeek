//---------------------------------------------------------------------------
/*
TestQtRoundedRectItem, tool to test QtRoundedRectItem
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtroundedrectitemmodifydialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>
#include <QTimer>

#include "qtroundedrectitemdialog.h"
#include "qtroundedrectitem.h"
#include "ribi_random.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestqtroundedrectitemmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedRectItemModifyDialog::QtTestQtRoundedRectItemModifyDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedRectItemModifyDialog),
    m_dialog_left(new QtRoundedRectItemDialog),
    m_dialog_right(new QtRoundedRectItemDialog)
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
    QObject::connect(timer,&QTimer::timeout,this,&ribi::QtTestQtRoundedRectItemModifyDialog::DoSomethingRandom);
    timer->setInterval(100);
    timer->start();
  }

  {
    boost::shared_ptr<QtRoundedRectItem> item(new QtRoundedRectItem);
    {
      const QPen pen(
        QBrush(qRgb(0,0,0)),
        2.0,
        Qt::SolidLine
      );
      item->SetContourPen(pen);
    }
    {
      const QPen pen(
        QBrush(qRgb(0,0,0)),
        3.0,
        Qt::DashLine
      );
      item->SetFocusPen(pen);
    }
    item->SetOuterHeight(32.0);
    item->SetCenterPos(0.0,0.0);
    item->SetRadiusX(5.0);
    item->SetRadiusY(6.0);
    item->SetOuterWidth(48.0);
    SetItem(item);
  }

}

ribi::QtTestQtRoundedRectItemModifyDialog::~QtTestQtRoundedRectItemModifyDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedRectItemModifyDialog::DoSomethingRandom() noexcept
{
  if (!ui->box_change->isChecked()) return;
  m_dialog_left->DoSomethingRandom();
  m_dialog_right->DoSomethingRandom();
}

void ribi::QtTestQtRoundedRectItemModifyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

boost::shared_ptr<ribi::QtRoundedRectItem> ribi::QtTestQtRoundedRectItemModifyDialog::CreateRandomItem() noexcept
{
  boost::shared_ptr<QtRoundedRectItem> item(new QtRoundedRectItem);
  {
    const QPen pen(
      QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
      1.0 + (static_cast<double>(std::rand() % 100) / 10.0),
      Qt::SolidLine
    );
    item->SetContourPen(pen);
  }
  {
    const QPen pen(
      QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
      1.0 + (static_cast<double>(std::rand() % 100) / 10.0),
      Qt::DashLine
    );
    item->SetFocusPen(pen);
  }
  item->SetInnerHeight(200.0 * Random().GetFraction());
  item->SetCenterPos(
    -50.0 + (100.0 * Random().GetFraction()),
    -50.0 + (100.0 * Random().GetFraction())
  );
  item->SetRadiusX(100.0 * Random().GetFraction());
  item->SetRadiusY(100.0 * Random().GetFraction());
  item->SetInnerWidth(200.0 * Random().GetFraction());
  return item;
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_button_set_item_clicked()
{
  const auto item = CreateRandomItem();
  assert(item);
  SetItem(item);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::SetItem(const boost::shared_ptr<QtRoundedRectItem>& item) noexcept
{
  m_dialog_left->SetItem(item);
  m_dialog_right->SetItem(item);

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
  ui->view_left->scene()->addItem(item.get());

}

#ifndef NDEBUG
void ribi::QtTestQtRoundedRectItemModifyDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
