#include "qtdialog.h"

#include <QKeyEvent>
#include <QUndoStack>
#include "qtbuttonincrementcommand.h"

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_stack(new QUndoStack(this))
{
  ui->setupUi(this);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::keyPressEvent(QKeyEvent * e)
{
  if ( (e->modifiers() & Qt::ControlModifier)
    && !(e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_stack->undo();
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_stack->redo();
  }
}

void QtDialog::on_button_clicked()
{
  QtButtonIncrementCommand * const cmd
    = new QtButtonIncrementCommand(ui->button);

  //By pushing the command, redo is called
  m_stack->push(cmd);
}
