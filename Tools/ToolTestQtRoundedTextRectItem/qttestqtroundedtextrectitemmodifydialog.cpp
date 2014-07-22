//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedRectItem
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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtroundedtextrectitemmodifydialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QGraphicsView>

#include "container.h"
#include "qtroundedtextrectitem.h"
#include "qtroundedtextrectitemdialog.h"
#include "trace.h"
#include "ui_qttestqtroundedtextrectitemmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedTextRectItemModifyDialog::QtTestQtRoundedTextRectItemModifyDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedTextRectItemModifyDialog),
    m_dialog_left(boost::make_shared<QtRoundedTextRectItemDialog>()),
    m_dialog_right(boost::make_shared<QtRoundedTextRectItemDialog>()),
    m_view_left(boost::make_shared<QGraphicsView>()),
    m_view_right(boost::make_shared<QGraphicsView>())

{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  const auto item = boost::make_shared<QtRoundedTextRectItem>();

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

ribi::QtTestQtRoundedTextRectItemModifyDialog::~QtTestQtRoundedTextRectItemModifyDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedTextRectItemModifyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedTextRectItemModifyDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQtRoundedTextRectItemModifyDialog::Test");
  TRACE("Finished ribi::QtTestQtRoundedTextRectItemModifyDialog::Test successfully");
}
#endif
