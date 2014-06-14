//---------------------------------------------------------------------------
/*
TestQtRoundedRectItem, tool to test QtRoundedRectItem
Copyright (C) 2012-2014 Richel Bilderbeek

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

#include <QKeyEvent>

#include "qtroundedrectitem.h"
#include "trace.h"
#include "ui_qttestqtroundedrectitemmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedRectItemModifyDialog::QtTestQtRoundedRectItemModifyDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedRectItemModifyDialog),
    m_item(boost::make_shared<QtRoundedRectItem>())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    assert(!ui->view_left->scene());
    assert(!ui->view_right->scene());
    QGraphicsScene * const scene = new QGraphicsScene;
    ui->view_left->setScene(scene);
    ui->view_right->setScene(scene);
    assert(ui->view_left->scene());
    assert(ui->view_right->scene());
    scene->addItem(m_item.get());
  }
  ui->box_x->setValue(m_item->pos().x());
  ui->box_y->setValue(m_item->pos().y());
  ui->box_width->setValue(m_item->rect().width());
  ui->box_height->setValue(m_item->rect().height());
  ui->box_radius_x->setValue(m_item->GetRadiusX());
  ui->box_radius_y->setValue(m_item->GetRadiusY());
}

ribi::QtTestQtRoundedRectItemModifyDialog::~QtTestQtRoundedRectItemModifyDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedRectItemModifyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedRectItemModifyDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQtRoundedRectItemModifyDialog::Test");
  TRACE("Finished ribi::QtTestQtRoundedRectItemModifyDialog::Test successfully");
}
#endif

void ribi::QtTestQtRoundedRectItemModifyDialog::on_button_contour_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0)
  );
  m_item->SetContourPen(pen);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_button_focus_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0),
    Qt::DashLine
  );
  m_item->SetFocusPen(pen);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_radius_x_valueChanged(double arg1)
{
  m_item->SetRadiusX(arg1);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_radius_y_valueChanged(double arg1)
{
  m_item->SetRadiusY(arg1);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_x_valueChanged(double arg1)
{
  m_item->SetPos(arg1,m_item->pos().y());
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_y_valueChanged(double arg1)
{
  m_item->SetPos(m_item->pos().x(),arg1);
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_width_valueChanged(double arg1)
{
  m_item->setRect(
    m_item->pos().x(),
    m_item->pos().y(),
    arg1,
    m_item->rect().height()
  );
}

void ribi::QtTestQtRoundedRectItemModifyDialog::on_box_height_valueChanged(double arg1)
{
  m_item->setRect(
    m_item->pos().x(),
    m_item->pos().y(),
    m_item->rect().width(),
    arg1
  );
}
