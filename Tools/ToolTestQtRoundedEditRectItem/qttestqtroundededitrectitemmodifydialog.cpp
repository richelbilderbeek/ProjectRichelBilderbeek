//---------------------------------------------------------------------------
/*
TestQtRoundedEditRectItem, tool to test QtRoundedRectItem
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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtroundededitrectitemmodifydialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QGraphicsView>

#include "container.h"
#include "qtroundededitrectitem.h"
#include "qtroundededitrectitemdialog.h"
#include "trace.h"
#include "ui_qttestqtroundededitrectitemmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedEditRectItemModifyDialog::QtTestQtRoundedEditRectItemModifyDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedEditRectItemModifyDialog),
    m_dialog_left(boost::make_shared<QtRoundedEditRectItemDialog>()),
    m_dialog_right(boost::make_shared<QtRoundedEditRectItemDialog>()),
    m_view_left(boost::make_shared<QGraphicsView>()),
    m_view_right(boost::make_shared<QGraphicsView>())

{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  const auto item = boost::make_shared<QtRoundedEditRectItem>();

  //Add item to both dialogs
  m_dialog_left->SetItem(item);
  m_dialog_right->SetItem(item);

  //Create scene and add item to it
  {
    assert(!m_view_left->scene());
    assert(!m_view_right->scene());
    QGraphicsScene * const scene = new QGraphicsScene;
    m_view_left->setScene(scene);
    m_view_right->setScene(scene);
    assert(m_view_left->scene());
    assert(m_view_right->scene());
    scene->addItem(item.get());
  }

  //Put dialogs and view on dialog
  {
    assert(!this->layout());
    QHBoxLayout * const my_layout = new QHBoxLayout;
    this->setLayout(my_layout);
    assert(this->layout());

    my_layout->addWidget(m_view_left.get());
    my_layout->addWidget(m_view_right.get());
    my_layout->addWidget(m_dialog_left.get());
    my_layout->addWidget(m_dialog_right.get());
  }
}

ribi::QtTestQtRoundedEditRectItemModifyDialog::~QtTestQtRoundedEditRectItemModifyDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

/*
void ribi::QtTestQtRoundedEditRectItemModifyDialog::OnPosChanged(QtRoundedRectItem * const qtitem) noexcept
{
  const double new_x = qtitem->pos().x();
  const double new_y = qtitem->pos().y();
  ui->box_x->setValue(new_x);
  ui->box_y->setValue(new_y);
}
*/

#ifndef NDEBUG
void ribi::QtTestQtRoundedEditRectItemModifyDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQtRoundedEditRectItemModifyDialog::Test");
  TRACE("Finished ribi::QtTestQtRoundedEditRectItemModifyDialog::Test successfully");
}
#endif
/*
void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_button_contour_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0)
  );
  m_item->SetContourPen(pen);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_button_focus_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0),
    Qt::DashLine
  );
  m_item->SetFocusPen(pen);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_box_radius_x_valueChanged(double arg1)
{
  m_item->SetRadiusX(arg1);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_box_radius_y_valueChanged(double arg1)
{
  m_item->SetRadiusY(arg1);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_box_x_valueChanged(double arg1)
{
  m_item->SetPos(arg1,m_item->pos().y());
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_box_y_valueChanged(double arg1)
{
  m_item->SetPos(m_item->pos().x(),arg1);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_button_font_clicked()
{
  static QFont font = m_item->GetFont();
  bool ok = false;
  const QFont new_font = QFontDialog::getFont(&ok, font, this);
  if (ok) { m_item->SetFont(new_font); }
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_text_textChanged()
{
  const auto s = ui->text->toPlainText().toStdString();
  const auto text = Container().SeperateString(s,'\n');
  m_item->SetText(text);
}

void ribi::QtTestQtRoundedEditRectItemModifyDialog::on_button_text_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0)
  );
  m_item->SetTextPen(pen);
}
*/
