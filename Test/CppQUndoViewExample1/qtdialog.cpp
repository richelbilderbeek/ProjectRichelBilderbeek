#include "qtdialog.h"

#include <cassert>
#include <QKeyEvent>
#include <QUndoStack>
#include <QUndoView>
#include "qtbuttonincrementcommand.h"

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_stack(new QUndoStack(this))
{
  ui->setupUi(this);

  //Add the QUndoView and be done with it
  {
    //Craate the QUndoView
    QUndoView * const view = new QUndoView(this);

    //Let it display the QUndoStack m_stack
    view->setStack(m_stack);

    //Let it have some height
    view->setMinimumHeight(200);

    //Add it to this dialog's layout
    assert(this->layout());
    this->layout()->addWidget(view);
  }
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
    return;
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    m_stack->redo();
    return;
  }
  if ( e->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
}

void QtDialog::on_button_clicked()
{
  QtButtonIncrementCommand * const cmd
    = new QtButtonIncrementCommand(ui->button);

  //By pushing the command, redo is called
  m_stack->push(cmd);
}
