#include "qtdialog.h"

#include <QKeyEvent>

#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QUndoStack>

#include "qtaddrowcommand.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_model(new QStandardItemModel),
  m_undo_stack(new QUndoStack)
{
  ui->setupUi(this);
  ui->tree->setModel(m_model);
  ui->tree->setItemDelegate(new QStyledItemDelegate);
}

QtDialog::~QtDialog()
{
  delete ui;
  delete m_undo_stack;
}

void QtDialog::keyPressEvent(QKeyEvent * e)
{
  if ( (e->modifiers() & Qt::ControlModifier)
    && !(e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_undo_stack->undo();
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_undo_stack->redo();
  }
}

void QtDialog::on_button_clicked()
{
  QtAddRowCommand * const cmd = new QtAddRowCommand(m_model,ui->tree);
  m_undo_stack->push(cmd);

  ui->tree->scrollToBottom();

  const int n_rows = m_model->rowCount();
  QStandardItem * const item = m_model->item(n_rows - 1);
  ui->tree->edit(item->index());

}
