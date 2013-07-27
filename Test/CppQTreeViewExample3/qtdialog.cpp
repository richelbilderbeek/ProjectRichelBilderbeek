#include "qtdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QUndoStack>

#include "qtaddrowcommand.h"
#include "ui_qtdialog.h"
#include "qtmytreeview.h"
#include "qtmyitem.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_model(new QStandardItemModel),
  m_undo_stack(new QUndoStack),
  m_view(new QtMyTreeView)
{
  ui->setupUi(this);
  assert(ui->scrollAreaWidgetContents->layout());
  ui->scrollAreaWidgetContents->layout()->addWidget(m_view);
  m_view->setModel(m_model);
  m_view->setItemDelegate(new QStyledItemDelegate);

  //Initial the QtMyTreeView with some items
  for (int i=0; i!=26; ++i)
  {
    QtAddRowCommand * const cmd
      = new QtAddRowCommand(
        m_model,
        m_view,
        boost::lexical_cast<std::string,char>('A' + i));
    m_undo_stack->push(cmd);
  }

}

QtDialog::~QtDialog()
{
  delete ui;
  delete m_model;
  delete m_undo_stack;
  delete m_view;
}

void QtDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
  if ( (e->modifiers() & Qt::ControlModifier)
    && !(e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_undo_stack->undo();
    return;
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_undo_stack->redo();
    return;
  }
}

void QtDialog::on_button_clicked()
{
  QtAddRowCommand * const cmd = new QtAddRowCommand(m_model,m_view);
  m_undo_stack->push(cmd);

  const int n_rows = m_model->rowCount();
  QtMyItem * const item = dynamic_cast<QtMyItem*>(m_model->item(n_rows - 1));
  assert(item);
  m_view->edit(item->index());

}
